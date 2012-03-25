#ifndef __CONFIGURATION_H
#define __CONFIGURATION_H

#include <string>
#include <map>
#include <iostream>
#include "base/common/DistackInfo.h"
#include "base/common/Helper.h"
#include "base/common/Log.h"
#include "base/configuration/triggerconf.h"
#include "base/module/DistackModuleInterface.h"

using std::string;
using std::cout;
using std::map;

/** @class Configuration
  * Manages configuration settings for all Distack instances. Each Distack instance calls the constructor for this class and a new Configuration object is created and stored in a static map which prevents creation of duplicate Configuration objects accessing the same configuration file. The configuration options thmeselves are accessed using the Triggerconf XML library.
  */
class Configuration{
public:
	Configuration( string filename );
	~Configuration();
	
	static void			init			(DistackInfo* info);
	static Configuration*		instance		(DistackInfo* info);
	static Configuration*		instance		();
	static void			cleanup			(DistackInfo* info);

	typedef enum _NETWORK_TRACE_SOURCE {
		NETWORK_TRACE_SOURCE_UNDEFINED,
		NETWORK_TRACE_SOURCE_INTERFACE,
		NETWORK_TRACE_SOURCE_TRACEFILE,
	} NETWORK_TRACE_SOURCE; 

	LogLevel::LOG_LEVEL		getLogLevel		();
	string				getLogType		();

	NETWORK_TRACE_SOURCE		getFrameSourceType	();

	bool				getChecksumCheck	();
	string				getNetworkInterface	();
	string				getTraceFile		();
	double				getTraceReplaySpeedup	();
	bool				getNetworkPromiscuous	();
	unsigned int			getNetworkCaptureLen	();
	Triggerconf::STRING_LIST	getRemoteNeighbors	();
	string				getRemoteMessaging	();
	unsigned int			getQueueMaxFrames	();
	unsigned int			getQueueMaxBytes	();
	Triggerconf::STRING_LIST	getAvailableModules	();
	ModuleConfiguration		getModuleConfiguration	(string module);
	Triggerconf::STRING_LIST	getChannels		();
	Triggerconf::STRING_LIST	getChannels		(unsigned short stage);
	Triggerconf::STRING_LIST	getChannelItems		(string channel);

	static const string		DELIM;
	static const string		ATTRIBUTE_LIBRARY;
	static const string		ATTRIBUTE_STAGE;

	static const string		PATH_GENERAL;
	static const string		PATH_GENERAL_LOG;
	static const string		PATH_GENERAL_LOG_LOGLEVEL;
	static const string		PATH_GENERAL_LOG_LOGTYPE;
	static const string		PATH_GENERAL_NETWORK;
	static const string		PATH_GENERAL_NETWORK_CHECKSUMCHECK;
	static const string		PATH_GENERAL_NETWORK_INTERFACE;
	static const string		PATH_GENERAL_NETWORK_TRACEFILE;
	static const string		PATH_GENERAL_NETWORK_TRACEREPLAYSPEEDUP;
	static const string		PATH_GENERAL_NETWORK_PROMISCUOUS;
	static const string		PATH_GENERAL_NETWORK_CAPTURELENGTH;	
	static const string		PATH_GENERAL_REMOTE;
	static const string		PATH_GENERAL_REMOTE_NEIGHBORS;
	static const string		PATH_GENERAL_REMOTE_MESSAGING;
	static const string		PATH_GENERAL_QUEUE;
	static const string		PATH_GENERAL_QUEUE_MAX_FRAME_LEN;
	static const string		PATH_GENERAL_QUEUE_MAX_BYTE_LEN;
	static const string		PATH_MODULES;
	static const string		PATH_CHANNELS;

private:
	Triggerconf				tconf;
	static map<string, Configuration*>	instances;
};

#endif // __CONFIGURATION_H
