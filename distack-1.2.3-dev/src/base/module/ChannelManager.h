#ifndef __CHANNEL_MANAGER_H
#define __CHANNEL_MANAGER_H

#include "base/module/Channel.h"
#include "base/protocol/Frame.h"
#include "base/module/DistackModuleInterface.h"
#include "base/message/MessagingSystem.h"
#include <vector>
#include <algorithm>
#include <list>
#include <boost/thread/mutex.hpp>

using std::list;
using std::find;
using std::vector;

#ifdef OMNET_SIMULATION
	class DistackOmnetModule; // forward decl
#endif // OMNET_SIMULATION

class ChannelManager {
public:
							ChannelManager				(DistackInfo* info);
							~ChannelManager				();

	typedef vector<Channel*>							CHANNEL_VECTOR;
	typedef CHANNEL_VECTOR::iterator					CHANNEL_VECTOR_ITERATOR;

	Channel*				newChannel					(Channel::CHANNEL_CONFIGURATION conf, MessagingSystem& msgsystem);
	void					deleteChannels				(unsigned short stage);
	void					frameCall					(Frame* frame);

#ifdef OMNET_SIMULATION
	void					setDistackModule			(DistackOmnetModule* module);	
#endif // OMNET_SIMULATION

private:

	CHANNEL_VECTOR						m_channels;
	boost::mutex						m_channelsMutex;

	DistackInfo* distackInfo;

#ifdef OMNET_SIMULATION
	DistackOmnetModule*					distackModule;	
#endif // OMNET_SIMULATION

};

#endif // __CHANNEL_MANAGER_H
