#ifndef __NETWORK_INTERFACE_OMNETPP_H
#define __NETWORK_INTERFACE_OMNETPP_H

#ifdef OMNET_SIMULATION

#include "base/network/NetworkInterface.h"
#include "base/protocol/PacketFactory.h"
#include "base/common/Helper.h"
#include "base/common/DistackInfo.h"
#include <cmath>
#include <queue>
#include <deque>
#include <boost/thread/mutex.hpp>

#pragma warning (disable : 4244 4800 4267)
#include <omnetpp.h>
#include <IPDatagram.h>
#include <ICMPMessage.h>
#include <TCPSegment.h>
#include <UDPPacket.h>
#pragma warning (default : 4244 4800 4267)

using std::queue;
using std::deque;

class FrameDistribution; // forward decl
class DistackOmnetModule;

class NetworkInterfaceOmnetpp : public NetworkInterface {
public:
	NetworkInterfaceOmnetpp( DistackInfo* info );
	~NetworkInterfaceOmnetpp();

	void setFrameDistribution( FrameDistribution* distrib );

	//
	// functions from NetworkInterface inheritance
	//

	bool open();
	bool close();
	Frame* read();

	friend class			DistackOmnetModule;	

	void					setDistackModule					(DistackOmnetModule* module);

private:

	void					handleMessage					(cPacket* msg);
	void					handleProtocolMessage			(cPacket* msg);

	Frame*					convertOmnetToDistack			(cPacket* message);	
	Packet*					convertMessage					(IPDatagram* msg);
	Packet*					convertMessage					(TCPSegment* msg);
	Packet*					convertMessage					(UDPPacket* msg);
	Packet*					convertMessage					(ICMPMessage* msg);

	FrameDistribution*		frameDistribution;
	DistackOmnetModule*		distackModule;

};

#endif // OMNET_SIMULATION
#endif // __NETWORK_INTERFACE_OMNETPP_H
