/**
 * @file EventPublisher.h
 * @brief Header file to support the publishing of events from the simulation to the Ponder2 broker.
 * @author Alberto Egon Schaeffer Filho (asf@comp.lancs.ac.uk)
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

#ifndef EVENTPUBLISHER_H_
#define EVENTPUBLISHER_H_

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <iostream>
#include <vector>

using namespace std;

class EventPublisher {
public:
	EventPublisher();
	EventPublisher(string s, int p);
	virtual ~EventPublisher();
	void publish(string event, vector<string> args);
private:
	string serverName;
	int portNumber;
};

#endif /* EVENTPUBLISHER_H_ */
