#include "ModuleManager.h"

#define MAX_NUM_STAGES 100

ModuleManager::ModuleManager (DistackInfo* info)
:	m_currentStageLevel		(0),
	m_lowestStageLevel		(0),
	m_stageUpdateThread		(NULL),
	m_stageUpdateInProgress	(false)
{
	distackInfo = info;
	m_frameDistribution = new FrameDistribution(distackInfo);
	m_channelManager = new ChannelManager(distackInfo);
	m_messagingSystem = new MessagingSystem(distackInfo);

#ifdef OMNET_SIMULATION
	distackModule = NULL;	
#endif // OMNET_SIMULATION

	//
	// get all the module descriptions that are available
	//

	Triggerconf::STRING_LIST			modules = Configuration::instance(distackInfo)->getAvailableModules ();
	Triggerconf::STRING_LIST_ITERATOR	begin	= modules.begin ();
	Triggerconf::STRING_LIST_ITERATOR	end		= modules.end	();

	for ( ; begin != end; begin++) {

		string				modulename	= *begin;
		ModuleConfiguration config		= Configuration::instance(distackInfo)->getModuleConfiguration (modulename);

		logging_debug( "found module " + modulename + " with parameters " + config.toString());

		if (m_modulePool.find (modulename) != m_modulePool.end()) {
			logging_error( "skipping duplicate module name " + modulename + " in configuration");
			continue;
		}

		m_modulePool.insert (MODULE_POOL_PAIR (modulename, config));

	} // for ( ; begin != end; begin++)

	//
	// register with the messaging system
	//

	MessagingNode* messenger = dynamic_cast<MessagingNode*> (this);
	assert (messenger != NULL);
	m_messagingSystem->subscribe (messenger, Message::MESSAGE_TYPE_ALERT);

	    //
	    // configure the library search pathes for the module libraries
	    //

	    DynamicLibrary::SEARCH_PATHES pathes;
	    pathes.push_back ("");
	    pathes.push_back ("./");
	    pathes.push_back ("./modules/");
	    pathes.push_back ("../lib/");

	    Module::setLibrarySearchPaths (pathes);
}

ModuleManager::~ModuleManager ()
{
	MessagingNode* messenger = dynamic_cast<MessagingNode*> (this);
	if (messenger != NULL) m_messagingSystem->unsubscribeAll (messenger);

	delete m_messagingSystem;
	delete m_channelManager;
	delete m_frameDistribution;

	m_modulePool.clear ();

	if (m_stageUpdateThread != NULL) {
		m_stageUpdateThread->join ();
		delete m_stageUpdateThread;
		m_stageUpdateThread = NULL;
	}
}

bool ModuleManager::startup ()
{
	//
	// load the minimal stage, try out which one is the first minimal 
	//

	bool ret = false;

	for (unsigned short stage = 0; stage < MAX_NUM_STAGES && ret == false; stage++) {
		
		ret = loadStage (stage);
		
		if (ret) {
			m_currentStageLevel = stage;
			m_lowestStageLevel  = stage;
		}
	}

	//
	// if no channel was assigned a stage number, load all channels together as stage 0
	//

	if (!ret) {
		ret = loadAllChannels ();

		if (ret) {
			m_currentStageLevel = 0;
			m_lowestStageLevel  = 0;
		}
	}

	return ret;
}

bool ModuleManager::loadStage (unsigned short stage)
{
	logging_debug( "loading stage " +  Helper::ultos(stage) + " ...");

	//
	// get all the channels that belong to the stage
	//

	Triggerconf::STRING_LIST channels = Configuration::instance(distackInfo)->getChannels (stage);

	//
	// load each channel that belongs to the stage
	//

	bool								ret		= false;
	bool                                    loadSuccess     = true;
	Triggerconf::STRING_LIST_ITERATOR	i		= channels.begin ();
	Triggerconf::STRING_LIST_ITERATOR	iend	= channels.end	 ();

	for ( ; i != iend; i++) {
		ret = true;
		loadSuccess &= loadChannel (*i, stage);
	}

	logging_debug( "loading stage " + Helper::ultos(stage) + " " + ((ret&loadSuccess) ? "succeeded" : "failed"));
	return (ret&loadSuccess);
}

bool ModuleManager::loadAllChannels ()
{
	logging_debug( "loading all channels as stage 0 ...");

	//
	// get all available channels
	//

	Triggerconf::STRING_LIST channels = Configuration::instance(distackInfo)->getChannels ();

	//
	// load each channel
	//

	bool								ret		= true;
	Triggerconf::STRING_LIST_ITERATOR	i		= channels.begin ();
	Triggerconf::STRING_LIST_ITERATOR	iend	= channels.end	 ();

	for ( ; i != iend; i++)
		ret &= loadChannel (*i, 0);

	string result = (ret ? "succeeded" : "failed");
	logging_debug( "loading stage " + result);

	return ret;
}

bool ModuleManager::loadChannel	(string name, unsigned short stage)
{
	Triggerconf::STRING_LIST modulenames = Configuration::instance(distackInfo)->getChannelItems (name);

	Triggerconf::STRING_LIST_ITERATOR i		= modulenames.begin ();
	Triggerconf::STRING_LIST_ITERATOR iend	= modulenames.end	();

	Channel::CHANNEL_CONFIGURATION configs;
	configs.name  = name;
	configs.stage = stage;

	for ( ; i != iend; i++) {
		
		MODULE_POOL_ITERATOR item = m_modulePool.find (*i);

		if (item == m_modulePool.end()) {
			logging_error( "module " + *i + " from channel " + name + " not found in configuration");	
			return false;
		}

		configs.moduleConfigs.push_back (item->second);
	}

	//
	// now create the channel with the configuration list
	//

	Channel* channel = m_channelManager->newChannel (configs, *m_messagingSystem);

	return (channel != NULL);
}

bool ModuleManager::unloadStage (unsigned short stage)
{
	logging_debug( "unloading stage " +  Helper::ultos(stage) + " ...");
	m_channelManager->deleteChannels (stage);	
	logging_debug( "unloading stage " + Helper::ultos(stage) + " done");

	return true;
}

bool ModuleManager::startFrameEating (FrameBuffer* framebuffer)
{
	m_frameDistribution->setFrameBuffer		(framebuffer);
	m_frameDistribution->setChannelManager	(m_channelManager);
	
#ifdef OMNET_SIMULATION
	return true;
#else
	return m_frameDistribution->startDistribution ();
#endif
}

bool ModuleManager::stopFrameEating ()
{
#ifdef OMNET_SIMULATION
	return true;
#else
	return m_frameDistribution->stopDistribution ();
#endif
}

MessagingSystem* ModuleManager::getMessagingSystem ()
{
	return m_messagingSystem;
}

FrameDistribution* ModuleManager::getFrameDistribution ()
{
	return m_frameDistribution;
}

void ModuleManager::receiveMessage (Message* msg)
{
	if (msg->getType() == Message::MESSAGE_TYPE_ALERT) {
		
		// TODO: should wait here somehow. or reinject the message
		// and execute it later when we are in the progress
		// of updating the stages. but waiting must be async!! do not block here!!!!

		if (m_stageUpdateInProgress) return;

		//
		// check from which stage the alert came and if some general invariants are correct.
		//

		MessageAlert* alertmsg = (MessageAlert*) msg;

		if (m_currentStageLevel < m_lowestStageLevel) return;
		if (alertmsg->getAlertModuleStage() < m_lowestStageLevel) return;
		if (alertmsg->getAlertModuleStage() > m_currentStageLevel) return;;

		// THOMAS: Beim Laden wird nicht beachtet, dass unterschiedliche Aggregate sich in unterschiedlichen Zustaenden befinden koennen

		//
		// loading or unloading stages _must_ be done asyncronously because
		// the nodes will register/unregister from the messaging system
		// and the call we are in right now comes from the messaging system.
		// Doing this syncronously will deadlock in a messaging system function.
		//
		// but we only do this async under a real live system. under omnet there
		// are reasons to do this sync due to timer registration issues!
		//

		m_stageUpdateInProgress = true;
		logging_info( "(un)loading channel with reason: " + alertmsg->getAlertMessage());		
		logging_info( "alerting stage: " + Helper::ultos(alertmsg->getAlertModuleStage()));

#ifdef OMNET_SIMULATION

	ModuleManager::updateStageThreadFunc (this, alertmsg->getAlertType(), alertmsg->getAlertModuleStage());

#else

		if (m_stageUpdateThread != NULL) {
			m_stageUpdateThread->join ();
			delete m_stageUpdateThread;
			m_stageUpdateThread = NULL;
		}

		m_stageUpdateThread = new boost::thread (boost::bind (&ModuleManager::updateStageThreadFunc, this, alertmsg->getAlertType(), alertmsg->getAlertModuleStage()));
#endif

	}
}

void ModuleManager::updateStageThreadFunc (ModuleManager* obj, MessageAlert::ALERT_TYPE type, unsigned short alertingStage)
{ 
	//
	// try to load/unload the new stage. If the loading fails
	// maybe there is no such stage defined
	//

	unsigned short& currentLevel	= obj->m_currentStageLevel;
	bool			success			= false;

	//
	// load/unload the stage with their channel(s)
	//

	if (type == MessageAlert::ALERT_TYPE_RAISE_LEVEL) {
	        if (alertingStage == currentLevel) {
		        success = obj->loadStage (currentLevel + 1);
			if (success)
			        currentLevel += 1;
		}

	//THOMAS: Hier sollte die aufrufende Stage gleich entladen werden um sicherzustellen, dass immer nur die Basisstufe und die aktuell hoechste Stufe geladen sind

	} else if (type == MessageAlert::ALERT_TYPE_LOWER_LEVEL) {
	        if (alertingStage == obj->m_lowestStageLevel) {
		        // if basic stage detected end of attack, unload all higher stages
			success = obj->unloadStage (alertingStage + 1);
			if (success)
			  currentLevel = alertingStage;
		} else { 
			success = obj->unloadStage (alertingStage);
			if (success)
			        currentLevel = alertingStage - 1;
		}
			
	} else 
		assert (false);

	obj->m_stageUpdateInProgress = false;
}

#ifdef OMNET_SIMULATION

void ModuleManager::setDistackModule (DistackOmnetModule* module)
{
	distackModule = module;
	m_channelManager->setDistackModule (module);
}

#endif // OMNET_SIMULATION
