/**
 * @file IDSModule.cc
 * @brief An implementation of the Intrusion Detection System Managed Object.
 * @author Tina Yu (tinayu@it.usyd.edu.au)
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

#include "IDSModule.h"
#include "IPDatagram_m.h"
#include <iostream>
#include <string>
#include "TCPSegment.h"
#include "UDPPacket.h"
#include "SCTPMessage_m.h"
#include "UDPSocket.h"
#include "IPAddressResolver.h"
#include "IDS_message_m.h"
#include <map>
#include <tr1/unordered_map>
#include "MechanismExporter.h"
#include <string>
#include "EventPublisher.h"

using namespace std;

bool report;

Define_Module ( IDSModule);

IDS::~IDS() {

}

IDS::IDS() {
	destination_ip = "0.0.0.0";
	packet_count = 1;
	seen = false;
}

typedef std::tr1::unordered_map<string, IDS> IDSTable;
IDSTable tableIDS;

//Initialise
void IDSModule::initialize(int stage) {
	EV<< "IDS initialised!\n";
	packetCount = 0;
	mechanism_exporter.registerIDS(this, this->getFullPath());
	report = false;
}

void IDSModule::handleMessage(cMessage *message) {
	//Get sim time
	simtime_t current_time = simTime();



		if (message->isPacket()) {
			packetCount++;
			EV<< "\nTotal number of packets: " << packetCount << "\n";
			IDS new_IDS;
			//Cast to a packet
			cPacket *packet = check_and_cast<cPacket *>(message);
			//Cast to a datagram
			IPDatagram *datagram = check_and_cast<IPDatagram *>(packet);
			//Get destination IP
			IPAddress destination_ip = datagram->getDestAddress();
			new_IDS.destination_ip=destination_ip;

			string destination_string = destination_ip.str();

			string key = destination_string;

			//string SAS1[] = {"0.2.0.15" , "0.2.0.16" , "0.2.0.17" , "0.2.0.18" , "0.2.0.19" , "0.2.0.20" , "0.2.0.21" , "0.2.0.22" , "0.2.0.23" , "0.2.0.24" , "0.2.0.25" , "0.2.0.26" , "0.2.0.27" , "0.2.0.28" , "0.2.0.29" , "0.2.0.30" , "0.2.0.31" , "0.2.0.32" , "0.2.0.33"};
			IDSTable::iterator iter;
			//EV<< "\nIDS Table" << "\n";

			//for ( iter = tableIDS.begin(); iter != tableIDS.end(); iter++ ) {
			//for (int x = 0; x < 19; x++) {

			//if (iter->first == SAS1[x]) {
			//	EV<< iter->first << " Packets Number: " << iter->second.packet_count << "\n";

			iter = tableIDS.find(key);
			if (iter != tableIDS.end()) {
				EV<< "Repeat IP: "<< key;
				//Increase packet count
				iter->second.packet_count++;
				unsigned int c = iter->second.packet_count;
				float prob = float(c)/float(packetCount);
				if (prob > 0.7) {

					simtime_t detection_time = simTime();

					char * current_ip=(char *)(iter->first.c_str());
					static char victim_ip[10];

					if (strcmp(current_ip, victim_ip)!=0) {
						strcpy(victim_ip, current_ip);
					}
					else {

						if ((report == true) && iter->second.seen == false) {
							iter->second.seen = true;
							vector<string> values;
							values.push_back(iter->first);
							EventPublisher publisher;
							publisher.publish("intrusion",values);
						}
						EV << "Found Victim!\n" << "Victim IP: " << iter->first <<"\n";
					}

				}
			} else if (iter == tableIDS.end()) {
				tableIDS.insert( std::make_pair(key,new_IDS) );
			}
		}

	send(message,"distack");
}

void IDSModule::setReport(string action) {
	if (action.compare("on") == 0) {
		report = true;
	} else if (action.compare("off") == 0) {
		report = false;
	}
}

void IDSModule::finish() {
	EV<< "IDS finished!\n";
}
