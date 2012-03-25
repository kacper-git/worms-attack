#include "RemoteCommSystem.h"
#include "RemoteMessagingSystem.h"

RemoteCommSystem::RemoteCommSystem (string name, string description, DistackInfo* info)
	: distackInfo( info ), m_name( name ), m_description( description ) {
}

RemoteCommSystem::~RemoteCommSystem ()
{
}

void RemoteCommSystem::setMessagingSystem (RemoteMessagingSystem* system)
{
	m_messagingSystem = system;
}

void RemoteCommSystem::read (DISTACK_REMOTE_DATA data)
{
	m_messagingSystem->receiveBytes (data);
}

string RemoteCommSystem::getName ()
{
	return m_name;
}

string RemoteCommSystem::getDescription ()
{
	return m_description;
}

#ifdef OMNET_SIMULATION
void RemoteCommSystem::setDistackModule (DistackOmnetModule* module)
{
	distackModule = module;
}
#endif // OMNET_SIMULATION
