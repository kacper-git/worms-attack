#include "IcmpPacket.h"

IcmpPacket::IcmpPacket(void)
{
	memset (&header, 0, sizeof (ICMP_HEADER));
	protocol = Packet::PROTO_ICMP;
}

IcmpPacket::~IcmpPacket(void)
{
}

bool IcmpPacket::parsePacket()
{
	memcpy		(&header, buffer, sizeof (ICMP_HEADER)); 
	layersize	= sizeof (ICMP_HEADER);

	if (Packet::getChecksumValidation ()) {

		unsigned short chksum	= header.checksum;
		header.checksum			= 0;
		this->checksumgood		= (checksum (	&header, 
												getBuffer	() + layersize, 
												getSize		() - layersize
											) == chksum);
		header.checksum			= chksum;

	} // if (Configuration::instance()->getSetBadChecksumsToBad ()) 

	header.checksum	= swap16 (header.checksum);

	//
	// depending on the type and code
	// we may have an IP Packet in the data
	//

	nextProtocol = Packet::PROTO_DATA_PAYLOAD;

	switch (header.type) {

		case 3:		// destination unreachable message 
		case 4:		// source quench message
		case 5:		// redirect message
		case 11:	// time exceeded message
		case 12:	// parameter problem message
			{
				nextProtocol = Packet::PROTO_IP;
				break;
			}
		case 0:		// echo message
		case 8:		// echo reply message
		case 13:	// timestamp
		case 14:	// timestamp reply
			{
				nextProtocol = Packet::PROTO_DATA_PAYLOAD;
				break;
			}
		case 15:	// information Request 
		case 16:	// information Reply 
		default:
			{
				nextProtocol = Packet::PROTO_NONE;
				break;
			}

	} // switch (header.type) 
	
	return true;
}

unsigned char IcmpPacket::getType ()
{
	return header.type;
}

unsigned char IcmpPacket::getCode ()
{
	return header.code;
}

void IcmpPacket::setType (unsigned char tp)
{
	header.type = tp;
}

void IcmpPacket::setCode (unsigned char cd)
{
	header.code = cd;
}

unsigned short IcmpPacket::getChecksum ()
{
	return header.checksum;
}

void IcmpPacket::setChecksum (unsigned short chk)
{
	header.checksum = chk;
}

unsigned short IcmpPacket::checksum (PICMP_HEADER header, unsigned char* data, int datalen)
{
	unsigned char* buffer = (unsigned char*) malloc (sizeof (ICMP_HEADER) + datalen);
	memcpy (buffer, header, sizeof (ICMP_HEADER));
	memcpy (buffer + sizeof (ICMP_HEADER), data, datalen);

	unsigned short sum = Packet::checksum (buffer, sizeof (ICMP_HEADER) + datalen);
	free (buffer);

	return sum;
}

string IcmpPacket::toString ()
{
	ostringstream out;

	out << "ICMP packet"						<< std::endl
		<< "\ttype: \t"		<< (int)getType ()	<< std::endl
		<< "\tcode: \t"		<< (int)getCode ()	<< std::endl
		<< "\tchecksum: \t"	<< getChecksum  ()	;

	return out.str ();
}

unsigned long IcmpPacket::getMisc ()
{
	return header.misc;
}

void IcmpPacket::setMisc (unsigned long msc) 
{
	header.misc = msc;
}

unsigned int IcmpPacket::getMinProtocolSize ()
{
	return sizeof (ICMP_HEADER);
}

