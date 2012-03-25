#include "ModuleFilterProtocol.h"

MODULE_INTERFACE(ModuleFilterProtocol);

const string ModuleFilterProtocol::PARAM_Protocol = "Protocol";
const string ModuleFilterProtocol::PARAM_Inverse  = "Inverse";

ModuleFilterProtocol::ModuleFilterProtocol ()
{
}

ModuleFilterProtocol::~ModuleFilterProtocol ()
{
}

bool ModuleFilterProtocol::configure (ModuleConfiguration& configList)
{
	bool good = true;
	good &= configList.has (PARAM_Protocol);
	good &= configList.has (PARAM_Inverse);

	if (good) {
		m_param_Protocol = (Packet::PROTOCOL) ProtocolNameResolver::instance()->getId (configList.get(PARAM_Protocol));
		if (Packet::PROTO_NONE) good = false;
		m_param_Inverse = (configList.getLong (PARAM_Inverse) == 1 ? true : false);
	}

	return good;
}

bool ModuleFilterProtocol::frameCall (Frame& frame)
{
	frame.parsePackets ();

	//
	// if we apply a non-inverse filter, we filter all packets witch contain the given protocol 
	// in case of an inverse filter, only packets which do not contain the specified protocol are regarded
	//

	for (Packet* packet=frame.payloadpacket; packet != NULL; packet=packet->getNextPacket()) {

		if ((packet->getProtocol() == m_param_Protocol)  ^ m_param_Inverse) return true;

	}

	return false;
}
