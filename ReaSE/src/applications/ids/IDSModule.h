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
#include <map>
#include <set>
#include <iostream>

using namespace std;

class Ratio {
	long long ghost_conn;
	long long real_conn; //init value
public:
	bool blocked;

public:
	Ratio() :
		ghost_conn(0), real_conn(1), blocked(false) {
	}
	;

	void incGhost() {
		++ghost_conn;
	}

	void incReal() {
		++real_conn;
	}

	double getRatio() {
		//cout << (double) ghost_conn / (double) (ghost_conn + real_conn) << endl;
		return (double) ghost_conn / (double) (ghost_conn + real_conn);
	}

	long long getGhost(){
		return this->ghost_conn;
	}
};

class INET_API IDSModule: public cSimpleModule {
public:
	void setReport(string report);
protected:
	virtual void initialize(int stage);
	virtual void handleMessage(cMessage *msg);

	virtual void finish();
	double dropRatio;
	int treshold;
	std::set<int> blockedIPs;
	std::map<uint32, Ratio> ratio_table;


};

#endif /* IDSMODULE_H_ */

