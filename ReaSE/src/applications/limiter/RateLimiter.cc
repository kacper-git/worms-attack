/**
 * @file RateLimiter.cc
 * @brief An implementation of the Rate Limiter Managed Object.
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
#include "RateLimiter.h"
#include "MechanismExporter.h"
#include <cstdlib>
#include <string>
#include <ctime>
#include <vector>
#include <sstream>
#include <fstream>

#include "stdlib.h"

#include "IPBlock_m.h"

using namespace std;

Define_Module ( RateLimiter);

//List of packets to be removed after processing
vector<long> to_block;

//Lists to update
vector<IPAddress> ip_block;
vector<int> ip_block_rate;
vector<bool> link_block;
vector<int> link_block_rate;
vector<unsigned int> flow_block;
vector<int> flow_block_rate;

fstream filestr;

void RateLimiter::initialize(int stage) {
	mechanism_exporter.registerRateLimiter(this, this->getFullPath());
	link_block.resize((this->gateSize("ifIn_network")) + (this->gateSize(
			"ifOut_network")));
	link_block_rate.resize((this->gateSize("ifIn_network")) + (this->gateSize(
			"ifOut_network")));
	blocked = 0;
	allowed = 0;
	count = 0;
	seen = 0;
	unseen = 0;
	filestr.open ("/home/matthewbroadbent/results.csv", fstream::in | fstream::out | fstream::app);
}

void RateLimiter::handleMessage(cMessage *message) {
	if(message->getArrivalGate()->isName("fromIDS")){
		//blockedIPs.insert(atoi(message->getName()));
		cout << "now blocking " << message->getName();
		IPBlock* msg = static_cast<IPBlock*>(message);
		cout << msg->getIPAddress() << endl;
		if (msg->getBlock())
			blockedIPs.insert(msg->getIPAddress());
		else
			blockedIPs.erase(msg->getIPAddress());
		delete message;
	}
	if (message->getArrivalGate()->isName("ifIn_ppp")) {
		if (link_block[message->getArrivalGate()->getIndex()] == true) {
			to_block.push_back(message->getId());
		}
		send(message, "ifOut_network", message->getArrivalGate()->getIndex());
	} else if (message->getArrivalGate()->isName("ifIn_network")) {
		bool to_send = true;
		//Link blocking
		unsigned int i;
		for (i = 0; i < to_block.size(); i++) {
			if (message->getId() == to_block[i]) {
				to_block.erase(to_block.begin()+i);
				//cerr << "Message could be blocked!" << endl;
				//srand ( time(NULL) );
				int probability = rand() % 100;
				if (probability <= link_block_rate[i]) {
					//cerr << "Message probability says yes!" << endl;
					blocked++;
					to_send = false;
				} else {
					allowed++;
				}
			}
		}
		//Cast to datagram and retrieve information
		cPacket *packet = check_and_cast<cPacket *> (message);
		IPDatagram *datagram = check_and_cast<IPDatagram *> (packet);
		IPAddress source_ip = datagram->getSrcAddress();
		IPAddress destination_ip = datagram->getDestAddress();

		if (blockedIPs.find(source_ip.getInt()) != blockedIPs.end()) {
			delete message;
			return;
		}

		//cerr << destination_ip << endl;
		int protocol = datagram->getTransportProtocol();
		//IP blocking
		string name = message->getName();
		if ((name.compare("udp_flood") == 0)
				|| (name.compare("SYN-Flood") == 0) || (name.compare(
				"ping_flood") == 0)) {
			//filestr << simTime().dbl() << "," << source_ip << "," << destination_ip << "," << protocol << "," << packet->getByteLength() << "," << "1" << endl;
		} else {
			//filestr << simTime().dbl() << "," << source_ip << "," << destination_ip << "," << protocol << "," << packet->getByteLength() << "," << "0" << endl;
		}
		for (i = 0; i < ip_block.size(); i++) {
			if (destination_ip == ip_block[i]) {
				//srand ( time(NULL) );
				int probability = rand() % 100;
				if (probability <= ip_block_rate[i]) {
					//cerr << "Message could be blocked!" << endl;
					to_send = false;
					blocked++;
					//cerr << "BLOCK! " << message->getArrivalTime() << endl;
				} else {
					allowed++;
				}
			}
		}
		//Flow blocking
		string string_to_hash = generateKey(source_ip.str(),
				destination_ip.str(), protocol);
		unsigned int key = DJBHash(string_to_hash);
		for (i = 0; i < flow_block.size(); i++) {
			if (key == flow_block[i]) {
				//srand ( time(NULL) );
								int probability = rand() % 100;
				if (probability <= flow_block_rate[i]) {
					to_send = false;
					blocked++;
				} else {
					allowed++;
				}
			}
		}

		if (to_send == true) {
			send(message, "ifOut_ppp", message->getArrivalGate()->getIndex());
			if (destination_ip.str().compare("0.2.0.27") == 0) {
				seen++;
			}
		} else {
			//cerr << "Message limited successfully!" << endl << endl;
			if (destination_ip.str().compare("0.2.0.27") == 0) {
				unseen++;
			}
			delete message;
		}
		if ((seen + unseen) == 10) {
			filestr << simTime().dbl() << "," << seen <<  "," << unseen << endl;
			seen = 0;
			unseen = 0;
		}
	}
}

void RateLimiter::addLinkBlock(int index, int rate) {
	if (link_block[index] == false) {
		cerr << simTime().dbl() << ": Added Link: " << index << endl;
	}

	link_block[index] = true;
	link_block_rate[index] = rate;
}

void RateLimiter::addIPBlock(string ip, int rate) {
	//link_block.erase(link_block.begin());
	//link_block_rate.erase(link_block_rate.begin());
	link_block.clear();
	link_block_rate.clear();
	char *conversion=new char[ip.size()+1];
	conversion[ip.size()]=0;
	memcpy(conversion,ip.c_str(),ip.size());
	bool to_add = true;
	for (int i = 0; i < ip_block.size(); i++) {
		if (ip_block[i]==conversion) {
			to_add = false;
		}
	}
	if (to_add == true) {
		cerr << getFullPath() << ": " << simTime().dbl() << ": Added IP: " << ip << endl;
		ip_block.push_back(conversion);
		cerr << conversion << " " << rate << endl;
		ip_block_rate.push_back(rate);
	}

}

void RateLimiter::addFlowBlock(string source, string destination, int protocol, int rate) {
	for (unsigned int i = 0; i < ip_block.size(); i++) {
		if (destination.compare(ip_block[i].str())) {
			ip_block.erase(ip_block.begin() + i);
			ip_block_rate.erase(ip_block_rate.begin()
					+ i);
		}
	}
	string string_to_hash = generateKey(source, destination, protocol);
	unsigned int hashed = DJBHash(string_to_hash);
	bool to_add = true;
	for (int i = 0; i < flow_block.size(); i++) {
		if (flow_block[i] == hashed) {
			to_add = false;
		}
	}
	if (to_add == true) {
		cerr << simTime().dbl() << ": Added Flow: " << source << " " << destination << " " << protocol << endl;
		flow_block.push_back(hashed);
		flow_block_rate.push_back(rate);
	}
	//cerr << hashed << endl;
}

string RateLimiter::generateKey(string source, string destination, int protocol) {
	std::stringstream out;
	out << protocol;
	string protocol_to_string = out.str();
	string key = source.append(destination).append(protocol_to_string);
	return key;
}

unsigned int RateLimiter::DJBHash(const std::string& str) {
	unsigned int hash = 5381;
	for (std::size_t i = 0; i < str.length(); i++) {
		hash = ((hash << 5) + hash) + str[i];
	}
	return (hash & 0x7FFFFFFF);
}

void RateLimiter::finish() {
	filestr.close();
	recordScalar("Packets blocked", blocked);
	recordScalar("Packets allowed", allowed);
}
