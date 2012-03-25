#include "Channel.h"

#include "Distack.h"
#include "base/module/Module.h"
#include "base/common/Timer.h"

Channel::Channel (string name, unsigned short stage, DistackInfo* info)
:	m_name				(name),
	m_stage				(stage),
	m_messagingSystem	(NULL)
{
	distackInfo = info;
#ifdef OMNET_SIMULATION
	distackModule = NULL;	
#endif // OMNET_SIMULATION
}

Channel::~Channel ()
{
	MODULE_VECTOR_ITERATOR i	= m_modules.begin	();
	MODULE_VECTOR_ITERATOR iend = m_modules.end		();		

	for ( ; i != iend; i++) {
		
		delete *i;

	} // for ( ; i != iend; i++)

	m_modules.clear ();
}

Module* Channel::addModule (ModuleConfiguration config)
{
	//
	// fill out the stage in the config list, 
	// only we know which stage we are on
	//

	config.stage = getStage ();

	//
	// create the module with the given parameters
	//

#ifdef OMNET_SIMULATION
	Module* module = new Module (config, distackModule, distackInfo);
#else
	Module* module = new Module (config, distackInfo);
#endif // OMNET_SIMULATION
	
	m_modules.push_back (module);

	return module;
}

void Channel::frameCall (Frame& frame)
{
	//
	// push the frame into the modules until 
	// one module tells us to stop pushing it further
	//

	MODULE_VECTOR_ITERATOR	i		 = m_modules.begin	();
	MODULE_VECTOR_ITERATOR	iend	 = m_modules.end	();		
	bool					cont	 = true;

	for ( ; i!=iend && cont; i++)
		cont &= (*i)->frameCall (frame);
}

string Channel::getName ()
{
	return m_name;
}

unsigned short Channel::getStage ()
{
	return m_stage;
}

bool Channel::startup (MODULE_CONFIGURATION_LIST config, MessagingSystem& msgsystem)
{
	logging_debug( "starting up channel " + m_name + " ...");
	m_messagingSystem = &msgsystem;

	//
	// put all the modules according to their configuration on to the channel
	//

	bool							   ret	= true;
	MODULE_CONFIGURATION_LIST_ITERATOR i	= config.begin ();
	MODULE_CONFIGURATION_LIST_ITERATOR iend	= config.end   ();

	for ( ; i != iend; i++) {

		Module* module = addModule( *i );

		//
		// configure the messaging system for the node
		//
		
		MessagingNode* messenger = dynamic_cast<MessagingNode*> (module->getInternal());
		
		if (messenger != NULL) {
		
			//
			// register the signals for the messaging system
			//

			logging_debug( "configuring messaging for module " + module->getName() );
			messenger->configure(
				boost::bind( &MessagingSystem::sendMessage, &msgsystem, _1, _2 ),
				boost::bind (&MessagingSystem::subscribe, &msgsystem, _1, _2),
				boost::bind (&MessagingSystem::unsubscribe, &msgsystem, _1, _2),
				boost::bind (&MessagingSystem::unsubscribeAll, &msgsystem, _1)
				);
		
			//
			// now the node can subcribe to its needed message types
			//

			logging_debug( "telling module " + module->getName() + " to register its messages");
			messenger->registerMessages	();
		
		} // if (messenger != NULL)

		ret &= module->good ();	
		if (! ret) {
			logging_error( "failed configuring module " + module->getName ());
			break;
		}

	} // for ( ; i != iend; i++)
	
	logging_debug( "channel " + m_name + " started up " + (ret ? "successfully" : "with errors"));
	return ret;
}

bool Channel::shutdown ()
{
	Channel::MODULE_VECTOR_ITERATOR i	 = m_modules.begin  ();
	Channel::MODULE_VECTOR_ITERATOR iend = m_modules.end	();

	for ( ; i != iend; i++) {
	
		MessagingNode* messenger = dynamic_cast<MessagingNode*> ((*i)->getInternal());
		if (messenger != NULL) m_messagingSystem->unsubscribeAll (messenger);
	
		delete *i;
	}

	m_modules.clear ();

	return true;
}

#ifdef OMNET_SIMULATION

void Channel::setDistackModule (DistackOmnetModule* module)
{
	distackModule = module;
}

#endif // OMNET_SIMULATION
