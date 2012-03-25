#include "ModuleFilterSubnet.h"

MODULE_INTERFACE(ModuleFilterSubnet);

const string ModuleFilterSubnet::PARAM_Address		= "Address";
const string ModuleFilterSubnet::PARAM_SubnetMask	= "SubnetMask";
const string ModuleFilterSubnet::PARAM_Inverse		= "Inverse";

ModuleFilterSubnet::ModuleFilterSubnet()
{
}

ModuleFilterSubnet::~ModuleFilterSubnet()
{
}

bool ModuleFilterSubnet::configure (ModuleConfiguration& configList)
{
	bool good = true;
	good &= configList.has (PARAM_Address);
	good &= configList.has (PARAM_SubnetMask);
	good &= configList.has (PARAM_Inverse);

	if (good) {
		good &= m_param_Address.fromString (configList.get(PARAM_Address));
		good &= m_param_SubnetMask.fromString   (configList.get(PARAM_SubnetMask));
		m_param_Inverse = (configList.getLong (PARAM_Inverse) == 1 ? true : false);
	}

	return good;
}

bool ModuleFilterSubnet::frameCall (Frame& frame)
{
	frame.parsePackets ();

	//
	// find first IP packet
	//

	IpPacket* ipPacket = NULL;

	for (Packet* packet=frame.payloadpacket; packet != NULL; packet=packet->getNextPacket()) {
		if (packet->getProtocol() == Packet::PROTO_IP) {
			
			ipPacket = (IpPacket*) packet;

		}
	}

	if (ipPacket == NULL) return m_param_Inverse;

	//
	// check the source and destination of the packet
	// if either source _or_ destination match, this is fine
	//

	IP_ADDR source = ipPacket->getSourceip ();
	IP_ADDR dest   = ipPacket->getDestip   ();

	return (matches(source) || matches(dest));
}

bool ModuleFilterSubnet::matches (IP_ADDR addr)
{
	//
	// check if addr is in the subnet regarding to mask
	//

	bool inSubnet = ((addr & m_param_SubnetMask) == (m_param_Address & m_param_SubnetMask));

	//
	// return value in respect to the positive/negative filter
	//

	return (inSubnet ^ m_param_Inverse);
}
