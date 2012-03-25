#include "NetworkManager.h"

NetworkManager::NetworkManager(DistackInfo* info)
	: distackInfo( info ),
	  m_frameBuffer( NULL ){
}

NetworkManager::~NetworkManager(){
}

bool NetworkManager::startup()
{
	logging_debug( "network manager is starting up ..." );

	//
	// get network configuration parameters
	//

	Configuration::NETWORK_TRACE_SOURCE source =
		Configuration::instance(distackInfo)->getFrameSourceType();

#ifdef OMNET_SIMULATION 
	source = Configuration::NETWORK_TRACE_SOURCE_INTERFACE;
#else
	if(source == Configuration::NETWORK_TRACE_SOURCE_UNDEFINED){
		logging_error( "undefined network frame source" );
		return false;
	}
#endif

	bool ret = true;
	string iface = Configuration::instance(distackInfo)->getNetworkInterface();
	string tracefile = Configuration::instance(distackInfo)->getTraceFile();
	bool promisc = Configuration::instance(distackInfo)->getNetworkPromiscuous();
	unsigned int captureLen = Configuration::instance(distackInfo)->getNetworkCaptureLen();

	//
	// create and open the network interface
	//

	logging_debug( "creating interface ..." );

	if( source == Configuration::NETWORK_TRACE_SOURCE_INTERFACE ){

#ifdef OMNET_SIMULATION
		m_interface = new NetworkInterfaceOmnetpp( distackInfo );
		logging_debug( "omnetpp interface created");
#else
		m_interface = new NetworkInterfacePcap( distackInfo, iface, promisc, captureLen );
		logging_debug( "online interface created" );
#endif

	}else if( source == Configuration::NETWORK_TRACE_SOURCE_TRACEFILE ){
	
#ifdef OMNET_SIMULATION
		logging_error( "can not use offline source in Omnet simulation" );
		return false;
#else
		double speedup = Configuration::instance(distackInfo)->getTraceReplaySpeedup();
		m_interface = new NetworkInterfacePcap( distackInfo, tracefile, speedup );
		logging_debug( "offline interface created" );
#endif

	} else {
		assert( false );
		return false;
	}

	logging_debug( "opening interface ..." );
	ret = m_interface->open();
	if(! ret ){
		logging_error( "opening interface " + iface + " failed" );
		return false;
	}

#ifndef OMNET_SIMULATION
	//
	// create the frame-buffer and set it on top of the network interface
	//

	logging_debug( "creating frame-buffer ..." );

	m_frameBuffer = new FrameBuffer( *m_interface, distackInfo );

	unsigned int maxFrames = Configuration::instance(distackInfo)->getQueueMaxFrames();
	unsigned int maxBytes = Configuration::instance(distackInfo)->getQueueMaxBytes();
	m_frameBuffer->setMaxFrames( maxFrames );
	m_frameBuffer->setMaxBytes( maxBytes );

	m_frameBuffer->startup();
#endif

	return true;
}

bool NetworkManager::shutdown()
{
	logging_debug( "network manager is shutting down ...");

	if( m_frameBuffer != NULL ) 
		m_frameBuffer->prepareshutdown();

	logging_debug( "---1");
	m_interface->close();
	logging_debug( "done1");

	logging_debug( "---2");
	if( m_frameBuffer != NULL ){
		delete m_frameBuffer;
		m_frameBuffer = NULL;
	}
	logging_debug( "done2");

	logging_debug( "---3");
	delete m_interface;
	logging_debug( "done3");

	logging_debug( "network manager has been shut down" );
	return true;
}

FrameBuffer* NetworkManager::getFrameSource()
{
	return m_frameBuffer;
}

NetworkInterface* NetworkManager::getNetworkInterface()
{
	return m_interface;
}
