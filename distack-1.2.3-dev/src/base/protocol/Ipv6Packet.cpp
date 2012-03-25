#include "Ipv6Packet.h"
#include "TcpPacket.h"
#include "UdpPacket.h"

Ipv6Packet::Ipv6Packet ()
{
	memset		(&header, 0, sizeof (IPV6_HEADER));
	protocol	= Packet::PROTO_IPV6;
}

Ipv6Packet::~Ipv6Packet ()
{	
}

bool Ipv6Packet::parsePacket ()
{
	memcpy			(&header, buffer, sizeof (IPV6_HEADER)); 
	layersize		= sizeof (IPV6_HEADER);

	header.version_trafficclass_flowlabel	= swap32 (header.version_trafficclass_flowlabel);
	header.payloadlen						= swap16 (header.payloadlen);

	nextProtocol	= IpPacket::getTransportProtocol (header.nextheader);

	//
	// remove ethernet padding
	//

	if (getSize () > sizeof (IPV6_HEADER) + header.payloadlen)
		this->size = sizeof (IPV6_HEADER) + header.payloadlen;

	return true;
}

string Ipv6Packet::toString ()
{
	ostringstream out;

	out << "IPv6 packet"											<< std::endl
		<< "\tVersion: \t"			<< (int) getVersion ()			<< std::endl
		<< "\tTrafficclass: \t0x"	<< std::hex << std::setw(2)		<< std::setfill ('0') << (int) getTrafficclass ()	<< std::endl << std::dec
		<< "\tFlowlabel: \t0x"		<< std::hex << std::setw(2)		<< std::setfill ('0') << getFlowlabel ()	<< std::endl << std::dec
		<< "\tPayloadlen: \t"		<< getPayloadlen ()				<< std::endl
		<< "\tNextheader: \t0x"		<< std::hex << std::setw(2)		<< std::setfill ('0') << (int) getNextheader ()	<< std::endl << std::dec
		<< "\tHoplimit: \t"			<< (int) getHoplimit ()			<< std::endl
		<< "\tSourceaddr: \t"		<< getSourceaddr().toString ()	<< std::endl
		<< "\tDestaddr: \t"			<< getDestaddr().toString	()	;

	return out.str ();
}

unsigned int Ipv6Packet::getMinProtocolSize ()
{
	return sizeof (IPV6_HEADER);
}

unsigned char Ipv6Packet::getVersion ()
{
	return IPV6_VERSION (header.version_trafficclass_flowlabel);
}

unsigned char Ipv6Packet::getTrafficclass ()
{
	return IPV6_TRAFFICCLASS (header.version_trafficclass_flowlabel);
}

unsigned int Ipv6Packet::getFlowlabel ()
{
	return IPV6_FLOWLABEL (header.version_trafficclass_flowlabel);
}

unsigned short Ipv6Packet::getPayloadlen ()
{
	return header.payloadlen;
}

unsigned char Ipv6Packet::getNextheader ()
{
	return header.nextheader;
}

unsigned char Ipv6Packet::getHoplimit ()
{
	return header.hoplimit;	
}

IPV6_ADDR Ipv6Packet::getSourceaddr ()
{
	return header.sourceaddr;
}

IPV6_ADDR Ipv6Packet::getDestaddr ()
{
	return header.destaddr;	
}

void Ipv6Packet::setVersion (unsigned char version)
{
	header.version_trafficclass_flowlabel = (((unsigned int)version & 0xF) << 28) | (header.version_trafficclass_flowlabel & 0x0FFFFFFF);
}

void Ipv6Packet::setTrafficclass (unsigned char trafficclass)
{
	header.version_trafficclass_flowlabel = ((unsigned int)trafficclass << 20) | (header.version_trafficclass_flowlabel & 0xF00FFFFF);
}

void Ipv6Packet::setFlowlabel (unsigned int flowlabel)
{
	header.version_trafficclass_flowlabel = (flowlabel & 0x000FFFFF) | (header.version_trafficclass_flowlabel & 0xFFF00000);
}

void Ipv6Packet::setPayloadlen (unsigned short payloadlen)
{
	header.payloadlen = payloadlen;
}

void Ipv6Packet::setNextheader (unsigned char nextheader)
{
	header.nextheader = nextheader;
}

void Ipv6Packet::setHoplimit (unsigned char hoplimit)
{
	header.hoplimit = hoplimit;
}

void Ipv6Packet::setSourceaddr (IPV6_ADDR sourceaddr)
{
	header.sourceaddr = sourceaddr;
}

void Ipv6Packet::setDestaddr (IPV6_ADDR destaddr)
{
	header.destaddr = destaddr;
}
