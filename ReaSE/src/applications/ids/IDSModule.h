/**
 * @file IDSModule.h
 * @brief Header file to support the implementation of the Intrusion Detection System Managed Object.
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

#ifndef IDSMODULE_H_
#define IDSMODULE_H_

#include "INETDefs.h"
#include "IPAddress.h"
#include <string>

using namespace std;

class INET_API IDSModule : public cSimpleModule
{
protected:
    virtual void initialize(int stage);
    virtual void handleMessage(cMessage *msg);

	virtual void finish();
	long packetCount;
public:
	char* victim_ip;
	  virtual void setReport(string action);
};

//Definition of IDS 
class IDS: cObject {
public:
	IPAddress destination_ip;
	unsigned int packet_count;
	bool seen;
	bool start;
	IDS();
	~IDS();
};

#endif /* IDSMODULE_H_ */


