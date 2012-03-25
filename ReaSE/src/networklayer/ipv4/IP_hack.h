#ifndef IP_HACK_H_
#define IP_HACK_H_

#include <omnetpp.h>
#include "IP.h"
#include "IPDatagram_hacked_m.h"
#include "ReaSEDefs.h"

/**
 * @brief Extension of the original IP protocol.
 *
 * Extends the original IP protocol of INET by address spoofing,
 * packet tracing, packet copying to attack detection instances, 
 * and router alert option.
 * These tasks are necessary for simulation of attacks, attack
 * detection, and signalling.
 */
class REASE_API IP_hack : public IP
{
protected:
	// service flags
	bool copyFlag, raoActive, tracingOn, spoofingAllowed;

	// statistics
	cOutVector output, tcpout, udpout, icmpout;

	// state
	bool startTrace;
	int totalTrace, udpTrace, tcpTrace, icmpTrace;
	int totalPackets, udpPackets, tcpPackets, icmpPackets;
	double traceInterval;
	cMessage *traceMsg;

public:
	IP_hack();
	virtual ~IP_hack();
	/// Dispatch received message to correct handler
	virtual void endService(cPacket *msg);
	void finish();
protected:
	virtual void initialize();
	/// Includes new feature: Address spoofing
	IPDatagram *encapsulate(cPacket *transportPacket, InterfaceEntry *&destIE);
	/// Outputs packet counts into vector file
	virtual void handleMessage(cMessage *msg);
	/// Generate new packet with RAO set
	virtual void handlePacketFromRAOControl(cPacket *msg);
	/// Forwards incoming packets from raoControl without processing
	virtual void handlePacketFromRAOControl(IPDatagram *datagram);
	/// Handle messages from higher layers
	virtual void handleMessageFromHL(cPacket *msg);
	/// Handle messages from lower layers
	virtual void handlePacketFromNetwork(IPDatagram *datagram);
	/// Processing of IP options and RAO option
	virtual void processPacket(IPDatagram *datagram, InterfaceEntry *destIE, bool fromHL, bool checkOpts);
	/// Handle changes in module parameters
        virtual void handleParameterChange(const char *parname);
};

#endif /*IP_HACK_H_*/
