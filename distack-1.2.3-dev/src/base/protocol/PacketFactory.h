#ifndef __PACKET_FACTORY_H
#define __PACKET_FACTORY_H

#include "Packet.h"
#include "EthernetPacket.h"
#include "IpPacket.h"
#include "TcpPacket.h"
#include "UdpPacket.h"
#include "IcmpPacket.h"
#include "PayloadPacket.h"
#include "ArpPacket.h"
#include "Ipv6Packet.h"
#include "MplsPacket.h"
#include "Frame.h"
#include "base/common/DistackInfo.h"

class Configuration;

//
// this flag control whether the packetfactory
// uses the boost::pool lib or normal new and free
// memory allocation
//
// #define PACKET_FACTORY_NORMAL_ALLOCATION	1
//

#ifdef _CRTDBG_MAP_ALLOC
	// boost::pool does not work with memory debugging
	#undef PACKET_FACTORY_NORMAL_ALLOCATION	
#endif 

#ifndef PACKET_FACTORY_NORMAL_ALLOCATION
	#ifdef WIN32
 #define WIN32_LEAN_AND_MEAN
	#endif // WIN32
	#include <boost/pool/poolfwd.hpp>
	#include <boost/pool/object_pool.hpp>
#endif

class PacketFactory {
public:
	static void reference( PacketFactory* factory );
	static PacketFactory* instance();

	Packet* createPacket( Packet::PROTOCOL protocol, DistackInfo* info );
	Frame* createFrame( DistackInfo* info );

	void freePacket( Packet* packet );
	void freeFrame( Frame* frame );

private:
     PacketFactory();
     ~PacketFactory();

	class Guard {
	public: ~Guard() {
 		if (PacketFactory::object != NULL && destroy)
  		delete PacketFactory::object;
 		}
	};

	friend class Guard;
	static PacketFactory* object;
	static bool destroy;

#ifndef PACKET_FACTORY_NORMAL_ALLOCATION
	boost::object_pool <Frame>           poolFrame;
	boost::object_pool <EthernetPacket>  poolEthernetPacket;
	boost::object_pool <ArpPacket>       poolArpPacket;
	boost::object_pool <MplsPacket>      poolMplsPacket;
	boost::object_pool <IpPacket>        poolIpPacket;
	boost::object_pool <Ipv6Packet>      poolIpv6Packet;
	boost::object_pool <IcmpPacket>      poolIcmpPacket;
	boost::object_pool <UdpPacket>       poolUdpPacket;
	boost::object_pool <TcpPacket>       poolTcpPacket;
	boost::object_pool <PayloadPacket>   poolPayloadPacket;
#endif
};

inline PacketFactory* PacketFactory::instance(){
	static Guard guard;

	if (object == NULL) {
 		object  = new PacketFactory ();
 		destroy = true;
	}
	
	return object;
}

#endif // __PACKET_FACTORY_H
