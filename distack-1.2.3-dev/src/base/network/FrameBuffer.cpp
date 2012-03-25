#include "FrameBuffer.h"

FrameBuffer::FrameBuffer( NetworkInterface& networkInterface, DistackInfo* info )
	: m_maxFrames( 0 ), m_maxBytes( 0 ), m_droppedFrames( 0 ),
	m_droppedBytes( 0 ), m_currentFrames( 0 ),
	m_currentBytes( 0 ), m_networkInterface( networkInterface ), distackInfo( info ),
	m_onlineCapture( networkInterface.getCaptureType() == NetworkInterface::CAPTURE_TYPE_ONLINE ){
}

FrameBuffer::~FrameBuffer ()
{
}

void FrameBuffer::startup(){

	//
	// start the packet-reader-thread if we are reading from 
	// an online source. if this is an offline source we will
	// just redirect any read requests directly to the interface
	//

	if (m_onlineCapture) {
		m_threadRunning = true;
		m_readThread = new boost::thread( 
			boost::bind (&FrameBuffer::readThreadFunction, this) );
	}
}

void FrameBuffer::prepareshutdown(){
	m_threadRunning = false;
}

void FrameBuffer::shutdown(){

	//
	// stop the packet reader thread
	//
	
	if (m_onlineCapture) {
		m_readThread->join ();
		delete m_readThread;
		m_readThread = NULL;
	}
	
	//
	// delete all buffered frames
	//

	clear ();
}

void FrameBuffer::setMaxFrames(unsigned int frames)
{
	boost::mutex::scoped_lock scopedLock( m_counterMutex );
	if( m_maxFrames > 0 ) m_maxFrames = frames;
}

void FrameBuffer::setMaxBytes(unsigned int bytes)
{
	boost::mutex::scoped_lock scopedLock( m_counterMutex );
	if( m_maxBytes > 0 ) m_maxBytes = bytes;
}

Frame* FrameBuffer::next ()
{
	Frame* frame = NULL;

	if (m_onlineCapture) {

		{
			boost::mutex::scoped_lock scopedLock (m_frameQueueMutex);

			if (m_frameQueue.empty ()) return frame;
			frame = m_frameQueue.front ();
			m_frameQueue.pop ();
		}

		{
			boost::mutex::scoped_lock scopedLock (m_counterMutex);
			m_currentFrames--;
			m_currentBytes -= frame->getSize ();
		}

	} else {

		frame = m_networkInterface.read ();
		if (frame == NULL) logging_info( "reached end of capture file");
	}

	return frame;
}

void FrameBuffer::clear ()
{
	{
		boost::mutex::scoped_lock scopedLock (m_frameQueueMutex);

		while (! m_frameQueue.empty ()) {
			
			Frame* frame = m_frameQueue.front ();
			m_frameQueue.pop ();
			
			//
			// free the packet. this is done recursively
			// because the Packet-dtor calls PacketFactory::freePacket
			// for his next packet ...
			//

			PacketFactory::instance()->freeFrame (frame);

		} // while (! m_frameQueue.empty ())
	}

	{
		boost::mutex::scoped_lock scopedLock (m_counterMutex);
		m_currentFrames = 0;
		m_currentBytes  = 0;
	}
}

unsigned int FrameBuffer::count ()
{
	boost::mutex::scoped_lock scopedLock (m_frameQueueMutex);
	return (unsigned int) m_frameQueue.size ();
}

unsigned int FrameBuffer::getFrameDrops ()
{
	boost::mutex::scoped_lock scopedLock (m_counterMutex);
	return m_droppedFrames;
}

unsigned int FrameBuffer::getByteDrops ()
{
	boost::mutex::scoped_lock scopedLock (m_counterMutex);
	return m_droppedBytes;
}

void FrameBuffer::readThreadFunction (FrameBuffer* obj)
{
	assert( obj->m_onlineCapture == true );
	Log::debug( obj->distackInfo, "starting packet-buffer read thread ..." );

	Frame* frame = NULL;
	bool acceptFrame = false;

	while( obj->m_threadRunning ){

		frame = obj->m_networkInterface.read ();
		acceptFrame = true;

		if (frame == NULL) {
			Helper::sleep (10);
			continue;
		}

		{
			boost::mutex::scoped_lock scopedLock (obj->m_counterMutex);
			
			if (obj->m_maxFrames > 0)
				acceptFrame &= (obj->m_currentFrames + 1 <= obj->m_maxFrames);
			
			if (obj->m_maxBytes > 0)
				acceptFrame &= (obj->m_currentBytes  + frame->getSize() <= obj->m_maxBytes);

			if (acceptFrame) {
				obj->m_currentFrames++;
				obj->m_currentBytes += frame->getSize ();
			} else {			
				obj->m_droppedFrames++;
				obj->m_droppedBytes += frame->getSize ();
			}
		}

		//
		// either queue the frame or delete it
		//

		if (acceptFrame) {
			boost::mutex::scoped_lock scopedLock (obj->m_frameQueueMutex);
			obj->m_frameQueue.push (frame);
		} else
			delete frame;

	} // while (obj->m_threadRunning)
}

NetworkInterface& FrameBuffer::getNetworkInterface ()
{
	return m_networkInterface;
}
