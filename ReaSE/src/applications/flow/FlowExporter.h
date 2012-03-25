/**
 * @file FlowExporter.h
 * @brief Header file to support the implementation of the Flow Exporter Managed Object.
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

#ifndef FLOWEXPORTER_H_
#define FLOWEXPORTER_H_

#include "INETDefs.h"
#include "IPAddress.h"

class INET_API FlowExporter : public cSimpleModule
{
protected:
    virtual void initialize(int stage);
    virtual void handleMessage(cMessage *msg);
    virtual void handleSelfMessage(cMessage *msg);
	virtual void finish();
    //Timeouts
	signed int flow_timeout;
	signed int idle_timeout;
    // Statistical measurements
	long packetCount;
	long tcpCount;
    long udpCount;
    long sctpCount;
    long otherCount;
    long benign;
    long malicious;
public:
    virtual void setTimeouts(int new_flow_timeout, int new_idle_timeout);
};

//Definition of a Flow object
class Flow: cObject {
public:
	simtime_t start_time;
	simtime_t end_time;
	IPAddress source_ip;
	IPAddress destination_ip;
	unsigned short source_port;
	unsigned short destination_port;
	unsigned short protocol;
	short version;
	int sequence_number;
	int ack_number;
	bool attack_tag;
	bool urg;
	bool ack;
	bool psh;
	bool rst;
	bool syn;
	bool fin;
	unsigned int packet_count;
	unsigned int byte_count;
	Flow();
	~Flow();
	cMessage* pointer;
};

#endif /* FLOWEXPORTER_H_ */


