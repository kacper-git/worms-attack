#include "UdpPacket.h"

UdpPacket::UdpPacket(void)
{
	memset		(&header, 0, sizeof (UDP_HEADER));
	protocol	= Packet::PROTO_UDP;
}

UdpPacket::~UdpPacket(void)
{
}

bool UdpPacket::parsePacket()
{
	memcpy (&header, buffer, sizeof (UDP_HEADER)); 

	//
	// what is the next protocol and the size of this protocol?
	//

	nextProtocol	= Packet::PROTO_DATA_PAYLOAD;
	layersize		= sizeof (UDP_HEADER);

	//
	// check for correct checksum
	//

	if (Packet::getChecksumValidation ()) {

		unsigned short chksum	= header.checksum;
		header.checksum			= 0;

		void* pipsource	= (ipProtocol == Packet::PROTO_IP ? (void*)&sourceip	: (void*)&sourceip6);
		void* pipdest	= (ipProtocol == Packet::PROTO_IP ? (void*)&destip		: (void*)&destip6	);
	
		this->checksumgood		= (checksum (	&header, 
												pipsource, 
												pipdest, 
												ipProtocol,
												getBuffer	() + layersize, 
												getSize		() - layersize) == chksum);
		header.checksum			= chksum;

	} // if (Configuration::instance()->getChecksumCheck ()) 

	//
	// adjust endianess
	//

	header.destport		=	swap16	(header.destport	);
	header.sourceport	=	swap16	(header.sourceport	);
	header.checksum		=	swap16	(header.checksum	);
	header.len			=	swap16	(header.len			);
	
	return true;
}

unsigned short UdpPacket::getSourceport()
{
	return header.sourceport;
}

unsigned short UdpPacket::getDestport()
{
	return header.destport;
}
		
unsigned short UdpPacket::getLen()
{
	return header.len;
}
						
unsigned short UdpPacket::getChecksum()
{
	return header.checksum;
}
		
void UdpPacket::setSourceport(unsigned short sp)
{
	header.sourceport = sp;
}

void UdpPacket::setDestport(unsigned short dp)
{
	header.destport = dp;
}
		
void UdpPacket::setLen(unsigned short len)
{
	header.len = len;
}	
						
void UdpPacket::setChecksum(unsigned short chksum)
{
	header.checksum = chksum;
}

unsigned short UdpPacket::checksum (PUDP_HEADER header, void* sourceip, void* destip, Packet::PROTOCOL ipproto, unsigned char* data, int datalen)
{
	//
	// create a pseudoheader
	// http://www.tcpipguide.com/free/t_TCPChecksumCalculationandtheTCPPseudoHeader-2.htm
	//
	
	if (datalen < 0) return 0;

	int udplen = sizeof (UDP_HEADER) + datalen;

	PUDP_PSEUDO_HEADER pseudoheader = NULL;
	unsigned int pseudolength		= 0;

	if (ipproto == Packet::PROTO_IP)	{
		pseudoheader = new UDP_IP4_PSEUDO_HEADER ();
		pseudolength = sizeof (UDP_IP4_PSEUDO_HEADER);
		
		memcpy (&((PUDP_IP4_PSEUDO_HEADER)pseudoheader)->sourceip, sourceip, IP_ADDR_LEN);
		memcpy (&((PUDP_IP4_PSEUDO_HEADER)pseudoheader)->destip,   destip,   IP_ADDR_LEN);

	} else {
		pseudoheader = new UDP_IP6_PSEUDO_HEADER ();
		pseudolength = sizeof (UDP_IP6_PSEUDO_HEADER);

		memcpy (&((PUDP_IP6_PSEUDO_HEADER)pseudoheader)->sourceip, sourceip, IPV6_ADDR_LEN);
		memcpy (&((PUDP_IP6_PSEUDO_HEADER)pseudoheader)->destip,   destip,   IPV6_ADDR_LEN);
	}
	
	pseudoheader->reserved	= 0;
	pseudoheader->protocol	= IPTYPE_UDP;
	pseudoheader->udplength	= swap16 (udplen);

	//
	// create a data buffer
	//

	int				buflen	= pseudolength + udplen;
	unsigned char*	buf		= (unsigned char*) malloc (buflen);

	memset (buf, 0, buflen);

	//
	// copy pseudoheader header, data into buffer
	// 

	memcpy (buf, pseudoheader,  pseudolength);
	memcpy (buf + pseudolength, header, sizeof (UDP_HEADER));
	memcpy (buf + pseudolength + sizeof (UDP_HEADER), data, datalen);

	//
	// create the checksum
	//

	unsigned short sum = Packet::checksum (buf, buflen);

	free (buf);
	delete pseudoheader;

	//
	// if the checksum calculates to 0x0000 we have to set it to 0xFFFF
	//

	if (sum == 0x0000)
		sum = 0xFFFF;

	return sum;
}

void UdpPacket::setIpAddresses (IP_ADDR source, IP_ADDR dest)
{
	sourceip	= source;
	destip		= dest;
	ipProtocol	= Packet::PROTO_IP;
}

void UdpPacket::setIpAddresses (IPV6_ADDR source, IPV6_ADDR dest)
{
	sourceip6	= source;
	destip6		= dest;
	ipProtocol	= Packet::PROTO_IPV6;
}

string UdpPacket::toString ()
{
	ostringstream out;

	out << "UDP packet"									<< std::endl
		<< "\tsource port: \t"	<< getSourceport ()		<< std::endl
		<< "\tdest port: \t"	<< getDestport ()		<< std::endl
		<< "\tlength: \t"		<< getLen ()			<< std::endl
		<< "\tchecksum: \t"		<< getChecksum ();

	return out.str ();
}

unsigned int UdpPacket::getMinProtocolSize ()
{
	return sizeof (UDP_HEADER);
}

