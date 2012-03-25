#include "Configuration.h"

const string	Configuration::DELIM					= "/";
const string	Configuration::ATTRIBUTE_LIBRARY			= "library";
const string	Configuration::ATTRIBUTE_STAGE				= "stage";

const string	Configuration::PATH_GENERAL				= "General";
const string	Configuration::PATH_GENERAL_LOG				= Configuration::PATH_GENERAL         + Configuration::DELIM + "Log";
const string	Configuration::PATH_GENERAL_LOG_LOGLEVEL		= Configuration::PATH_GENERAL_LOG     + Configuration::DELIM + "Loglevel";
const string	Configuration::PATH_GENERAL_LOG_LOGTYPE			= Configuration::PATH_GENERAL_LOG     + Configuration::DELIM + "Logtype";
const string	Configuration::PATH_GENERAL_NETWORK			= Configuration::PATH_GENERAL         + Configuration::DELIM + "Network";
const string 	Configuration::PATH_GENERAL_NETWORK_CHECKSUMCHECK	= Configuration::PATH_GENERAL_NETWORK + Configuration::DELIM + "ChecksumCheck"; 
const string 	Configuration::PATH_GENERAL_NETWORK_INTERFACE		= Configuration::PATH_GENERAL_NETWORK + Configuration::DELIM + "Interface";
const string 	Configuration::PATH_GENERAL_NETWORK_TRACEFILE		= Configuration::PATH_GENERAL_NETWORK + Configuration::DELIM + "TraceFile";
const string 	Configuration::PATH_GENERAL_NETWORK_TRACEREPLAYSPEEDUP	= Configuration::PATH_GENERAL_NETWORK + Configuration::DELIM + "TraceReplaySpeedup";
const string 	Configuration::PATH_GENERAL_NETWORK_PROMISCUOUS		= Configuration::PATH_GENERAL_NETWORK + Configuration::DELIM + "Promiscuous";
const string 	Configuration::PATH_GENERAL_NETWORK_CAPTURELENGTH	= Configuration::PATH_GENERAL_NETWORK + Configuration::DELIM + "CaptureLength";
const string	Configuration::PATH_GENERAL_REMOTE			= Configuration::PATH_GENERAL         + Configuration::DELIM + "Remote";
const string 	Configuration::PATH_GENERAL_REMOTE_NEIGHBORS		= Configuration::PATH_GENERAL_REMOTE  + Configuration::DELIM + "Neighbors";
const string 	Configuration::PATH_GENERAL_REMOTE_MESSAGING		= Configuration::PATH_GENERAL_REMOTE  + Configuration::DELIM + "Messaging";
const string	Configuration::PATH_GENERAL_QUEUE			= Configuration::PATH_GENERAL         + Configuration::DELIM + "Queue";
const string	Configuration::PATH_GENERAL_QUEUE_MAX_FRAME_LEN		= Configuration::PATH_GENERAL_QUEUE   + Configuration::DELIM + "MaxPackets";
const string	Configuration::PATH_GENERAL_QUEUE_MAX_BYTE_LEN		= Configuration::PATH_GENERAL_QUEUE   + Configuration::DELIM + "MaxBytes";
const string 	Configuration::PATH_MODULES				= "Modules";
const string 	Configuration::PATH_CHANNELS				= "Channels";

/**
  * stores all created Configuration instances to prevent duplicates
  */
map<string, Configuration*> Configuration::instances;

/**
  * creates a new Configuration instance if there already isn't one for a specific config file
  * @param info the DistackInfo object used to determine which config file to use
  */
void Configuration::init (DistackInfo* info)
{
	if(instances.find(info->configId) == instances.end()) {
		Configuration* object = new Configuration(info->configId);
		instances[info->configId] = object;
	}
}

void Configuration::cleanup (DistackInfo* info)
{
	map<string, Configuration*>::iterator i = instances.find(info->configId);
	if (i != instances.end()) {
		delete (*i).second;
		instances.erase(i);
	}
}
	
/**
  * used to access the correct Configuration instance, based on the DistackInfo object
  * @param info the DistackInfo object used to determine which config file to use
  * @see DistackInfo
  * @return the requested Configuration instance
  */
Configuration* Configuration::instance (DistackInfo* info)
{
	Configuration *object = instances[info->configId];
	return object;
}
#ifndef OMNET_SIMULATION
/**
  * only used with the pcap interface. as there is only one Distack instance in a pcap run on a given machine, we only need to create one Configuration instance
  * @return the requested Configuration instance
  */
Configuration* Configuration::instance ()
{
	Configuration* object = (instances.begin())->second;
	return object;
}
#endif // OMNET_SIMULATION

Configuration::Configuration (string filename)
	: tconf( filename, false, true, false) {

	//
	// check if the configuration file is fine
	//

	if (! tconf.isGood ()) {
		cout << "configuration error: " << tconf.getError () << std::endl;
		exit (0);
	}
}

Configuration::~Configuration ()
{
}

LogLevel::LOG_LEVEL Configuration::getLogLevel ()
{
	string val = tconf.getConfigValue (PATH_GENERAL_LOG_LOGLEVEL);
	LogLevel::LOG_LEVEL logLevel = LogLevel::TYPE_DEBUG;

	if (val == LOG_LEVEL_NAME_DEBUG)
		logLevel = LogLevel::TYPE_DEBUG;
	else if (val == LOG_LEVEL_NAME_INFO)
		logLevel = LogLevel::TYPE_INFO;
	else if (val == LOG_LEVEL_NAME_WARNING)
		logLevel = LogLevel::TYPE_WARNING;
	else if (val == LOG_LEVEL_NAME_ERROR)
		logLevel = LogLevel::TYPE_ERROR;

	return logLevel;
}

string Configuration::getLogType ()
{
	return tconf.getConfigValue (PATH_GENERAL_LOG_LOGTYPE);
}

Configuration::NETWORK_TRACE_SOURCE Configuration::getFrameSourceType ()
{
	string iface = getNetworkInterface	();
	string file  = getTraceFile			();

	if (iface.length() != 0 && file.length () == 0) return NETWORK_TRACE_SOURCE_INTERFACE;
	if (file.length () != 0 && iface.length() == 0) return NETWORK_TRACE_SOURCE_TRACEFILE;

	return NETWORK_TRACE_SOURCE_UNDEFINED;
}

string Configuration::getTraceFile ()
{
	return tconf.getConfigValue (PATH_GENERAL_NETWORK_TRACEFILE);
}

bool Configuration::getChecksumCheck ()
{
	// as this function is called very often
	// we cache the result to speed up
	
	static bool valid = false;
	static bool value = false;

	if( valid ) return value;

	value = (tconf.getConfigValue (PATH_GENERAL_NETWORK_CHECKSUMCHECK) == "1");
	valid = true;

	return value;
}

string Configuration::getNetworkInterface ()
{
	return tconf.getConfigValue (PATH_GENERAL_NETWORK_INTERFACE);
}

bool Configuration::getNetworkPromiscuous ()
{
	return (tconf.getConfigValue (PATH_GENERAL_NETWORK_PROMISCUOUS) == "1");
}

unsigned int Configuration::getNetworkCaptureLen ()
{
	string val = tconf.getConfigValue (PATH_GENERAL_NETWORK_CAPTURELENGTH);
	long ret = Helper::stol (val);
	
	if (ret < 0) return 0;
	else return ret;
}

Triggerconf::STRING_LIST Configuration::getRemoteNeighbors ()
{
	string val = tconf.getConfigValue (PATH_GENERAL_REMOTE_NEIGHBORS);
	Triggerconf::STRING_LIST ret;

	if (val == "") return ret;

	Helper::STRING_LIST iplist = Helper::split (val, ",");

	Helper::STRING_LIST_ITERATOR i    = iplist.begin ();
	Helper::STRING_LIST_ITERATOR iend = iplist.end   ();

	for ( ; i != iend; i++) 
		ret.push_back (Helper::trim(*i));

	return ret;
}

string Configuration::getRemoteMessaging ()
{
	return tconf.getConfigValue (PATH_GENERAL_REMOTE_MESSAGING);
}

unsigned int Configuration::getQueueMaxFrames ()
{
	string val = tconf.getConfigValue (PATH_GENERAL_QUEUE_MAX_FRAME_LEN);
	long ret = Helper::stol (val);
	
	if (ret < 0) return 0;
	else return ret;
}

unsigned int Configuration::getQueueMaxBytes ()
{
	string val = tconf.getConfigValue (PATH_GENERAL_QUEUE_MAX_BYTE_LEN);
	long ret = Helper::stol (val);
	
	if (ret < 0) return 0;
	else return ret;
}

Triggerconf::STRING_LIST Configuration::getAvailableModules ()
{
	return tconf.getSubmoduleNames (PATH_MODULES);
}

ModuleConfiguration Configuration::getModuleConfiguration (string module)
{
	ModuleConfiguration ret;
	
	ret.name = module;
	ret.library = tconf.getSubmoduleAttributeValue (PATH_MODULES, module, ATTRIBUTE_LIBRARY);
	
	string path = PATH_MODULES + Configuration::DELIM + module;

	Triggerconf::STRING_LIST params	= tconf.getConfigItemNames (path);
	Triggerconf::STRING_LIST_ITERATOR begin	= params.begin	();
	Triggerconf::STRING_LIST_ITERATOR end = params.end	();

	for ( ; begin != end; begin++) {
		
		string param = *begin;
		string val	 = tconf.getConfigValue (path + DELIM + param);

		ret.set (param, val);
	}

	return ret;
}

Triggerconf::STRING_LIST Configuration::getChannels ()
{
	Triggerconf::STRING_LIST channels = tconf.getSubmoduleNames (PATH_CHANNELS);

	return channels;
}

Triggerconf::STRING_LIST Configuration::getChannels (unsigned short stage)
{
	Triggerconf::STRING_LIST retChannels;
	Triggerconf::STRING_LIST channels = tconf.getSubmoduleNames (PATH_CHANNELS);

	Triggerconf::STRING_LIST_ITERATOR i = channels.begin ();
	Triggerconf::STRING_LIST_ITERATOR iend	= channels.end	 ();

	for ( ; i != iend; i++) {
		string currentStage = tconf.getSubmoduleAttributeValue (PATH_CHANNELS, *i, ATTRIBUTE_STAGE);
		
		if (Helper::stoi (currentStage) == stage)
			retChannels.push_back (*i);
	}
		
	return retChannels;
}	

Triggerconf::STRING_LIST Configuration::getChannelItems (string channel)
{
	Triggerconf::STRING_LIST moduleIds = tconf.getConfigItemNames (PATH_CHANNELS, channel);
	Triggerconf::STRING_LIST names;

	Triggerconf::STRING_LIST_ITERATOR i = moduleIds.begin ();
	Triggerconf::STRING_LIST_ITERATOR iend	= moduleIds.end	  ();

	for ( ; i != iend; i++)
		names.push_back (tconf.getConfigValue (PATH_CHANNELS, channel, *i));

	return names;
}

double Configuration::getTraceReplaySpeedup ()
{
	string speedup = tconf.getConfigValue (PATH_GENERAL_NETWORK_TRACEREPLAYSPEEDUP);
	if (speedup.length() <= 0) return 1.0;
	else return Helper::stod (speedup);
}
