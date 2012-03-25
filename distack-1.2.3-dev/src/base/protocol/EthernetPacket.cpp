#include "EthernetPacket.h"

EthernetPacket::EthernetPacket(void)
{
	protocol	= Packet::PROTO_ETHERNET;
	memset		(&header, 0, sizeof (ETHERNET_HEADER));
}

EthernetPacket::~EthernetPacket(void)
{
}

bool EthernetPacket::parsePacket()
{
	if (buffer == NULL) return false;

	if ((unsigned int)size < sizeof (ETHERNET_HEADER)) {
		cout << "packet too small to contain ethernet header (" << size << "bytes)" << std::endl;
		return false;
	}

	memcpy (&header, buffer, sizeof (ETHERNET_HEADER));
	header.type = swap16 (header.type);

	switch (header.type) {
		case ETHERTYPE_IP:				nextProtocol = Packet::PROTO_IP;	break;
		case ETHERTYPE_ARP:				nextProtocol = Packet::PROTO_ARP;	break;
		case ETHERTYPE_IPV6:			nextProtocol = Packet::PROTO_IPV6;	break;
		case ETHERTYPE_MPLS:			nextProtocol = Packet::PROTO_MPLS;	break;
		case ETHERTYPE_MPLS_MULTICAST:	nextProtocol = Packet::PROTO_MPLS;	break;
		case ETHERTYPE_UNKNOWN:	nextProtocol = Packet::PROTO_DATA_PAYLOAD;	break;
	}

	layersize	= sizeof (ETHERNET_HEADER);

	return true;
}

MAC_ADDR EthernetPacket::getSourceMac ()
{
	MAC_ADDR ret = {{0}};
	memcpy (&ret, &header.sourcehost, ETHER_ADDR_LEN);
	return ret;
}

MAC_ADDR EthernetPacket::getDestMac ()
{
	MAC_ADDR ret = {{0}};
	memcpy (&ret, &header.desthost, ETHER_ADDR_LEN);
	return ret;
}

unsigned short EthernetPacket::getType ()
{	
	return header.type;
}

void EthernetPacket::setSourceMac (MAC_ADDR mac)
{
	memcpy (&header.sourcehost, &mac, ETHER_ADDR_LEN);
}

void EthernetPacket::setDestMac	(MAC_ADDR mac)
{
	memcpy (&header.desthost, &mac, ETHER_ADDR_LEN);
}

void EthernetPacket::setType (unsigned short tp)
{
	header.type = tp;
}

string EthernetPacket::toString	()
{
	ostringstream out;
	
	out << "Ethernet packet"	<< std::endl
		<< "\tsource mac: \t"	<< getSourceMac ().toString ()	<< std::endl
		<< "\tdest mac: \t"		<< getDestMac   ().toString ()	<< std::endl
		<< "\ttype: \t\t0x"		<< std::hex << std::setw (4) << std::setfill ('0') << getType		();

	return out.str ();
}

unsigned int EthernetPacket::getMinProtocolSize ()
{
	return sizeof (ETHERNET_HEADER);
}





