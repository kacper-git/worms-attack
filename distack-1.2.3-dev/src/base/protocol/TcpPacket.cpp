#include "TcpPacket.h"

TcpPacket::TcpPacket(void)
{
	options.buf		= NULL;
	options.size	= 0;
	memset			(&header, 0, sizeof (TCP_HEADER));
	protocol		= Packet::PROTO_TCP;
}

TcpPacket::~TcpPacket(void)
{
	options.destroy ();
}

bool TcpPacket::parsePacket	 ()
{
	memcpy (&header, buffer, sizeof (TCP_HEADER)); 

	//
	// check for correct header values to make sure the packet is not corrupt
	// if is is corrupt we will stop the parsing here and return
	//

	header.headerlen_flags = swap16	(header.headerlen_flags);

	if (! (	TCP_HEADER_NO_OPTIONS_LEN	<= getHeaderlength	()  && 
			getHeaderlength	()			<= getSize			()	)) {
		
		layersize		= getSize ();
		nextProtocol	= Packet::PROTO_NONE;
		options.size	= 0;
		options.buf		= NULL;
		return true;
	}

	//
	// get the options, if any are provided
	// 

	options.size	= getHeaderlength() - TCP_HEADER_NO_OPTIONS_LEN;
	options.buf		= NULL;
	

	if (options.size > 0 && getSize() >= TCP_HEADER_NO_OPTIONS_LEN + options.size) {
		options.buf = (unsigned char*) malloc (options.size);
		memcpy (options.buf, buffer + TCP_HEADER_NO_OPTIONS_LEN, options.size);
	} else
		options.size = 0;

	nextProtocol	= Packet::PROTO_DATA_PAYLOAD;
	layersize		= sizeof (TCP_HEADER) + options.size;

	header.headerlen_flags = swap16	(header.headerlen_flags);

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
												options.buf, 
												options.size, 
												getBuffer	() + layersize, 
												getSize		() - layersize
											) == chksum);
		header.checksum			= chksum;

	} // if (Configuration::instance()->getChecksumCheck ()) 

	//
	// swap some values
	//

	header.acknum				= swap32	(header.acknum				);
	header.checksum				= swap16	(header.checksum			);
	header.destport				= swap16	(header.destport			);
	header.headerlen_flags		= swap16	(header.headerlen_flags		);
	header.sequencenum			= swap32	(header.sequencenum			);	
	header.sourceport			= swap16	(header.sourceport			);
	header.urgentpointer		= swap16	(header.urgentpointer		);
	header.windowsize			= swap16	(header.windowsize			);

	return true;
}

unsigned short TcpPacket::getSourceport()
{
	return header.sourceport;
}
		
unsigned short TcpPacket::getDestport()
{
	return header.destport;
}
		
unsigned long TcpPacket::getSequencenum()
{
	return header.sequencenum;
}
		
unsigned long TcpPacket::getAcknum()
{
	return header.acknum;
}
		
unsigned short TcpPacket::getHeaderlength()
{
	return TCP_HEADER_LEN (header.headerlen_flags);
}
		
unsigned short TcpPacket::getFlags()
{
	return TCP_HEADER_FLAGS (header.headerlen_flags);
}
		
unsigned short TcpPacket::getWindowsize()
{
	return header.windowsize;
}
			
unsigned short TcpPacket::getChecksum()
{
	return header.checksum;
}
		
unsigned short TcpPacket::getUrgentpointer()
{
	return header.urgentpointer;
}
		

void TcpPacket::setSourceport(unsigned short sourcep)
{
	header.sourceport = sourcep;
}

void TcpPacket::setDestport(unsigned short destp)
{
	header.destport = destp;
}
		
void TcpPacket::setSequencenum(unsigned long seqnum)
{
	header.sequencenum = seqnum;
}
		
void TcpPacket::setAcknum(unsigned long aknum)
{
	header.acknum = aknum;
}
		
void TcpPacket::setHeaderlength(unsigned short hdlen)
{
	header.headerlen_flags = (((hdlen/4) & 0xF) << 12) | (getFlags() & 0x3F);
}
		
void TcpPacket::setFlags(unsigned short flgs)
{
	header.headerlen_flags = (((getHeaderlength()/4)& 0xF) << 12) | (flgs & 0x3F);
}
	
bool TcpPacket::isFlagSet (TCP_FLAG flag)
{
	return ((getFlags() & flag) == flag);
}

void TcpPacket::setFlag (TCP_FLAG flag, bool set)
{
	unsigned short headerflags = getFlags ();

	if (set) headerflags |= flag;
	else	 headerflags &= (~flag);

	setFlags (headerflags);
}

void TcpPacket::setWindowsize(unsigned short wsize)
{
	header.windowsize = wsize;
}
			
void TcpPacket::setChecksum(unsigned short cksum)
{
	header.checksum = cksum;
}
		
void TcpPacket::setUrgentpointer(unsigned short	urgpnt)
{
	header.urgentpointer = urgpnt;
}
	
unsigned short TcpPacket::checksum (PTCP_HEADER header, void* sourceip, void* destip, Packet::PROTOCOL ipproto,unsigned char* options, int optionslen, unsigned char* data, int datalen)
{
	//
	// create a pseudoheader
	// http://www.tcpipguide.com/free/t_TCPChecksumCalculationandtheTCPPseudoHeader-2.htm
	//
	
	if (optionslen	== 0) options	= NULL;
	if (datalen		== 0) data		= NULL;

	int tcplen	= sizeof (TCP_HEADER) + optionslen + datalen;

	//
	// create the approriate pseudo header (with IPv4 or IPv6 addresses)
	//

	PTCP_PSEUDO_HEADER pseudoheader = NULL;
	unsigned int pseudolength		= 0;

	if (ipproto == Packet::PROTO_IP)	{
		pseudoheader = new TCP_IP4_PSEUDO_HEADER ();
		pseudolength = sizeof (TCP_IP4_PSEUDO_HEADER);
		
		memcpy (&((PTCP_IP4_PSEUDO_HEADER)pseudoheader)->sourceip, sourceip, IP_ADDR_LEN);
		memcpy (&((PTCP_IP4_PSEUDO_HEADER)pseudoheader)->destip,   destip,   IP_ADDR_LEN);

	} else {
		pseudoheader = new TCP_IP6_PSEUDO_HEADER ();
		pseudolength = sizeof (TCP_IP6_PSEUDO_HEADER);

		memcpy (&((PTCP_IP6_PSEUDO_HEADER)pseudoheader)->sourceip, sourceip, IPV6_ADDR_LEN);
		memcpy (&((PTCP_IP6_PSEUDO_HEADER)pseudoheader)->destip,   destip,   IPV6_ADDR_LEN);
	}

	pseudoheader->reserved	= 0;
	pseudoheader->protocol	= IPTYPE_TCP;
	pseudoheader->tcplength	= swap16 (tcplen);

	//
	// create a data buffer
	//

	int				buflen	= pseudolength + tcplen;
	unsigned char*	buf		= (unsigned char*) malloc (buflen);

	memset (buf, 0, buflen);

	//
	// copy pseudoheader header, options, data into buffer
	// 

	memcpy (buf, pseudoheader, pseudolength);
	memcpy (buf + pseudolength, header, sizeof (TCP_HEADER));
	memcpy (buf + pseudolength + sizeof (TCP_HEADER), options, optionslen);
	memcpy (buf + pseudolength + sizeof (TCP_HEADER) + optionslen, data, datalen);

	//
	// create the checksum
	//

	unsigned short sum = Packet::checksum (buf, buflen);

	free (buf);
	delete pseudoheader;

	return sum;
}

void TcpPacket::setIpAddresses (IP_ADDR source, IP_ADDR dest)
{
	sourceip	= source;
	destip		= dest;
	ipProtocol	= Packet::PROTO_IP;
}

void TcpPacket::setIpAddresses (IPV6_ADDR source, IPV6_ADDR dest)
{
	sourceip6	= source;
	destip6		= dest;
	ipProtocol	= Packet::PROTO_IPV6;
}

void TcpPacket::setOptions (unsigned char* buf, int len)
{
	options.buf		= (unsigned char*) realloc (options.buf, len);
	options.size	= len;
	memcpy (options.buf, buf, len);
}

Packet::PAYLOAD_BUFFER TcpPacket::getOptions	()
{
	PAYLOAD_BUFFER retbuf;
	
	retbuf.buf = (unsigned char*) malloc (options.size);
	retbuf.size = options.size;

	memcpy (retbuf.buf, options.buf, options.size);

	return retbuf;
}

string TcpPacket::toString ()
{
	ostringstream out;
	Packet::PAYLOAD_BUFFER opts = getOptions ();

	out << "TCP packet" << std::endl
		<< "\tsource port: \t"		<< getSourceport ()		<< std::endl
		<< "\tdest port: \t"		<< getDestport ()		<< std::endl
		<< "\tsequencenum: \t"		<< getSequencenum ()	<< std::endl
		<< "\tacknum: \t"			<< getAcknum ()			<< std::endl
		<< "\theaderlen: \t"		<< getHeaderlength ()	<< " bytes" << std::endl
		<< "\tflags: \t\t0x"		<< std::hex << std::setw (4) << std::setfill ('0') << getFlags () << std::endl << std::dec
		<< "\twindowsize: \t"		<< getWindowsize ()		<< std::endl
		<< "\tchecksum: \t0x"		<< std::hex << std::setw (4) << std::setfill ('0') << getChecksum () << std::endl << std::dec
		<< "\turgent pnt: \t"		<< getUrgentpointer ()	<< std::endl
		<< "\toptions len: \t"		<< opts.size			<< std::endl
		<< "\toptions: \t"			<< opts.toString ();

	opts.destroy ();

	return out.str ();
}

unsigned int TcpPacket::getMinProtocolSize ()
{
	return sizeof (TCP_HEADER);
}
