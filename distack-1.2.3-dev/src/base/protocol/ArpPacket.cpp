#include "ArpPacket.h"
		
ArpPacket::ArpPacket ()
{
	memset 			(&header, 0, sizeof (ARP_HEADER));
	checksumgood 	= true;
	protocol		= Packet::PROTO_ARP;
	layersize		= sizeof (ARP_HEADER);
}

ArpPacket::~ArpPacket ()
{	
}

bool ArpPacket::parsePacket ()
{
	memcpy (&header, buffer, sizeof (ARP_HEADER));

	header.hardwaretype = swap16 (header.hardwaretype);
	header.protocoltype = swap16 (header.protocoltype);
	header.opcode		= swap16 (header.opcode);

	nextProtocol = Packet::PROTO_NONE;
	layersize = sizeof (ARP_HEADER);

	return true;
}

string ArpPacket::toString ()
{
	ostringstream out;

	out << "ARP packet"													<< std::endl
		<< "\thardware type: 0x\t"		<< std::hex << std::setw (4) << std::setfill ('0') << header.hardwaretype	<< std::endl << std::dec
		<< "\tprotocol type: \t"		<< std::hex << std::setw (4) << std::setfill ('0') << header.protocoltype	<< std::endl << std::dec
		<< "\thardware addr len: \t"	<< header.hwaddrlen				<< std::endl
		<< "\tprotocol addr len: \t"	<< header.protoaddrlen			<< std::endl
		<< "\topcode: \t"				<< std::hex << std::setw (4) << std::setfill ('0') << header.opcode			<< std::endl << std::dec
		<< "\tsource mac: \t"			<< header.sourcemac.toString () << std::endl
		<< "\tsource ip: \t"			<< header.sourceip.toString ()	<< std::endl
		<< "\tdest mac: \t"				<< header.destmac.toString ()	<< std::endl
		<< "\tdest ip: \t"				<< header.destip.toString ()	<< std::endl;

	return out.str ();
}

unsigned int ArpPacket::getMinProtocolSize ()
{
	return sizeof (ARP_HEADER);
}

unsigned short ArpPacket::getHardwaretype ()
{
	return header.hardwaretype;	
}

unsigned short ArpPacket::getProtocoltype ()
{
	return header.protocoltype;
}

unsigned char ArpPacket::getHardwareaddrlen ()
{
	return header.hwaddrlen;
}

unsigned char ArpPacket::getProtocoladdrlen ()
{
	return header.protoaddrlen;
}

unsigned short ArpPacket::getOpcode ()
{
	return header.opcode;
}

MAC_ADDR ArpPacket::getSourcemac ()
{
	return header.sourcemac;
}

IP_ADDR	ArpPacket::getSourceip ()
{
	return header.sourceip;
}

MAC_ADDR ArpPacket::getDestmac ()
{
	return header.destmac;
}

IP_ADDR	ArpPacket::getDestip ()
{
	return header.destip;
}

void ArpPacket::setHardwaretype (unsigned short hwtype)	
{
	header.hardwaretype = hwtype;
}

void ArpPacket::setProtocoltype (unsigned short	prototype)
{
	header.protocoltype = prototype;
}

void ArpPacket::setHardwareaddrlen (unsigned char hwlen)
{
	header.hwaddrlen = hwlen;
}

void ArpPacket::setProtocoladdrlen (unsigned char protolen)
{
	header.protoaddrlen = protolen;
}

void ArpPacket::setOpcode (unsigned short opcode)
{
	header.opcode = opcode;
}

void ArpPacket::setSourcemac (MAC_ADDR sourcemac)
{
	header.sourcemac = sourcemac;
}

void ArpPacket::setSourceip (IP_ADDR sourceip)
{
	header.sourceip = sourceip;	
}

void ArpPacket::setDestmac (MAC_ADDR destmac)
{
	header.destmac = destmac;
}

void ArpPacket::setDestip (IP_ADDR destip)
{
	header.destip = destip;
}

