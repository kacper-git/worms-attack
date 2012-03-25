#include "Packet.h"
#include "PacketFactory.h" // this include _must_ be here because we have a circular inclusion

Packet::Packet(void)
:	buffer			(NULL),
	size			(0),
	layersize		(0),
	protocol		(PROTO_NONE),
	nextProtocol	(PROTO_NONE),
	nextPacket		(NULL),
	checksumgood	(false),
	checksumcheck	(false)
{
}

Packet::~Packet(void)
{
	if (nextPacket != NULL)
		PacketFactory::instance()->freePacket (nextPacket);

	nextPacket = NULL;

	if (buffer != NULL)
		free (buffer);

	buffer = NULL;
}

unsigned char* Packet::getBuffer()
{
	return buffer;
}

unsigned int Packet::getSize ()
{
	return size;
}

bool Packet::createNextLayer(DistackInfo* info)
{
	bool ret = true;

	//
	// create the next packet object
	//

	nextPacket = PacketFactory::instance()->createPacket (nextProtocol, info);
	if (nextPacket == NULL) return false;

	//
	// some protocols need special handling because they 
	// need information from layer n-1
	//

	switch (nextProtocol) {
		case Packet::PROTO_TCP:
			{
				if (this->protocol == Packet::PROTO_IP)
					((TcpPacket*)nextPacket)->setIpAddresses (((IpPacket*)this)->getSourceip(), ((IpPacket*)this)->getDestip());
				else if (this->protocol == Packet::PROTO_IPV6)
					((TcpPacket*)nextPacket)->setIpAddresses (((Ipv6Packet*)this)->getSourceaddr(), ((Ipv6Packet*)this)->getDestaddr());
				
				break;
			}
		case Packet::PROTO_UDP:
			{	
				if (this->protocol == Packet::PROTO_IP)
					((UdpPacket*)nextPacket)->setIpAddresses (((IpPacket*)this)->getSourceip(), ((IpPacket*)this)->getDestip());
				else if (this->protocol == Packet::PROTO_IPV6)
					((UdpPacket*)nextPacket)->setIpAddresses (((Ipv6Packet*)this)->getSourceaddr(), ((Ipv6Packet*)this)->getDestaddr());
				
				break;
			}
		default: 
			{
				// this default is needed to shut up g++
				break;
			}
	} // switch (nextProtocol) 

	//
	// if we have space in the buffer then there may be
	// more packets, create them, else, abort
	//

	if (size <= layersize ) {
		nextProtocol = Packet::PROTO_NONE;	
		
		if (nextPacket != NULL)
			PacketFactory::instance()->freePacket (nextPacket); 

		nextPacket = NULL;
		return true;
	}

	//
	// not enought data left to create the new layer
	// maybe a incomplete packet
	//

	if (nextPacket->getMinProtocolSize() > (size - layersize)) {
		nextProtocol = Packet::PROTO_NONE;	
		
		if (nextPacket != NULL)
			PacketFactory::instance()->freePacket (nextPacket); 

		nextPacket = NULL;
		return true;
	}

	//
	// create a new packet
	//

	nextPacket->setSize (size - layersize);
	memcpy				(nextPacket->getBuffer(), getBuffer() + layersize, nextPacket->size);

	nextPacket->protocol = nextProtocol;

	ret |= nextPacket->parsePacket		();
	ret |= nextPacket->createNextLayer	(info);

	return ret;
}

Packet::PROTOCOL Packet::getProtocol ()
{
	return protocol;
}

Packet*	Packet::getNextPacket()
{
	return nextPacket;
}

void Packet::setNextPacket (Packet* nextpacket)
{
	nextPacket = nextpacket;
}	

void Packet::setNextProtocol(PROTOCOL proto)
{
	nextProtocol = proto;
}

Packet::PROTOCOL Packet::getNextProtocol ()
{
	return nextProtocol;
}

unsigned short Packet::checksum(unsigned char* databuf, int len)
{
	const unsigned short*	buf		= (const unsigned short *)databuf;
	int						length	= len;
	unsigned long			result	= 0;

    while (length > 1) {
        result += *(buf++);
        length  -= sizeof(*buf);
    }

	if (length) 
		result += *(unsigned char*)buf;

    result =	(result >> 16) + (result & 0xFFFF);
    result +=	(result >> 16);
    result =	(~result) & 0xFFFF;

    return (unsigned short)result;
}

void Packet::setChecksumValidation (bool validate)
{
	checksumcheck = validate;
}

bool Packet::getChecksumValidation ()
{
	return checksumcheck;
}

bool Packet::getChecksumgood ()
{
	return checksumgood;
}

void Packet::setChecksumgood (bool good)
{	
	checksumgood = good;
}

string Packet::getProtocolNameFromId (PROTOCOL proto)
{	
	return ProtocolNameResolver::instance()->getName (proto);
}

Packet::PROTOCOL Packet::getProtocolIdFromName (string name)
{
	return (Packet::PROTOCOL) ProtocolNameResolver::instance()->getId (name);	
}
