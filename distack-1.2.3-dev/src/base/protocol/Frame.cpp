#include "Frame.h"

#include <cassert>
#include "base/protocol/PacketFactory.h"
#include "base/common/DistackInfo.h"

Frame::LINK_TYPE Frame::nettype = Frame::LINK_UNKNOWN;

Frame::Frame(void){
}

Frame::~Frame(void)
{
	PacketFactory::instance()->freePacket (payloadpacket);
}

void Frame::buildFrame(DistackInfo* info){
	distackInfo = info;

#ifndef OMNET_SIMULATION
	switch (nettype) {
		case Frame::LINK_ETHERNET:
			{
				payloadpacket = PacketFactory::instance()->createPacket(Packet::PROTO_ETHERNET, distackInfo);
				break;
			}
		case Frame::LINK_RAWIP:
			{
				payloadpacket = PacketFactory::instance()->createPacket(Packet::PROTO_IP, distackInfo);	
				break;
			}
		case Frame::LINK_UNKNOWN:
		default:
			{
				cout << "invalid network type" << std::endl;
				payloadpacket = NULL;
			}
	} // switch (nettype)
#else
	nettype = Frame::LINK_ETHERNET;
#endif
}

string Frame::toString()
{
	ostringstream out;

	out << "Frame"														<< std::endl
		<< "\tnettype: \t"		<< nettype								<< std::endl
		<< "\ttimestamp: \t"	<< timestamp.toString ()				<< std::endl
		<< "\tlength: \t"		<< capturelength	<< " captured, "	
								<< packetlength		<< " original"		<< std::endl;
	
	Packet* cur = payloadpacket;

	while (cur != NULL) {
		out << cur->toString() << std::endl;
		cur = cur->getNextPacket ();
	}
		
	out << std::endl;
	return out.str ();
}

unsigned int Frame::getSize	()
{
	return (payloadpacket != NULL ? payloadpacket->getSize() : 0);
}

void Frame::parsePackets ()
{
	//
	// something went completely wrong and we have no ethernet base packet
	//

	if (payloadpacket == NULL) {
		assert (false);	
		return;
	}

	//
	// the frame has already been parsed through
	//

	if (payloadpacket->getNextPacket() != NULL) return;

	//
	// recursively parse the protocols 
	//

	payloadpacket->parsePacket		();
	payloadpacket->createNextLayer	(distackInfo);
}
