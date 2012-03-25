/**
 * @file FlowExporter.cc
 * @brief An implementation of the Flow Exporter Managed Object.
 * @author Matthew Broadbent (m.broadbent@lancs.ac.uk)
 * @date 22/09/10
 * */

// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.

#include "FlowExporter.h"
#include "IPDatagram_m.h"
#include <iostream>
#include <string>
#include "TCPSegment.h"
#include "UDPPacket.h"
#include "SCTPMessage_m.h"
#include "UDPSocket.h"
#include "IPAddressResolver.h"
#include "flow_message_m.h"
#include <map>
#include <tr1/unordered_map>
#include "MechanismExporter.h"

MechanismExporter exporter;

using namespace std;

Define_Module ( FlowExporter);

//Flow record deconstructor
Flow::~Flow() {
}

//Flow record constructor
Flow::Flow() {
	start_time = 0;
	end_time = 0;
	source_ip = "0.0.0.0";
	destination_ip = "0.0.0.0";
	source_port = NULL;
	destination_port = NULL;
	protocol = NULL;
	version = 0;
	sequence_number = 0;
	ack_number = 0;
	attack_tag = false;
	urg = NULL;
	ack = NULL;
	psh = NULL;
	rst = NULL;
	syn = NULL;
	fin = NULL;
	packet_count = 1;
	byte_count = 0;
	pointer = NULL;
}

//Unordered map for storage of ongoing flow records
typedef std::tr1::unordered_map<string, Flow> FlowTable;
FlowTable table;

/** This method is used to initialise the flow exporter during simulation start up.
 *  @param stage The initialisation stage number
 */
void FlowExporter::initialize(int stage) {
	EV<< "Flow Exporter initialised!\n";
	//Initialise counters to 0
	packetCount = 0;
	tcpCount = 0;
	udpCount = 0;
	sctpCount = 0;
	otherCount = 0;
	malicious = 0;
	benign = 0;
	//Set initial idle timeout and flow timeout values
	idle_timeout = -1;
	flow_timeout = -1;
	//Register classifier with the mechanism exporter
	mechanism_exporter.registerFlowExporter(this,this->getFullPath());
}

/** This method handles packets sent by the module to itself.
 *  @param message The message passed from itself.
 */
void FlowExporter::handleSelfMessage(cMessage *message) {
	//Get the name of this message (should be the key)
	const char *message_key = message->getName();
	//Cast to string
	string key(message_key);
	//Create an iterator
	FlowTable::iterator iter;
	//Find the entry in the table that matches the key
	iter = table.find(key);
	//If the key is found
	if (iter != table.end()) {
		EV<< "Flow finished, sending! \n";
		EV << key << "\n";
		//Create a UDP socket to the classifier
		UDPSocket socket;
		socket.setOutputGate(gate("out"));
		socket.bind(2055);
		socket.connect(IPAddressResolver().resolve("Inet.sas0.host23"), 2055);
		//Retrieve the flow that belongs to that key
		Flow flow_export = iter->second;
		//Create a new Flow_Message that will store the transported flow
		Flow_Message *msg = new Flow_Message("Flow_Export",0);
		//Attach the flow
		msg->setFlow(flow_export);
		//Send message
		socket.send(msg);
		//Close the socket
		socket.close();
		//Erase the entry
		table.erase(key);
		//Set boolean to true because we have found a match
	}
	//If we haven't found a match
	else if (iter == table.end()) {
		EV << "Not found in Flow Table!";
	}
	//Delete self message
	delete message;
}

/** This method handles incoming packets passed from other modules.
 *  @param message The message passed from another module
 */
void FlowExporter::handleMessage(cMessage *message) {
	//Get sim time
	simtime_t start_time = simTime();
	//Handle self message
	if (message->isSelfMessage()) {
		//Call method to handle this self message
		handleSelfMessage(message);
	} else {
		//Duplicate message to Distack
		cMessage* distack_message = message->dup();
		//Send duplicated message to Distack
		send(distack_message, "distack");
		EV<< "Forwarding message to Distack!\n";
		EV << "Flow Exporter received a message!";
		//Check if the flow exporter has had it's timeout values set (it has not been disabled)
		if (idle_timeout != -1 && flow_timeout != -1) {
			//Check if the message is a packet
			if (message->isPacket()) {
				//Increment packet counter
				packetCount++;
				//Create a new flow
				Flow new_flow;
				//Detect attack type for classifier biasing
				string name = message->getName();
				//If the packet is that of a malicious type
				if ((name.compare("udp_flood") == 0) || (name.compare("SYN-Flood") == 0) || (name.compare("ping_flood") == 0)) {
					//Set attack tagging to true
					new_flow.attack_tag = true;
					//Incremenet counter to show we have seen a malicious packet
					malicious++;
				//Else, if the packet is not malicious
				} else {
					//Increment counter to show we have seen a benign packet
					benign++;
				}
				EV << "Message is a packet!\n";
				//Cast to a packet
				cPacket *packet = check_and_cast<cPacket *>(message);
				//Cast to a datagram
				IPDatagram *datagram = check_and_cast<IPDatagram *>(packet);
				//Get version
				short version = datagram->getVersion();
				new_flow.version = version;
				//Get source IP
				IPAddress source_ip = datagram->getSrcAddress();
				EV << source_ip << "\n";
				new_flow.source_ip=source_ip;
				//Get destination IP
				IPAddress destination_ip = datagram->getDestAddress();
				EV << destination_ip << "\n";
				new_flow.destination_ip=destination_ip;
				unsigned short protocol = NULL;
				//Get protocol number
				protocol = datagram->getTransportProtocol();
				EV << protocol << "\n";
				//Initialise values to null
				new_flow.protocol=protocol;
				unsigned short source_port = NULL;
				unsigned short destination_port = NULL;
				bool urg = NULL;
				bool ack = NULL;
				bool psh = NULL;
				bool rst = NULL;
				bool syn = NULL;
				bool fin = NULL;
				//If it is a TCP packet
				if (protocol == 6) {
					//Increment counter to show that we have seen a TCP packet
					tcpCount++;
					//Cast to a TCP segment
					TCPSegment *tcpsegment = check_and_cast<TCPSegment*>(datagram->getEncapsulatedMsg());
					//Get source port
					source_port = tcpsegment->getSrcPort();
					EV << source_port << "\n";
					new_flow.source_port=source_port;
					//Get destination port
					destination_port = tcpsegment->getDestPort();
					EV << destination_port << "\n";
					new_flow.destination_port=destination_port;
					//Get sequence number
					int sequence_number = tcpsegment->getSequenceNo();
					new_flow.sequence_number = sequence_number;
					//Get ACK number
					int ack_number = tcpsegment->getAckNo();
					new_flow.ack_number = ack_number;
					//Get URG bit
					urg = tcpsegment->getUrgBit();
					new_flow.urg=urg;
					//Get ACK bit
					ack = tcpsegment->getAckBit();
					new_flow.ack=ack;
					//Get PSH bit
					psh = tcpsegment->getPshBit();
					new_flow.psh=psh;
					//Get RST bit
					rst = tcpsegment->getRstBit();
					new_flow.rst=rst;
					//Get SYN bit
					syn = tcpsegment->getSynBit();
					new_flow.syn=syn;
					//Get FIN bit
					fin = tcpsegment->getFinBit();
					new_flow.fin=fin;
					//If it is a UDP packet
				} else if (protocol == 17) {
					//Increment counter to show that we have seen a UDP packet
					udpCount++;
					//Cast to a UDP packet
					UDPPacket* udppacket = check_and_cast<UDPPacket*>(datagram->getEncapsulatedMsg());
					//Get source port
					source_port = udppacket->getSourcePort();
					new_flow.source_port=source_port;
					//Get destination port
					destination_port = udppacket->getDestinationPort();
					new_flow.destination_port=destination_port;
					//If it is a SCTP packet
				} else if (protocol == 132) {
					//Increment counter to show that we have seen a SCTP packet
					sctpCount++;
					//Cast to a SCTP message
					SCTPMessage_Base* sctppacket = check_and_cast<SCTPMessage_Base*>(datagram->getEncapsulatedMsg());
					//Get source port
					source_port = sctppacket->getSrcPort();
					new_flow.source_port=source_port;
					//Get destination port
					destination_port = sctppacket->getDestPort();
					new_flow.destination_port=destination_port;
					//Handle the remaining protocols
				} else {
					//If it's a different protocol - not sure any others are entered
					otherCount++;
				}
				//Cast the source address to string
				string source_string = source_ip.str();
				//Cast the destination address to string
				string destination_string = destination_ip.str();
				//Cast the protocol to string
				std::string protocol_string;
				std::stringstream out;
				out << protocol;
				protocol_string = out.str();
				//Create key using the source, destination and protocol concatentated together
				string key = source_string + ":" + destination_string + ":" + protocol_string;
				//Cast this string to a character array
				char *message_key = (char*)key.c_str();
				EV << key;
				//Create an expiry message
				cMessage *expiry_message = new cMessage(message_key);
				//Create a timeout message
				cMessage *timeout_message = new cMessage(message_key);
				//Set boolean to show we have't seen this flow before
				bool found = false;
				//Create a new iterator
				FlowTable::iterator iter;
				//Find the record with that key in the table
				iter = table.find(key);
				//If a record with that key exists in the table
				if (iter != table.end()) {
					//Cancel any forthcoming expiry messages
					cancelEvent(iter->second.pointer);
					//Increment packet count
					iter->second.packet_count++;
					//Increment byte count
					unsigned int byte_count = packet->getByteLength();
					iter->second.byte_count = iter->second.byte_count + byte_count;
					//Set finish time
					iter->second.end_time = simTime();
					//Set boolean to show we have seen this flow before
					found = true;
					//If expiry is inside the timeout window
					if (((iter->second.start_time)+flow_timeout) > (simTime() + idle_timeout)) {
						//Reschedule message
						scheduleAt(simTime()+idle_timeout, expiry_message);
						//Renew pointer
						iter->second.pointer = expiry_message;
					}
				//If that key does not exist in the table
				} else if (iter == table.end()) {
					//Schedule timeout
					scheduleAt(simTime()+flow_timeout, timeout_message);
					//Schedule expiry
					scheduleAt(simTime()+idle_timeout, expiry_message);
					//Set start time and initial end time
					new_flow.start_time = start_time;
					new_flow.end_time = start_time;
					//Save pointer so that we can safely destroy scheduled message if need be
					new_flow.pointer = expiry_message;
					//Set initial byte count
					unsigned int byte_count = packet->getByteLength();
					new_flow.byte_count = byte_count;
					//Add to table
					table.insert( std::make_pair(key,new_flow) );
				}
				delete message;
			}
			//If the message is not a packet
			else
			{
				EV << "Message is not a packet!\n";
			}
		}
	}

}

/** This method used to record values to file at simulation end. */
void FlowExporter::finish() {
	EV<< "Flow Exporter finished!\n";
	//Record stats to results file
	recordScalar("Packets seen", packetCount);
	recordScalar("TCP packets seen", tcpCount);
	recordScalar("UDP packets seen", udpCount);
	recordScalar("SCTP packets seen", sctpCount);
	recordScalar("Other packets seen", otherCount);
}

/** This method handles incoming packets passed from other modules.
 *  @param new_flow_timeout Value for the new flow timeout
 *  @param new_idle_timeout Value for the new idle timeout
 */
void FlowExporter::setTimeouts(int new_flow_timeout, int new_idle_timeout) {
	//Set the global value for the flow timeout (longest period a flow can exist for)
	flow_timeout = new_flow_timeout;
	//Set the global value for the idle timeout (longest period a flow can exist for without seeing any more packets from the same set of tuples)
	idle_timeout = new_idle_timeout;
}
