/**
 * @file Classifier.cc
 * @brief An implementation of the Classifier Managed Object.
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

#include "Classifier.h"
#include "UDPSocket.h"
#include "FlowExporter.h"
#include "flow_message_m.h"
#include <cstdlib>
#include <string>
#include <ctime>
#include "EventPublisher.h"
#include "MechanismExporter.h"

using std::cout;
using std::string;

Define_Module (Classifier);

/** This method is used to initialise the classifer during simulation start up.
 *  @param stage The initialisation stage number
 */
void Classifier::initialize(int stage)
{
	EV << "Classifier initialised!\n";
	//Initialise the counting of packets to 0
	packetCount = 0;
	//Create a new socket for the Flow Exporter to connect to
	UDPSocket socket;
	socket.setOutputGate(gate("out"));
	socket.bind(2055);
	//Register classifier with the mechanism exporter
	mechanism_exporter.registerClassifier(this, (this->getFullPath()));
	//Set initial values for the generation of false positives and false negatives
	false_positive = 0;
	false_negative = 0;
	//Set RNG seed
	srand ( time(0) );
}

/** This method handles incoming packets passed from other modules.
 *  @param message The message passed from another module
 */
void Classifier::handleMessage(cMessage *message)
{
	EV << "Classifier received a message!\n";
	packetCount++;
	//Check if it is a packet
	if (message->isPacket()) {
		//Cast to a packet
		cPacket *packet = check_and_cast<cPacket *>(message);
		//Cast to a Flow_Message
		Flow_Message *flow_message = check_and_cast<Flow_Message *>(packet);
		//Get the Flow stored within
		Flow flow = flow_message->getFlow();
		EV << flow.start_time << "\n";
		EV << flow.end_time << "\n";
		//Create a new random number for classification
		int classification = (rand()%10)+1;
		//Create an EventPublisher to facilitate the publishing of an event
		EventPublisher publisher;
		//Create a vector for use in the publishing of the event
		vector<string> values;
		//Retrieve the protocol of the flow
		int protocol = flow.protocol;
		//Cast the protocol to an integer
		std::string protocol_to_int;
		std::stringstream out;
		out << protocol;
		protocol_to_int = out.str();
		//Calculate a probability (0-99)
		int probability = rand() % 100;
		//Classify flow if it has already been identified as an attack and is not a false negative
		if (flow.attack_tag==true && (probability > false_negative)) {
			//Push values into vector and publish to Ponder2
			values.push_back(this->getFullPath());
			values.push_back(flow.source_ip.str());
			values.push_back(flow.destination_ip.str());
			values.push_back(protocol_to_int);
			publisher.publish("classification",values);
			cerr << "Classification." << endl;
		//Classify flow as a false positive
		} else if (probability < false_positive){
			//Push values into vector and publish to Ponder2
			values.push_back(this->getFullPath());
			values.push_back(flow.source_ip.str());
			values.push_back(flow.destination_ip.str());
			values.push_back(protocol_to_int);
			publisher.publish("classification",values);
			cerr << "False Positive." << endl;
		}
	}
}

/** This method used to record values to file at simulation end. */
void Classifier::finish()
{
	EV << "Classifier finished!\n";
	//Record stats to results file
	recordScalar("Packets seen", packetCount);
}

