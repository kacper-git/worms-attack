#include "PayloadPacket.h"

PayloadPacket::PayloadPacket()
{
	protocol = Packet::PROTO_DATA_PAYLOAD;
}

PayloadPacket::~PayloadPacket(void)
{
	data.destroy ();
}

bool PayloadPacket::parsePacket ()
{
	data.size = getSize ();
	data.buf = (unsigned char*) malloc (data.size);

	memcpy (data.buf, getBuffer(), data.size);

	nextProtocol	= Packet::PROTO_NONE;
	layersize		= getSize ();

	return true;
}

Packet::PAYLOAD_BUFFER PayloadPacket::getData ()
{
	Packet::PAYLOAD_BUFFER retbuf;

	retbuf.buf	= (unsigned char*) malloc (data.size);
	retbuf.size = data.size;

	memcpy (retbuf.buf, data.buf, data.size);

	// TODO:	return pseudo size
	//			need adaption in all procols that have
	//			a length field: IP, UDP (?), IPv6, more?

	return retbuf;
}

void PayloadPacket::setData (unsigned char* buf, int len)
{
	if( buf == NULL || len == 0){
		data.buf = NULL;
		data.size = 0;
		return;
	}

	data.buf	= (unsigned char*) realloc (data.buf, len);
	data.size	= len;

	memcpy (data.buf, buf, len);
}

string PayloadPacket::toString () 
{
	ostringstream out;
	out << "Payload packet"									<< std::endl
		<< "\tlength: \t"		<< data.size				<< std::endl
		<< "\tdata: \t\t"		<< data.toString (false)	<< std::endl
		<< "\tstring: \t\""		<< data.toString (true)		<< "\"";

	return out.str ();
}

unsigned int	PayloadPacket::getMinProtocolSize()
{
	return 1; // the protocol needs to have at least ony byte
}
