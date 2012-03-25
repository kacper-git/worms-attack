#include "NetworkInterfaceOmnetpp.h"

#include "base/module/FrameDistribution.h"
#include "Distack.h"

#ifdef OMNET_SIMULATION

NetworkInterfaceOmnetpp::NetworkInterfaceOmnetpp( DistackInfo* info )
	: NetworkInterface(
		info, "OmnetppInterface", NetworkInterface::CAPTURE_TYPE_ONLINE, 
		true, (unsigned int) pow (2.0, 16) ),
	frameDistribution( NULL ){
}

NetworkInterfaceOmnetpp::~NetworkInterfaceOmnetpp ()
{
	if (getState() == NetworkInterface::INTERFACE_STATE_OPEN)
		close ();
}

bool NetworkInterfaceOmnetpp::open ()
{
	return true;
}

bool NetworkInterfaceOmnetpp::close ()
{
	return true;
}

Frame* NetworkInterfaceOmnetpp::read ()
{
	return NULL;
}

void NetworkInterfaceOmnetpp::handleMessage (cPacket* msg)
{
	handleProtocolMessage (msg);
}

void NetworkInterfaceOmnetpp::setFrameDistribution (FrameDistribution* distrib)
{
	frameDistribution = distrib;
}

void NetworkInterfaceOmnetpp::handleProtocolMessage (cPacket* msg)
{
	if (msg == NULL) return;

	//
	// create the distack encapsulated Packets
	// according to the omnet packets ... 
	//

	Frame* frame = convertOmnetToDistack (msg);	

	if (frame == NULL) return;

	frameDistribution->manualFrameInjection (frame);
}

Frame* NetworkInterfaceOmnetpp::convertOmnetToDistack (cPacket* message)
{
	cPacket* currentMessage = message;

	//
	// we do not use the full capacity of protocol encapsulation etc.
	// here. Maybe worth updating this code to support such stuff. 
	// Currently not needed ...
	//

	//
	// first protocol must be IP as we are an IPv4-Router
	//

	IPDatagram* ipDatagram = check_and_cast<IPDatagram*>(currentMessage);
	if(ipDatagram == NULL) return NULL;

	IpPacket*	ipPacket	= (IpPacket*) convertMessage (ipDatagram);
	Packet*		packetChain = ipPacket;
	Packet*		current		= ipPacket;

	//
	// handle IP-in-IP packets
	//

	if (ipPacket->getNextProtocol() == Packet::PROTO_IP) {

		currentMessage		 = currentMessage->getEncapsulatedMsg ();
		IPDatagram* datagram = check_and_cast<IPDatagram*> (currentMessage);

		Packet* innerIpPacket = convertMessage (datagram);

		ipPacket->setNextPacket	  (innerIpPacket);
		ipPacket->setNextProtocol (Packet::PROTO_IP);
		
		current = innerIpPacket;
	
	} // if (ipPacket->getProtocol() == Packet::PROTO_IP)
	
	//
	// handle the transport layer protocol
	//

	current->setNextProtocol (IpPacket::getTransportProtocol (((IpPacket*)current)->getProtocol()));

	Packet*			 transportPacket = NULL;
	Packet::PROTOCOL transportProto  = current->getNextProtocol ();
	currentMessage					 = currentMessage->getEncapsulatedMsg ();
	int payloadLength = 0;

	if (currentMessage != NULL) {

		switch (transportProto) {
			case Packet::PROTO_TCP:
				{
					TCPSegment* tcpSegment = check_and_cast<TCPSegment*>(currentMessage);
					transportPacket = convertMessage (tcpSegment);
					if (tcpSegment->getPayloadArraySize() > 0) {
						currentMessage = tcpSegment->getPayload(0).msg;
						payloadLength = currentMessage->getByteLength();
						uint32 x = 0;
						delete tcpSegment->removeFirstPayloadMessage(x);
					}
					break;
				}
			case Packet::PROTO_UDP:
				{
					UDPPacket* udpPacket = check_and_cast<UDPPacket*>(currentMessage);
					transportPacket = convertMessage (udpPacket);
					currentMessage = currentMessage->getEncapsulatedMsg();
					if (currentMessage != NULL) payloadLength = currentMessage->getByteLength();
					break;	
				}
			case Packet::PROTO_ICMP:	
				{
					ICMPMessage* icmpMsg = check_and_cast<ICMPMessage*>(currentMessage);
					transportPacket = convertMessage (icmpMsg);
					currentMessage = currentMessage->getEncapsulatedMsg();
					if (currentMessage != NULL) payloadLength = currentMessage->getByteLength();
					break;
				}
			default:					
				{
					transportPacket = NULL;		
					break;
				}
		} //switch (transportProto)
	} // if (currentMessage != NULL)

	current->setNextPacket   (transportPacket);
	current->setNextProtocol (transportProto);

	//
	// no more protocols in upper layers as Omnet does not support any
	// (also no IP-in-ICMP etc. stuff is available, so we are done
	// but there might be some data which we model with the PayloadPacket
	//

	if (transportPacket != NULL) {
		if (currentMessage == NULL) {
			transportPacket->setNextPacket	 (NULL);
			transportPacket->setNextProtocol (Packet::PROTO_NONE);
		} else {
			PayloadPacket* payload = (PayloadPacket*)PacketFactory::instance()->createPacket (Packet::PROTO_DATA_PAYLOAD, distackInfo);
			
			payload->setData		 (NULL, 0);
			payload->setSize		(payloadLength, true);
			payload->setNextPacket	 (NULL);
			payload->setNextProtocol (Packet::PROTO_NONE);

			transportPacket->setNextPacket	 (payload);
			transportPacket->setNextProtocol (Packet::PROTO_DATA_PAYLOAD);
		}
	
	} // if (transportPacket != NULL)

	//
	// put it into a frame
	//

	Frame* frame = PacketFactory::instance()->createFrame (distackInfo);
	frame->payloadpacket = packetChain;

	frame->capturelength = frame->payloadpacket->getSize  ();
	frame->packetlength  = frame->payloadpacket->getSize  ();
	
	//
	// set the timestamp for the frame
	//

	simtime_t timestamp = message->getTimestamp ();

	double intPart   = 0;
	double fractPart = 0;

	fractPart = modf (timestamp.dbl(), &intPart); //TODO: prüfen ob das so korrekt ist

	frame->timestamp.tv_sec  = (long)intPart;
	frame->timestamp.tv_usec = (long)fractPart * 1000;

	assert (frame->timestamp.tv_sec  >= 0);
	assert (frame->timestamp.tv_usec >= 0);

	return frame;
}

Packet* NetworkInterfaceOmnetpp::convertMessage (IPDatagram* msg)
{
	IpPacket* ipPacket = (IpPacket*)PacketFactory::instance()->createPacket (Packet::PROTO_IP, distackInfo);
	ipPacket->setSize (msg->getByteLength(), true);

	ipPacket->setVersion		((unsigned char)msg->getVersion());
	ipPacket->setHeaderlength	((unsigned char)msg->getHeaderLength());
	ipPacket->setTos			(0); // no support in Omnet
	ipPacket->setTotallen		((short)msg->getByteLength()); 
	ipPacket->setIdentification (msg->getIdentification());
	ipPacket->setFlag			(IpPacket::IP_FLAG_R, false);
	ipPacket->setFlag			(IpPacket::IP_FLAG_DF, 	msg->getDontFragment());
	ipPacket->setFlag			(IpPacket::IP_FLAG_MF, 	msg->getMoreFragments());
	ipPacket->setFragoffset		(msg->getFragmentOffset());
	ipPacket->setTtl			((unsigned char)msg->getTimeToLive());
	ipPacket->setProtocol		(msg->getTransportProtocol());
	ipPacket->setChecksum		(0); // no support in Omnet
	ipPacket->setSourceip		(IP_ADDR (msg->getSrcAddress()));
	ipPacket->setDestip			(IP_ADDR (msg->getDestAddress()));
	ipPacket->setOptions		(NULL, 0); // tricky to implement

	return ipPacket;
}

Packet* NetworkInterfaceOmnetpp::convertMessage (TCPSegment* msg)
{
	TcpPacket* tcpPacket = (TcpPacket*)PacketFactory::instance()->createPacket (Packet::PROTO_TCP, distackInfo);
	tcpPacket->setSize (msg->getByteLength(), true);

	tcpPacket->setSourceport	(msg->getSrcPort());
	tcpPacket->setDestport		(msg->getDestPort());
	tcpPacket->setSequencenum	(msg->getSequenceNo());
	tcpPacket->setAcknum		(msg->getAckNo());
	tcpPacket->setHeaderlength	(TCP_HEADER_NO_OPTIONS_LEN);
	tcpPacket->setFlag			(TcpPacket::TCP_FLAG_FIN, msg->getFinBit());
	tcpPacket->setFlag			(TcpPacket::TCP_FLAG_SYN, msg->getSynBit());
	tcpPacket->setFlag			(TcpPacket::TCP_FLAG_RST, msg->getRstBit());
	tcpPacket->setFlag			(TcpPacket::TCP_FLAG_PSH, msg->getPshBit());
	tcpPacket->setFlag			(TcpPacket::TCP_FLAG_ACK, msg->getAckBit());
	tcpPacket->setFlag			(TcpPacket::TCP_FLAG_URG, msg->getUrgBit());
	tcpPacket->setFlag			(TcpPacket::TCP_FLAG_ECN, false);
	tcpPacket->setFlag			(TcpPacket::TCP_FLAG_CWR, false);
	tcpPacket->setWindowsize	((unsigned short)msg->getWindow());
	tcpPacket->setChecksum		(0);
	tcpPacket->setUrgentpointer ((unsigned short) msg->getUrgentPointer());
	tcpPacket->setOptions		(NULL, 0); // tricky to implement

	return tcpPacket;
}

Packet* NetworkInterfaceOmnetpp::convertMessage (UDPPacket* msg)
{	
	UdpPacket* udpPacket = (UdpPacket*)PacketFactory::instance()->createPacket (Packet::PROTO_UDP, distackInfo);
	udpPacket->setSize (msg->getByteLength(), true);

	udpPacket->setSourceport	(msg->getSourcePort());
	udpPacket->setDestport		(msg->getDestinationPort());
	udpPacket->setLen			((short)msg->getByteLength());
	udpPacket->setChecksum		(0); // no support from Omnet

	return udpPacket;
}

Packet* NetworkInterfaceOmnetpp::convertMessage (ICMPMessage* msg)
{
	//IcmpPacket* icmpPacket = new IcmpPacket ();
	IcmpPacket* icmpPacket = (IcmpPacket*)PacketFactory::instance()->createPacket (Packet::PROTO_ICMP, distackInfo);
	icmpPacket->setSize (msg->getByteLength(), true);

	//
	// omnet uses different icmp type values. code is the same
	//

	IcmpPacket::ICMP_TYPE type = IcmpPacket::ICMP_TYPE (0);

	switch (msg->getType()) {
		case ICMP_DESTINATION_UNREACHABLE:	type = IcmpPacket::ICMP_TYPE_DEST_UNREACHABLE;	break;
		case ICMP_REDIRECT:					type = IcmpPacket::ICMP_TYPE_REDIRECT;			break;
		case ICMP_TIME_EXCEEDED:			type = IcmpPacket::ICMP_TYPE_TIME_EXCEEDED;		break;
		case ICMP_PARAMETER_PROBLEM:		type = IcmpPacket::ICMP_TYPE_PARAM_PROBLEM;		break;
		case ICMP_ECHO_REQUEST:				type = IcmpPacket::ICMP_TYPE_ECHO_REQUEST;		break;
		case ICMP_ECHO_REPLY:				type = IcmpPacket::ICMP_TYPE_ECHO_REPLY;		break;
		case ICMP_TIMESTAMP_REQUEST:		type = IcmpPacket::ICMP_TYPE_TIMESTAMP_REQUEST;	break;
		case ICMP_TIMESTAMP_REPLY:			type = IcmpPacket::ICMP_TYPE_TIMESTAMP_REPLY;	break;
	}

	icmpPacket->setType			(type);
	icmpPacket->setCode			(msg->getCode());
	icmpPacket->setChecksum		(0); // no support from Omnet
	icmpPacket->setMisc			(0); // no support from Omnet

	return icmpPacket;
}

void NetworkInterfaceOmnetpp::setDistackModule(DistackOmnetModule* module) {
	distackModule = module;
}

#endif // OMNET_SIMULATION
