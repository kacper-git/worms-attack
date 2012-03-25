#include "Distack.h"

//************************************************

#ifndef OMNET_SIMULATION

/**
  *  The main() function for use with the pcap interface.
  */
int main (int argc, char* argv[])
{
	string configfile;
	string path("single");
	
	if (argc == 1) {
		
		#ifdef WIN32
			#ifdef _DEBUG
				configfile = "..\\..\\etc\\distack-settings.xml";
			#else
				configfile = "settings.xml";
			#endif
		#else
			configfile = "./distack-settings.xml";
		#endif

	} else if (argc == 2) {
		configfile = argv[1];
	} else {
		cout << "Invalid parameters" << std::endl;	
		cout << "Usage: distack <xml configuration file>" << std::endl;
		return false;
	} 

	cout 	<< "-------------------\\" << std::endl
		<< "Distack v" << VERSION << " --- distributed attack detection ---" << std::endl
		<< "-------------------/" << std::endl;

	DistackInfo dInfo( 0, configfile, path );
	Distack distack (&dInfo);

	if (distack.startup ()) {
		getchar();
		distack.shutdown ();
	}

	cout << "Distack has shut down, press <enter> to exit" << std::endl;
	getchar ();

	return 0;
}

#endif // OMNET_SIMULATION

//************************************************

#ifdef OMNET_SIMULATION

int DistackOmnetModule::GLOBAL_ID = 0;

/**
 * Constructor
 */
DistackOmnetModule::DistackOmnetModule ()
	: omnetInterface( NULL ), distackInfo( NULL ), 
	distack( NULL ), doShutdown( false )
{
}

/**
 * Destructor
 */
DistackOmnetModule::~DistackOmnetModule ()
{
	if (distack != NULL) {
		distack->shutdown ();
		delete distack;
	}
}

/**
  *  used by Omnet++ to determine the number of stages for a multi stage init. Reimplemented from cSimpleModule.
  * @return the number of stages
  */
int DistackOmnetModule::numInitStages () const
{
	return 7;
}

/**
  * called by Omnet++ during initialization: creates a Distack instance and sets up instance parameters and the network interface.
  * if the assinged configId parameter consists of a single space character, distack is not started for this module
  * @param stage the current stage of the multi stage initialize
  * @see DistackInfo
  * @see numInitStages()
  */
void DistackOmnetModule::initialize (int stage)
{
	if (doShutdown) return;

	if (stage == 0) {

		int tempid( DistackOmnetModule::GLOBAL_ID++ );
		string tempconf( par("configId").stringValue() );
		string temppath = getFullPath();
		temppath.erase(temppath.find(".distack"));

		if (tempconf == " ") {
			doShutdown = true;
			cout << "libdistack init INFO: " << temppath << 
				": configId was empty, shutting down." << endl;
			return;
		}

		distackInfo = new DistackInfo( tempid, tempconf, temppath );
		distack = new Distack( distackInfo );
		return;

	} else if (stage == 3) {

		distack->setDistackModule( this );
		distack->startup();
		distack->getModuleManager()->getMessagingSystem()->getRemoteSystem()->getCommSystem()->init(stage);

		NetworkInterface* iface	= distack->getNetworkManager()->getNetworkInterface ();
		omnetInterface = dynamic_cast<NetworkInterfaceOmnetpp*>(iface);
		assert( omnetInterface != NULL );
		omnetInterface->setDistackModule( this );

		string loctest(setlocale(LC_NUMERIC, NULL));
		if(loctest != "en_US.UTF-8") {
			bool result = setlocale(LC_NUMERIC, "en_US.UTF-8");
			if(!result) 
				cout << "libdistack init WARNING: could not change " <<
					"locale settings, simulation may crash" << endl;
		}

	} else if (stage > 3 && stage < 7) {

		distack->getModuleManager()->getMessagingSystem()->
			getRemoteSystem()->getCommSystem()->init(stage);

	}
}

/**
  * called from Omnet++ during simulation: called when the module receives a message
  * @param msg the cMessage object arriving at the module
  */
void DistackOmnetModule::handleMessage	(cMessage* msg)
{
	if (doShutdown) {
		if (getParentModule()->getSubmodule("networkLayer")->getSubmodule("ip")->par("copyFlag").boolValue()) {
			getParentModule()->getSubmodule("networkLayer")->getSubmodule("ip")->par("copyFlag").setBoolValue(false);
		}
		if (msg->isSelfMessage ()) {
			cancelAndDelete(msg);
		} else {
			delete msg;
		}
		return;
	}

	string loctest(setlocale(LC_NUMERIC, NULL));
	if(loctest != "en_US.UTF-8") {
		bool result = setlocale(LC_NUMERIC, "en_US.UTF-8");
		if(!result) cout << "libdistack WARNING: could not change " <<
			"locale settings, simulation may crash" << endl;
	}

	if (msg->isSelfMessage ()) {

		if (strstr(msg->getName(), "DistackTimer") != 0) {
	
			//
			// handle timer message (self-messages)
			//
	
			boost::mutex::scoped_lock scopedLock (timerListMutex);
			
			OMNET_TIMER_LIST_ITERATOR i	   = timerList.begin ();
			OMNET_TIMER_LIST_ITERATOR iend = timerList.end   ();
	
			//
			// inject the timer message to each registered
			// timer. the timer which matches the id will return true
			//
				
			for ( ; i != iend; i++) {
				
				if ((*i)->getTimerId () == msg->getKind()) {
					if ((*i)->receiveMessage(msg) == true) 
						break;
				}
	
			} // for ( ; i != iend; i++)

		} else {
				cout << "libdistack WARNING: discarding unhandled selfmessage with name " 
					<< msg->getName() << " kind " << msg->getKind() << endl;
				cancelAndDelete(msg);
		}

	} else {

		//
		// handle network messages
		//
		// if message is no cPacket, fail
		cPacket* packet = check_and_cast<cPacket*>(msg);

		if (packet->getArrivalGate()->isName("in")) {

			if (omnetInterface != NULL) {
			omnetInterface->handleMessage (packet);
				delete packet;
			}

		} else if (packet->getArrivalGate()->isName("sigIn")) {

			if (strstr(packet->getName(), "ICMP-error")) {
				logging_warn( "recieved ICMP error on sigIn gate, most likely tried to send to malformed or non-existing IP address");
				delete packet;
			} else {
				distack->getModuleManager()->getMessagingSystem()->
					getRemoteSystem()->getCommSystem()->handleMessage(packet);
			}
		}
		else {
			// if we end up here, something went horribly wrong
			cout << "WARNING: discarding unhandled message with name " << 
				packet->getName() << " kind " << packet->getKind() << " on arrivalgate " << 
				(packet->getArrivalGate() ? packet->getArrivalGate()->getName() : "no gate") << endl;
			delete packet;
		}
	}

	//
	// flush the messaging system. otherwise it does not
	// get enough CPU under an OMNET_SIMULATION and will
	// not deliver the messages in a timely fashion
	//

	distack->getModuleManager()->getMessagingSystem()->flush();
}

/**
  *  called from Omnet++ during simulation: called when the simulation terminates. Can be used for writing statistics and the likes.
  */
void DistackOmnetModule::finish ()
{
}

/**
  *  registers a self-message timer to this module
  * @param timer the Timer object to be registered with this module
  * @see Timer
  */
void DistackOmnetModule::registerTimer (Timer* timer)
{
	//
	// if the timer is not yet in the list, register it
	//

	boost::mutex::scoped_lock scopedLock (timerListMutex);
	OMNET_TIMER_LIST_ITERATOR item = find (timerList.begin(), timerList.end(), timer);

	if (item == timerList.end()) {
		timerList.push_back		(timer);
		timer->setDistackModule (this);
	}
}

/**
  *  unregisters a self-message timer to this module
  * @param timer the Timer object to be unregistered with this module
  * @see Timer
  */
void DistackOmnetModule::unregisterTimer (Timer* timer)
{
	//
	// if the timer is registered, unregister it
	//

	boost::mutex::scoped_lock scopedLock (timerListMutex);
	OMNET_TIMER_LIST_ITERATOR item = find (timerList.begin(), timerList.end(), timer);

	if (item != timerList.end()) {
		timer->setDistackModule (NULL);
		timerList.erase (item);
	}
}

/**
  *  creates a new cMessage object for a specific timer.
  * @param timerid the timerid of the corresponding Timer object
  * @param name the name of the timer (e.g. "AnalyzerProtocolAnomaly")
  * @see Timer
  * @return the created cMessage object
  */
cMessage* DistackOmnetModule::createTimerMsg (int timerid, string name)
{
	boost::mutex::scoped_lock scopedLock (sendMsgMutex);

	cMessage* scheduledMessage = new cMessage (name.length()>0 ? name.c_str() : "DistackTimer");
	scheduledMessage->setKind (timerid);

	return scheduledMessage;
}

/**
  *  schedules a self-message timer with Omnet++
  * @param tm the time (in simulation time) at which the self-message is supposed to arrive back at the module
  * @param msg the message object to be scheduled
  * @see Timer
  */
void DistackOmnetModule::scheduleTimerMsg (simtime_t tm, cMessage* msg)
{
	boost::mutex::scoped_lock scopedLock (sendMsgMutex);
	scheduleAt (tm, msg);
}

Distack* DistackOmnetModule::getDistack ()
{
	return distack;
}

#endif // OMNET_SIMULATION

//************************************************

/**
  *  sets up Configuration and Log
  * @param info the startup parameters
  * @see DistackInfo
  * @see Configuration
  * @see Log
  */
Distack::Distack (DistackInfo* info)
:	distackInfo(info),
	m_logoutputter(NULL)
{
#if (defined (_DEBUG) & defined (_MSC_VER))
	//
	// switch on memory debugging when debugging with msvc
	//
	////_crtBreakAlloc = 18687;
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF );
#endif 

	Configuration::init (distackInfo);
	Log::init (distackInfo);
}

Distack::~Distack ()
{
}

#ifdef OMNET_SIMULATION
void Distack::setDistackModule (DistackOmnetModule* module)
{
	distackModule = module;
}
#endif

/**
  *  starts up the Distack system. Logging is set, NetworkManager and ModuleManager instances are created and their respective startup functions called
  * @see NetworkManager
  * @see ModuleManager
  * @see FrameDistribution
  * @see Log
  */
bool Distack::startup ()
{	
	//
	// configure log outputting
	//

	LogLevel::LOG_LEVEL logLevel = Configuration::instance(distackInfo)->getLogLevel();
	string logType = Configuration::instance(distackInfo)->getLogType();

	if (m_logoutputter == NULL) {

		if(logType == "stdout") {

			m_logoutputter = new StdOutLogOutputter ();
			Log::instance(distackInfo)->addLogOutput(m_logoutputter);
			Log::instance(distackInfo)->setLogLevel(logLevel);

		} else if(logType == "file") {
#ifdef OMNET_SIMULATION
			char temp[8];
			sprintf(temp, "%d", distackInfo->distackId);
			string fname("distacklog_config-" + string(temp) + "_" + distackInfo->modulePath);
#else
			char temp[8];
			sprintf(temp, "%d", distackInfo->distackId);
			string fname("distacklog_config-" + string(temp));
#endif
			m_logoutputter = new FileLogOutputter(fname);
			Log::instance(distackInfo)->addLogOutput(m_logoutputter);
			Log::instance(distackInfo)->setLogLevel(logLevel);

		} else if(logType == "none") {
			Log::instance(distackInfo)->setLogLevel(LogLevel::TYPE_ERROR);
		} else {
			//if we reach this, configuration is bad
			//do not log
			cout << "WARNING: logging not correctly configured, unknown logtype: " 
				<< logType << std::endl;
		}
		
	}
	
	//
	// startup all the stuff
	//

	m_networkmanager = new NetworkManager( distackInfo );
	m_modulemanager  = new ModuleManager( distackInfo );

#ifdef OMNET_SIMULATION
	m_modulemanager->setDistackModule( distackModule );
#endif

	bool ret = true;

	ret &= m_networkmanager->startup();
	if (! ret) return false;

	//
	// start up the module manager and load the initial stage
	//

	m_modulemanager->startup();

	//
	// start eating frames ...
	//

#ifdef OMNET_SIMULATION
	m_modulemanager->getMessagingSystem()->getRemoteSystem()->
		getCommSystem()->setDistackModule (distackModule);

	m_modulemanager->setDistackModule (distackModule);
	NetworkInterfaceOmnetpp* omnetiface = (NetworkInterfaceOmnetpp*)m_networkmanager->getNetworkInterface();
	omnetiface->setFrameDistribution( m_modulemanager->getFrameDistribution() );
#endif

	ret &= m_modulemanager->startFrameEating (m_networkmanager->getFrameSource ());
	if (! ret) return false;
	
	return ret;
}

bool Distack::shutdown ()
{
	bool ret = true;

	ret &= m_modulemanager->stopFrameEating();
	ret &= m_networkmanager->shutdown();
	
	delete m_networkmanager;
	delete m_modulemanager;

	if (m_logoutputter != NULL) {
		Log::instance(distackInfo)->removeLogOutput( m_logoutputter );
		delete m_logoutputter;
		m_logoutputter = NULL;
	}
	
	Configuration::cleanup( distackInfo );
	Log::cleanup( distackInfo );
	//delete distackInfo; // TODO: crashes with this delete

	return ret;
}

NetworkManager*	Distack::getNetworkManager ()
{
	return m_networkmanager;
}

ModuleManager* Distack::getModuleManager ()
{
	return m_modulemanager;
}

//************************************************
