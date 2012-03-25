#ifndef __MODULE_MANAGER_H
#define __MODULE_MANAGER_H

#include <string>
#include <map>
#include "base/common/Log.h"
#include "base/configuration/Configuration.h"
#include "base/module/DistackModuleInterface.h"
#include "base/module/Module.h"
#include "base/module/FrameDistribution.h"
#include "base/module/ChannelManager.h"
#include "base/message/MessagingSystem.h"
#include "messages/utility/MessageAlert.h"
#include "base/message/MessagingNode.h"
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>

using std::map;
using std::pair;
using std::string;

#ifdef OMNET_SIMULATION
	class DistackOmnetModule; // forward decl
#endif // OMNET_SIMULATION

class ModuleManager : public MessagingNode {
public:
						ModuleManager			(DistackInfo* info);
						~ModuleManager			();

	bool				startup					();

	bool				startFrameEating		(FrameBuffer* framebuffer);
	bool				stopFrameEating			();

	MessagingSystem*	getMessagingSystem		();
	FrameDistribution*	getFrameDistribution	();


#ifdef OMNET_SIMULATION
	void				setDistackModule		(DistackOmnetModule* module);	
#endif // OMNET_SIMULATION

protected:

	bool				loadStage				(unsigned short stage);
	bool				unloadStage				(unsigned short stage);
	void				receiveMessage			(Message* msg);

private:

	bool				loadAllChannels			();	
	bool				loadChannel				(string name, unsigned short stage);	
	
	typedef pair<string, ModuleConfiguration>	MODULE_POOL_PAIR;
	typedef map<string, ModuleConfiguration>	MODULE_POOL;
	typedef MODULE_POOL::iterator				MODULE_POOL_ITERATOR;
	MODULE_POOL									m_modulePool;

	FrameDistribution*	m_frameDistribution;
	ChannelManager*		m_channelManager;
	MessagingSystem*	m_messagingSystem;

	unsigned short		m_currentStageLevel;
	unsigned short		m_lowestStageLevel;
	boost::thread*		m_stageUpdateThread;
	volatile bool		m_stageUpdateInProgress;
	static void			updateStageThreadFunc	(ModuleManager* obj, MessageAlert::ALERT_TYPE type, unsigned short alertingStage);
	DistackInfo*		distackInfo;

#ifdef OMNET_SIMULATION
	DistackOmnetModule*	distackModule;	
#endif // OMNET_SIMULATION

};

#endif // __MODULE_MANAGER_H
