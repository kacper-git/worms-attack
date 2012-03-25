/**
 * @file MechanismExporter.cc
 * @brief Used to register the various instances of managed objects and export their control mechanisms to Ponder2.
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

#include "MechanismExporter.h"
#include "EventPublisher.h"
#include "FlowExporter.h"
#include "Classifier.h"
#include "IDSModule.h"
#include "FlowExporterControl.h"
#include "RateLimiterControlLink.h"
#include "RateLimiterControlFlow.h"
#include "RateLimiterControlIP.h"
#include "IDSControl.h"
#include "RateLimiter.h"
#include <tr1/unordered_map>

static bool hasStarted;

FlowPointerTable flow_exporter_pointer_table;
ClassifierPointerTable classifier_pointer_table;
RatePointerTable rate_limiter_pointer_table;
IDSPointerTable ids_pointer_table;

void *run_server(void *arg)
{
	cout << "Running XML-RPC server (C++)..." << endl;

	xmlrpc_c::registry myRegistry;

	xmlrpc_c::methodPtr const FlowExporterControlP(new FlowExporterControl);
	myRegistry.addMethod("flowexporter_one.setthreshold", FlowExporterControlP);

	xmlrpc_c::methodPtr const RateLimiterControlLinkP(new RateLimiterControlLink);
	myRegistry.addMethod("ratelimiter_one.limitlink", RateLimiterControlLinkP);

	xmlrpc_c::methodPtr const RateLimiterControlIPP(new RateLimiterControlIP);
	myRegistry.addMethod("ratelimiter_one.limitip", RateLimiterControlIPP);

	xmlrpc_c::methodPtr const RateLimiterControlFlowP(new RateLimiterControlFlow);
	myRegistry.addMethod("ratelimiter_one.limitflow", RateLimiterControlFlowP);

	xmlrpc_c::methodPtr const IDSControlP(new IDSControl);
		myRegistry.addMethod("ids_one.togglereport", IDSControlP);

	xmlrpc_c::serverAbyss myAbyssServer(myRegistry, 8080, "/tmp/xmlrpc_log");
	myAbyssServer.run();

	//xmlrpc_c::serverAbyss* server = static_cast<xmlrpc_c::serverAbyss*>(arg);
	//server->run();
}

MechanismExporter::MechanismExporter()
{
	pthread_t serverThread;
	int threadId;
	char *message = "Server Thread";

	if (!hasStarted)
	{
		cout << "Mechanism Exporter!!!" << endl;
	    threadId = pthread_create(&serverThread, NULL, run_server, (void *) message);//&myAbyssServer);
	    hasStarted = true;
	    cout << "Server started!!!" << endl;

	    cout << "\t \t Test publishing event" << endl;
	    cout << "\t \t To be removed after testing" << endl;
	    //vector<string> values;
	    //values.push_back("75");
	    //EventPublisher publisher;
	    //publisher.publish("highLinkUtil", values);
	}
}

MechanismExporter mechanism_exporter;

void MechanismExporter::registerFlowExporter(
		FlowExporter* flow_exporter_pointer, std::string name) {
	cerr << "Flow Exporter: " << name << endl;
	flow_exporter_pointer_table.insert(std::make_pair(name,
			flow_exporter_pointer));
}

void MechanismExporter::registerClassifier(
		Classifier* classifier_pointer, std::string name) {
	cerr << "Classifier: " << name << endl;
	classifier_pointer_table.insert(std::make_pair(name,
			classifier_pointer));
}

void MechanismExporter::registerRateLimiter( RateLimiter* rate_limiter_pointer, std::string name) {
	//Checks if module is a host - just want routers
	int match=name.find("host");
	if (match<1) {
		cerr << "Rate Limiter: " << name << endl;
		rate_limiter_pointer_table.insert(std::make_pair(name, rate_limiter_pointer));
	}
}

void MechanismExporter::registerIDS(
		IDSModule* ids_pointer, std::string name) {
	cerr << "IDS: " << name << endl;
	ids_pointer_table.insert(std::make_pair(name,
			ids_pointer));
}

MechanismExporter::~MechanismExporter() {
	// TODO Auto-generated destructor stub
}

