#include "PacketFactory.h"

#include "base/configuration/Configuration.h"

PacketFactory* PacketFactory::object = NULL;
bool PacketFactory::destroy = false;

void PacketFactory::reference (PacketFactory* factory)
{
	destroy = false;
	object  = factory;
}

PacketFactory::PacketFactory ()
{
}

PacketFactory::~PacketFactory ()
{
}

Packet* PacketFactory::createPacket (Packet::PROTOCOL protocol, DistackInfo* info)
{
	Packet* ret = NULL;

	switch (protocol) {
		case Packet::PROTO_ETHERNET: 
			{
#ifdef PACKET_FACTORY_NORMAL_ALLOCATION
				ret = new EthernetPacket ();
#else
				ret	= poolEthernetPacket.construct ();
#endif
				break;
			}
		case Packet::PROTO_ARP:
			{
#ifdef PACKET_FACTORY_NORMAL_ALLOCATION
				ret = new ArpPacket ();
#else
				ret	= poolArpPacket.construct ();
#endif
				break;
			}
		case Packet::PROTO_ICMP:	
			{
#ifdef PACKET_FACTORY_NORMAL_ALLOCATION
				ret = new IcmpPacket ();
#else
				ret	= poolIcmpPacket.construct ();
#endif
				break;
			}
		case Packet::PROTO_IP:
			{
#ifdef PACKET_FACTORY_NORMAL_ALLOCATION
				ret = new IpPacket ();
#else	
				ret	= poolIpPacket.construct ();
#endif
				break;
			}
		case Packet::PROTO_IPV6:
			{
#ifdef PACKET_FACTORY_NORMAL_ALLOCATION
				ret = new Ipv6Packet ();
#else
				ret  = poolIpv6Packet.construct (); 
#endif
				break;
			}
		case Packet::PROTO_TCP:
			{
#ifdef PACKET_FACTORY_NORMAL_ALLOCATION
				ret = new TcpPacket ();
#else
				ret	= poolTcpPacket.construct ();
#endif
				break;
			}
		case Packet::PROTO_UDP:
			{	
#ifdef PACKET_FACTORY_NORMAL_ALLOCATION
				ret = new UdpPacket ();
#else
				ret	= poolUdpPacket.construct ();
#endif
				break;
			}
		case Packet::PROTO_DATA_PAYLOAD:
			{
#ifdef PACKET_FACTORY_NORMAL_ALLOCATION
				ret = new PayloadPacket ();
#else
				ret	= poolPayloadPacket.construct ();
#endif
				break;
			}
		case Packet::PROTO_MPLS:
			{
#ifdef PACKET_FACTORY_NORMAL_ALLOCATION
				ret = new MplsPacket ();
#else
				ret	= poolMplsPacket.construct ();
#endif
				break;
			}
		case Packet::PROTO_NONE:
		default:
			{
				ret	= NULL;
				break;
			}
	} // switch (nextProtocol) 

	if(ret != NULL) {
		ret->setChecksumValidation(Configuration::instance(info)->getChecksumCheck ());
	}
	return ret;
}

Frame* PacketFactory::createFrame (DistackInfo* info)
{
	Frame* ret = NULL;
#ifdef PACKET_FACTORY_NORMAL_ALLOCATION
	ret = new Frame ();
#else
	ret = poolFrame.construct ();
#endif
	ret->buildFrame( info );
	return ret;
}

void PacketFactory::freePacket (Packet* packet)
{
	if (packet == NULL) return;

#ifdef PACKET_FACTORY_NORMAL_ALLOCATION
	delete packet;
#else
	Packet::PROTOCOL protocol = packet->getProtocol ();
	switch (protocol) {
		case Packet::PROTO_ETHERNET:		poolEthernetPacket.destroy	((EthernetPacket*)	packet); 	break;
		case Packet::PROTO_ARP:				poolArpPacket.destroy		((ArpPacket*)		packet); 	break;
		case Packet::PROTO_ICMP:			poolIcmpPacket.destroy		((IcmpPacket*)		packet); 	break;
		case Packet::PROTO_IP:				poolIpPacket.destroy		((IpPacket*)		packet); 	break;
		case Packet::PROTO_IPV6:			poolIpv6Packet.destroy		((Ipv6Packet*)		packet); 	break;
		case Packet::PROTO_TCP:				poolTcpPacket.destroy		((TcpPacket*)		packet); 	break;
		case Packet::PROTO_UDP:				poolUdpPacket.destroy		((UdpPacket*)		packet); 	break;
		case Packet::PROTO_DATA_PAYLOAD:	poolPayloadPacket.destroy	((PayloadPacket*)	packet); 	break;
		case Packet::PROTO_MPLS:			poolMplsPacket.destroy		((MplsPacket*)		packet);	break;
		default:							assert (false); free (packet);								break;		
	} // switch (nextProtocol) 

#endif
}

void PacketFactory::freeFrame (Frame* frame)
{
#ifdef PACKET_FACTORY_NORMAL_ALLOCATION
	delete frame;
#else
	poolFrame.destroy (frame);
#endif
}
