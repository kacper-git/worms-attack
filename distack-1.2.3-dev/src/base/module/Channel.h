#ifndef __CHANNEL_H
#define __CHANNEL_H

#include <vector>
#include <algorithm>
#include "base/protocol/Frame.h"
#include "base/message/MessagingSystem.h"

class Timer;
class Module;
#ifdef OMNET_SIMULATION
class DistackOmnetModule;
#endif

using std::find;
using std::vector;

class Channel {
public:
	Channel( string name, unsigned short stage, DistackInfo* info );
	virtual ~Channel();

	typedef list<ModuleConfiguration> 		MODULE_CONFIGURATION_LIST;
	typedef MODULE_CONFIGURATION_LIST::iterator	MODULE_CONFIGURATION_LIST_ITERATOR;

	typedef struct _CHANNEL_CONFIGURATION {
		string				name;
		unsigned short			stage;
		MODULE_CONFIGURATION_LIST	moduleConfigs;
	} CHANNEL_CONFIGURATION, *PCHANNEL_CONFIGURATION;

	bool startup( MODULE_CONFIGURATION_LIST config, MessagingSystem& msgsystem );
	bool shutdown();

	void frameCall( Frame& frame );

	string getName();
	unsigned short getStage();
	
#ifdef OMNET_SIMULATION
	void setDistackModule( DistackOmnetModule* module );
#endif // OMNET_SIMULATION

private:
	DistackInfo* distackInfo;

	typedef vector<Module*> MODULE_VECTOR;
	typedef MODULE_VECTOR::iterator MODULE_VECTOR_ITERATOR;

	Module* addModule( ModuleConfiguration config );
	MODULE_VECTOR m_modules;

	string m_name;
	unsigned short m_stage;

	MessagingSystem* m_messagingSystem;

#ifdef OMNET_SIMULATION
	DistackOmnetModule* distackModule;
#endif // OMNET_SIMULATION

};

#endif // __CHANNEL_H
