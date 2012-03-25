#include "ChannelManager.h"

ChannelManager::ChannelManager (DistackInfo* info)
{
	distackInfo = info;
#ifdef OMNET_SIMULATION
	distackModule = NULL;	
#endif // OMNET_SIMULATION
}

ChannelManager::~ChannelManager ()
{
	boost::mutex::scoped_lock scopedLock (m_channelsMutex);

	CHANNEL_VECTOR_ITERATOR i	 = m_channels.begin ();
	CHANNEL_VECTOR_ITERATOR iend = m_channels.end	();

	for ( ; i != iend; i++) 
		delete *i;

	m_channels.clear ();
}

Channel* ChannelManager::newChannel (Channel::CHANNEL_CONFIGURATION conf, MessagingSystem& msgsystem)
{
	//
	// create a new channel
	//

	Channel* channel = new Channel (conf.name, conf.stage, distackInfo);

#ifdef OMNET_SIMULATION
	channel->setDistackModule (distackModule);
#endif // OMNET_SIMULATION

	bool ret = channel->startup (conf.moduleConfigs, msgsystem);

	//
	// if any module creation failed (incorrect configuration parameters) we return 
	//

	if (! ret) {
		delete channel;	
		return NULL;
	}

	//
	// add the new channel to the channels vector
	//
 
	{
		boost::mutex::scoped_lock scopedLock (m_channelsMutex);
		m_channels.push_back (channel);
	}

	return channel;
}

void ChannelManager::deleteChannels (unsigned short stage)
{
	boost::mutex::scoped_lock scopedLock (m_channelsMutex);

	bool deleted;

	do{
		deleted = false;

		CHANNEL_VECTOR_ITERATOR i	 = m_channels.begin ();
		CHANNEL_VECTOR_ITERATOR iend = m_channels.end	();

		for ( ; i != iend; i++) {

			Channel* channel = *i;
			assert (channel != NULL);

			if (channel->getStage() >= stage) {

				channel->shutdown	 ();
				// erase invalidates iterator i, thus we have to break this for loop and restart the while loop
				m_channels.erase (i);
				delete channel;
				
				deleted = true;
				break;

			} // if (i->getStage() >= stage)
		} // for ( ; i != iend; i++)

	} while (deleted);
}

void ChannelManager::frameCall (Frame* frame)
{
	if (frame == NULL) return;

	boost::mutex::scoped_lock scopedLock (m_channelsMutex);

	CHANNEL_VECTOR_ITERATOR i	 = m_channels.begin ();
	CHANNEL_VECTOR_ITERATOR iend = m_channels.end	();

	for ( ; i != iend; i++) 
		(*i)->frameCall (*frame);
}

#ifdef OMNET_SIMULATION
void ChannelManager::setDistackModule (DistackOmnetModule* module)
{
	distackModule = module;
}
#endif // OMNET_SIMULATION
