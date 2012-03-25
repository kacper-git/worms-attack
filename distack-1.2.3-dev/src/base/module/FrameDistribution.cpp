#include "FrameDistribution.h"

FrameDistribution::FrameDistribution (DistackInfo* info)
:	m_channelManager	(NULL),
	m_frameBuffer		(NULL),
	m_frameCount		(0)
{
	distackInfo = info;
}

FrameDistribution::~FrameDistribution ()
{
}
	
void FrameDistribution::setChannelManager (ChannelManager* channelmanager)
{
	boost::mutex::scoped_lock scopedLock (m_distributionMutex);
	m_channelManager = channelmanager;
}

void FrameDistribution::setFrameBuffer (FrameBuffer* framebuffer)
{
	boost::mutex::scoped_lock scopedLock (m_distributionMutex);
	m_frameBuffer = framebuffer;
}

bool FrameDistribution::startDistribution ()
{
	logging_debug( "starting frame distribution ...");

	assert (m_channelManager != NULL);
	assert (m_frameBuffer	 != NULL);

	m_threadRunning		 = true;
	m_distributionThread = new boost::thread (boost::bind (&FrameDistribution::distribThreadFunction, this));
	
	logging_debug( "frame distribution running");

	return (m_distributionThread != NULL);
}

bool FrameDistribution::stopDistribution ()
{
	logging_debug( "stopping frame distribution");

	m_threadRunning = false;

	//
	// early stop the network interface
	// otherwise the networkinterface::read-call will
	// block until the next frame is replayed
	//
	{
		boost::mutex::scoped_lock scopedLock (m_distributionMutex);
		m_frameBuffer->getNetworkInterface().close ();
	}

	m_distributionThread->join ();
	delete m_distributionThread;
	m_distributionThread = NULL;

	logging_debug( "frame distribution stopped");

	return true;
}

void FrameDistribution::distribThreadFunction (FrameDistribution* obj)
{
	while (obj->m_threadRunning) {

		Frame* frame = NULL;

		{
			boost::mutex::scoped_lock scopedLock (obj->m_distributionMutex);
			frame = obj->m_frameBuffer->next ();
		}

		if (frame == NULL) {		

			//
			// reached end of file on offline capture file
			//

			if (obj->m_frameBuffer->getNetworkInterface().getCaptureType() == NetworkInterface::CAPTURE_TYPE_OFFLINE) {
				Log::info( obj->distackInfo, "end of capture file after " + 
					Helper::ultos(obj->m_frameCount) + " frames" );
				return;
			}
			
			// TODO: maybe use boost::condition. Would be better performance
			// but worse usage because it would block and shutdown is bad
			Helper::sleep (10);		
		
			continue;
		}

		{
			boost::mutex::scoped_lock scopedLock (obj->m_distributionMutex);

			obj->m_channelManager->frameCall	 (frame);
			PacketFactory::instance()->freeFrame (frame);

			obj->m_frameCount++;
		}

	} // while (obj->m_threadRunning)
}

void FrameDistribution::manualFrameInjection (Frame* frame)
{
	boost::mutex::scoped_lock scopedLock (m_distributionMutex);
	m_channelManager->frameCall			 (frame);
	PacketFactory::instance()->freeFrame (frame);
}
