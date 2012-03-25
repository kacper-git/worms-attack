#include "IpPacket.h"
#include "TcpPacket.h"
#include "UdpPacket.h"

IpPacket::IpPacket(void)
{
	options.buf		= NULL;
	options.size	= 0;
	memset			(&header, 0, sizeof (IP_HEADER));
	protocol		= Packet::PROTO_IP;
}

IpPacket::~IpPacket(void)
{
	options.destroy ();
}

bool IpPacket::parsePacket() 
{
	memcpy (&header, buffer, sizeof (IP_HEADER));

	//
	// check for correct checksum
	//

	if (Packet::getChecksumValidation ()) {
		unsigned short chksum	= header.checksum;
		header.checksum			= 0;
		this->checksumgood		= (checksum (&header) == chksum);
		header.checksum			= chksum;
	}
		
	//
	// correct some endianess stuff 
	//

	header.totallen			=	swap16	(header.totallen			);	 
	header.identification	=	swap16	(header.identification		);
	header.flags_fragoffset	=	swap16	(header.flags_fragoffset	);
	header.checksum			=	swap16	(header.checksum			);	

	//
	// get the next transport layer protocol
	//

	nextProtocol = IpPacket::getTransportProtocol (header.protocol);

	//
	// check for correct header values to make sure the packet is not corrupt
	// if is is corrupt we will stop the parsing here and return
	//

	if (! (	IP_HEADER_NO_OPTIONS_LEN	<= getHeaderlength	()  && 
			getHeaderlength	()			<= getTotallen		() 	)) {
		
		layersize		= getSize ();
		nextProtocol	= Packet::PROTO_NONE;
		options.size	= 0;
		options.buf		= NULL;
		return true;
	}

	//
	// get the options, if any are provided
	// 

	options.size	= getHeaderlength () - IP_HEADER_NO_OPTIONS_LEN;
	options.buf		= NULL;

	if (options.size > 0 && getSize () >= IP_HEADER_NO_OPTIONS_LEN + options.size) {
		options.buf = (unsigned char*) malloc (options.size);
		memcpy (options.buf, buffer + IP_HEADER_NO_OPTIONS_LEN, options.size);
	} else
		options.size = 0;

	layersize = sizeof (IP_HEADER) + options.size;

	//
	// remove the ethernet padding. Otherwise
	// it will be used as payload.
	// the ethernet class will add it again
	// 
	
	if (getSize () > getTotallen ()) 
		this->size = getTotallen ();

	return true;
}

unsigned short IpPacket::checksum (PIP_HEADER ipheader)
{
	return Packet::checksum ((unsigned char*)ipheader, sizeof (IP_HEADER));
}

unsigned char IpPacket::getVersion ()
{
	return IP_HEADER_VERSION (header.version_len);
}

unsigned char IpPacket::getHeaderlength ()
{
	return IP_HEADER_LEN (header.version_len);
}

unsigned char IpPacket::getTos ()
{
	return header.typeofservice;
}

unsigned short IpPacket::getIdentification ()
{
	return header.identification;
}

unsigned short IpPacket::getFlags ()
{
	return IP_HEADER_FLAGS (header.flags_fragoffset);
}

unsigned short IpPacket::getFragoffset ()
{
	return IP_HEADER_FRAGOFFSET (header.flags_fragoffset);
}

unsigned char IpPacket::getTtl ()
{
	return header.ttl;
}

unsigned char IpPacket::getProtocol ()
{
	return header.protocol;
}

unsigned short IpPacket::getChecksum ()
{
	return header.checksum;
}

IP_ADDR IpPacket::getSourceip ()
{	
	IP_ADDR ret;
	memcpy (&ret, &header.sourceip, IP_ADDR_LEN);
	return ret;
}

IP_ADDR	IpPacket::getDestip ()
{
	IP_ADDR ret;
	memcpy (&ret, &header.destip, IP_ADDR_LEN);
	return ret;
}

bool IpPacket::isFlagSet (IP_FLAG flag)
{
	return ((getFlags() & flag) == flag);
}

void IpPacket::setFlag (IP_FLAG flag, bool set)
{
	unsigned short headerflags = getFlags ();

	if (set) headerflags |= flag;
	else	 headerflags &= (~flag);

	setFlags (headerflags);
}

void IpPacket::setVersion (unsigned char ver)
{
	header.version_len = ((ver & 0xF) << 4) | (getHeaderlength() / 4);
}

void IpPacket::setHeaderlength (unsigned char len)
{
	header.version_len = (getVersion() << 4) | ((unsigned char)((len/4) & 0xF));
}

void IpPacket::setTos (unsigned char tos)
{
	header.typeofservice = tos;
}

void IpPacket::setIdentification (unsigned short ident)
{
	header.identification = ident;
}

void IpPacket::setFlags (unsigned short	flgs)
{
	header.flags_fragoffset = ((unsigned short)(flgs & 0x07) << 13) | getFragoffset();
}

void IpPacket::setFragoffset (unsigned short fragoff)
{
	header.flags_fragoffset = ((getFlags() & 0x07) << 13) | (0xD & fragoff);
}

void IpPacket::setTtl (unsigned char tl)
{
	header.ttl = tl;
}

void IpPacket::setProtocol (unsigned char proto)
{
	header.protocol = proto;
}

void IpPacket::setChecksum (unsigned short checks)
{
	header.checksum = checks;
}

void IpPacket::setSourceip (IP_ADDR	sip)
{
	memcpy (&header.sourceip, &sip, IP_ADDR_LEN);
}

void IpPacket::setDestip (IP_ADDR dip)
{
	memcpy (&header.destip, &dip, IP_ADDR_LEN);
}	

unsigned short IpPacket::getTotallen ()
{
	return header.totallen;
}

void IpPacket::setTotallen (unsigned short totlen)
{
	header.totallen = totlen;
}

void IpPacket::setOptions (unsigned char* buf, int len)
{
	options.buf		= (unsigned char*) realloc (options.buf, len);
	options.size	= len;
	memcpy (options.buf, buf, len);
}

Packet::PAYLOAD_BUFFER IpPacket::getOptions	()
{
	PAYLOAD_BUFFER retbuf;
	
	retbuf.buf = (unsigned char*) malloc (options.size);
	retbuf.size = options.size;

	memcpy (retbuf.buf, options.buf, options.size);

	return retbuf;
}

string IpPacket::toString ()
{
	ostringstream out;
	Packet::PAYLOAD_BUFFER opts = getOptions ();

	out << "IP packet"			<< std::endl
		<< "\tversion: \t"		<< (int)getVersion ()			<< std::endl
		<< "\tlength: \t"		<< (int)getHeaderlength ()		<< " bytes" << std::endl
		<< "\ttos: \t\t0x"		<< std::hex << std::setw (2)	<< std::setfill ('0')<< (int)getTos () << std::endl << std::dec
		<< "\ttotal length: \t" << getTotallen () << " bytes"	<< std::endl
		<< "\tident: \t\t0x"	<< std::hex << std::setw (4)	<< std::setfill ('0') << getIdentification () << std::endl << std::dec
		<< "\tflags: \t\t0x"	<< std::hex << std::setw (2)	<< std::setfill ('0') << getFlags () << std::endl << std::dec
		<< "\tfragoff: \t0x"	<< std::hex << std::setw (4)	<< std::setfill ('0') << getFragoffset () << std::endl << std::dec
		<< "\tttl: \t\t"		<< (int)getTtl ()				<< std::endl
		<< "\tprotocol: \t0x"	<< std::hex << std::setw(2)		<< std::setfill ('0') << (int)getProtocol () << std::endl << std::dec
		<< "\tchecksum: \t0x"	<< std::hex << std::setw (4)	<< std::setfill ('0') << getChecksum () << std::endl << std::dec
		<< "\tsource ip: \t"	<< getSourceip ().toString ()	<< std::endl
		<< "\tdest ip: \t"		<< getDestip ().toString ()		<< std::endl
		<< "\toptions len: \t"	<< opts.size					<< std::endl
		<< "\toptions: \t"		<< opts.toString ();
	
	opts.destroy ();

	return out.str ();
}

unsigned int IpPacket::getMinProtocolSize ()
{
	return sizeof (IP_HEADER);
}

Packet::PROTOCOL IpPacket::getTransportProtocol (unsigned char proto)
{
	Packet::PROTOCOL nextproto = Packet::PROTO_DATA_PAYLOAD;

	switch (proto) {
		case IPTYPE_TCP:	nextproto = Packet::PROTO_TCP;			break;
		case IPTYPE_UDP:	nextproto = Packet::PROTO_UDP;			break;
		case IPTYPE_ICMP:	nextproto = Packet::PROTO_ICMP;			break;
		case IPTYPE_IP:		nextproto = Packet::PROTO_IP;			break;
		case IPTYPE_IPV6:	nextproto = Packet::PROTO_IPV6;			break;
		case IPTYPE_MPLS:	nextproto = Packet::PROTO_MPLS;			break;
		default:			nextproto = Packet::PROTO_DATA_PAYLOAD;	break;
	}

	return nextproto;
}
