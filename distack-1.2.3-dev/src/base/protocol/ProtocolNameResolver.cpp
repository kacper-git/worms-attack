#include "ProtocolNameResolver.h"
#include "Packet.h" // circular inclusion

ProtocolNameResolver* ProtocolNameResolver::object  = NULL;

ProtocolNameResolver* ProtocolNameResolver::instance ()
{
	static Guard guard;

	if (object == NULL)
		object  = new ProtocolNameResolver ();
	
	return object;
}

ProtocolNameResolver::ProtocolNameResolver ()
{
	protocolNameMap.clear ();

	protocolNameMap.insert (PROTOCOL_NAME_PAIR (Packet::PROTO_NONE,			"None"		));
	protocolNameMap.insert (PROTOCOL_NAME_PAIR (Packet::PROTO_DATA_PAYLOAD,	"Payload"	));
	protocolNameMap.insert (PROTOCOL_NAME_PAIR (Packet::PROTO_ETHERNET,		"Ethernet"	));
	protocolNameMap.insert (PROTOCOL_NAME_PAIR (Packet::PROTO_MPLS,			"MPLS"		));
	protocolNameMap.insert (PROTOCOL_NAME_PAIR (Packet::PROTO_ARP,			"ARP"		));
	protocolNameMap.insert (PROTOCOL_NAME_PAIR (Packet::PROTO_IP,			"IPv4"		));
	protocolNameMap.insert (PROTOCOL_NAME_PAIR (Packet::PROTO_IPV6,			"IPv6"		));
	protocolNameMap.insert (PROTOCOL_NAME_PAIR (Packet::PROTO_TCP,			"TCP"		));
	protocolNameMap.insert (PROTOCOL_NAME_PAIR (Packet::PROTO_UDP,			"UDP"		));
	protocolNameMap.insert (PROTOCOL_NAME_PAIR (Packet::PROTO_ICMP,			"ICMP"		));
	protocolNameMap.insert (PROTOCOL_NAME_PAIR (Packet::PROTO_MAXIMUM,		"Maximum"	));
}

ProtocolNameResolver::~ProtocolNameResolver	()
{
	protocolNameMap.clear ();
}
	
string ProtocolNameResolver::getName (int id)
{
	PROTOCOL_NAME_MAP_ITERATOR it = protocolNameMap.find (id);
	if (it == protocolNameMap.end())	return "unknown";
	else								return it->second;
}

int ProtocolNameResolver::getId	(string name)
{
	PROTOCOL_NAME_MAP_ITERATOR i	= protocolNameMap.begin ();
	PROTOCOL_NAME_MAP_ITERATOR iend = protocolNameMap.end	();

	for ( ; i != iend; i++) {
		if (i->second.compare (name) == 0) return i->first;
	}

	return Packet::PROTO_NONE;
}
