#include "Module.h"

#include "Distack.h"
#include "base/module/DistackModuleInterface.h"
#include "base/common/DistackInfo.h"
#include "base/protocol/PacketFactory.h"
#include "base/common/Timer.h"

unsigned long Module::ID_COUNTER = 0;
DynamicLibrary::SEARCH_PATHES Module::m_libraryPaths;

#ifdef OMNET_SIMULATION
Module::Module ( ModuleConfiguration config, DistackOmnetModule* omnetModule, DistackInfo* info )
#else
Module::Module ( ModuleConfiguration config, DistackInfo* info )
#endif // OMNET_SIMULATION
:	m_name			(config.name),
	m_library		(config.library, info, m_libraryPaths),
	m_internal		(NULL),
	distackInfo		(info)
{
#ifdef OMNET_SIMULATION
	m_distackModule = omnetModule;	
#endif // OMNET_SIMULATION

	//
	// init the module library by calling its create-function
	//

	m_internal = m_library.functionCall<DistackModuleInterface*,unsigned int> 
					(MODULE_INTERFACE_ENTRYFUNCTION, ID_COUNTER++);

	goodstate = (m_internal != NULL);
	
	logging_debug( "loading module library " + config.library + " " + 
			(goodstate ? "succeeded" : "failed"));

	if (m_internal != NULL) {

		m_internal->distackInfo = distackInfo;
	
#ifdef OMNET_SIMULATION

		//
		// configure the timers for the node in OMNET_SIMULATION
		// 
		
		Timer* timer = dynamic_cast<Timer*> (m_internal);
		if (timer != NULL)
			m_distackModule->registerTimer (timer);

		//
		// set the DistackModuleInterface distackModule, so that
		// the modules can access the omnet module
		//

		m_internal->omnetModule = m_distackModule;
		timer->setDistackModule (m_distackModule);

#endif // OMNET_SIMULATION

		//
		// configure the module with the stuff from the xml config file
		//

		goodstate &= m_internal->configure (config);

		//
		// if the module needs some packet parsing capabilities then 
		// we configure its PacketFactory to the global factory
		//

		m_library.functionCall<int,PacketFactory*> 
			(MODULE_INTERFACE_INIT_PACKETFACTORY, PacketFactory::instance ());

		//
		// if the module wants logging, configure it
		//

		m_library.functionCall<int,Log*> 
			(MODULE_INTERFACE_INIT_LOGGING, Log::instance(distackInfo));
	
	} // if (m_internal != NULL)
}

Module::~Module ()
{
#ifdef OMNET_SIMULATION
	Timer* timer = dynamic_cast<Timer*> (m_internal);
	if (timer != NULL)
		m_distackModule->unregisterTimer (timer);
#endif // OMNET_SIMULATION

	delete m_internal;
}

void Module::setLibrarySearchPaths (DynamicLibrary::SEARCH_PATHES pathes)
{
	m_libraryPaths = pathes;
}

void Module::setName (string name)
{
	m_name = name;
}

string Module::getName ()
{
	return m_name;
}

bool Module::good ()
{
	return goodstate;
}

bool Module::frameCall (Frame& frame)
{	
	return m_internal->frameCall (frame);
}

DistackModuleInterface* Module::getInternal ()
{
	return m_internal;
}
