/**
 * @file IDSModule.cc
 * @brief An implementation of the Intrusion Detection System Managed Object.
 * @author Florian Hagenauer & Kacper Surdy
 * @date 13.04.2012
 * */

#include "IDSModule.h"
#include "IPDatagram_m.h"
#include <iostream>
#include <string>
#include "TCPSegment.h"
#include "UDPPacket.h"
#include "SCTPMessage_m.h"
#include "UDPSocket.h"
#include "IPAddressResolver.h"
//#include "IDS_message_m.h"
#include <map>
#include <tr1/unordered_map>
#include "MechanismExporter.h"
#include <string>
#include "EventPublisher.h"

#include "stdlib.h"
#include "ICMPMessage_m.h"
#include "IPControlInfo.h"
#include "IPBlock_m.h"

using std::cout;
using std::endl;

bool report;

Define_Module ( IDSModule)
;

//Initialize
void IDSModule::initialize(int stage) {
	EV<< "IDS initialised!\n";
	mechanism_exporter.registerIDS(this, this->getFullPath());
	dropRatio = par("dropRatio");
	treshold = par("treshold");
}

void IDSModule::handleMessage(cMessage *message) {

	if (!message->isPacket()) {
		send(message, "distack");
		return;
	}

	// With this casts you get the type of the message
	//cPacket *packet = check_and_cast<cPacket *> (message);
	IPDatagram *datagram = static_cast<IPDatagram *> (message);

	/* TRESHOLD
	 string name = datagram->getName();
	 bool worm = false;
	 if ((name.compare("messageworm_udp") == 0) || (name.compare("worm_udp")
	 == 0)) {
	 worm = true;
	 }
	 bool isicmp = false;
	 if (datagram->getTransportProtocol() == IP_PROT_ICMP) {
	 try {
	 cPacket * encap = datagram->decapsulate(); // getting the encapsulated ICMP message
	 ICMPMessage *icmp = dynamic_cast<ICMPMessage *> (encap);

	 if (icmp && icmp->getType() == ICMP_DESTINATION_UNREACHABLE) {
	 isicmp = true;
	 // if the message is an destination error -> increase ghost messages
	 //cout << datagram->getDestAddress() << endl;
	 ratio_table[datagram->getDestAddress().getInt()].incGhost();
	 //if(ratio_table.size() > 1000){
	 //			cout << "ratio_table" << ratio_table.size() << endl;
	 //		}
	 }
	 datagram->encapsulate(encap); // encapsulate the message again for sending
	 } catch (cRuntimeError e) {
	 //do nothing
	 }
	 }

	 if (!isicmp && ratio_table[datagram->getSrcAddress().getInt()].getGhost()
	 >= treshold) {
	 blockedIPs.insert(datagram->getSrcAddress().getInt());
	 if (worm) {
	 //cout << "worm from " << datagram->getSrcAddress()
	 //		<< " blocked, ghost: "
	 //		<< ratio_table[datagram->getSrcAddress().getInt()].getGhost()
	 //		<< endl;
	 }
	 } else {
	 if (worm) {
	 //cout << "worm from " << datagram->getSrcAddress()
	 //		<< " NOT blocked, ghost: "
	 //		<< ratio_table[datagram->getSrcAddress().getInt()].getGhost()
	 //		<< endl;
	 }
	 send(message, "distack");
	 }
	 */

	// RATIO
	string name = datagram->getName();
	bool worm = false;
	if ((name.compare("messageworm_udp") == 0) || (name.compare("worm_udp")
			== 0)) {
		//std::cout << "Worm detected!" << endl;
		worm = true;
	}
	bool isicmp = false;
	if (datagram->getTransportProtocol() != IP_PROT_ICMP) {
		ratio_table[datagram->getSrcAddress().getInt()].incReal(); // if the message is not an error
	} else {
		try {
			cPacket * encap = datagram->decapsulate(); // getting the encapsulated ICMP message
			ICMPMessage *icmp = dynamic_cast<ICMPMessage *> (encap);

			if (icmp && icmp->getType() == ICMP_DESTINATION_UNREACHABLE) {
				isicmp = true;
				// if the message is an destination error -> increase ghost messages
				//cout << datagram->getDestAddress() << endl;
				Ratio& ratio = ratio_table[datagram->getDestAddress().getInt()];
				ratio.incGhost();
				//if(ratio_table.size() > 1000){
				//			cout << "ratio_table" << ratio_table.size() << endl;
				//		}
				if (!ratio.blocked && ratio.getRatio() > dropRatio) {
					cerr << getFullPath() << ": " << simTime().dbl() << ": IP: " << datagram->getDestAddress().str() << " sent to ponder" << endl;
					ratio.blocked = true;
					vector<string> values;
					values.push_back(datagram->getDestAddress().str());
					EventPublisher publisher;
					publisher.publish("intrusion",values);
				}
			} else {
				ratio_table[datagram->getSrcAddress().getInt()].incReal(); // other ICMP messages
			}
			datagram->encapsulate(encap); // encapsulate the message again for sending
		} catch (cRuntimeError e) {
			//do nothing
		}
	}

	if (false && !isicmp && ratio_table[datagram->getSrcAddress().getInt()].getRatio() > dropRatio) {
		/* !! BLOCK DISABLED !! */

		//char name;
		//sprintf("%d", datagram->getSrcAddress().getInt());
		IPBlock *block = new IPBlock("Block message", 0);
		block->setIPAddress(datagram->getSrcAddress().getInt());
		block->setBlock(true);
		send(block, "toRateLimiter");
		blockedIPs.insert(datagram->getSrcAddress().getInt());
		if (worm) {
			//cout << "worm from " << datagram->getSrcAddress() << " blocked, ratio: "
			//		<< ratio_table[datagram->getSrcAddress().getInt()].getRatio()
			//		<< endl;
		}
	} else {
		if (worm) {
			//	cout << "worm from " << datagram->getSrcAddress()
			//			<< " NOT blocked, ratio: "
			//			<< ratio_table[datagram->getSrcAddress().getInt()].getRatio()
			//			<< endl;
		}
		send(message, "distack");
	}

}

void IDSModule::finish() {
	recordScalar("#blocked IPs", blockedIPs.size());
	EV<< "IDS finished!\n";
}

void IDSModule::setReport(string report) {

}
