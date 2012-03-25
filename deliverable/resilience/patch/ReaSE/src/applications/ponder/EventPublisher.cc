/**
 * @file EventPublisher.cc
 * @brief Used to publish events from the simulation to the Ponder2 broker.
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

#include "EventPublisher.h"

const int DEFAULT_PORT = 4444;

EventPublisher::EventPublisher() {
	serverName = "localhost";
	portNumber = DEFAULT_PORT;
}

EventPublisher::EventPublisher(string s, int p) {
	serverName = s;
	portNumber = p;
}

EventPublisher::~EventPublisher() {
	// TODO Auto-generated destructor stub
}

void EventPublisher::publish(string event, vector<string> args)
{
    int sock;
    char data[1024];
    struct hostent *host;
    struct sockaddr_in server_addr;

    host = gethostbyname(serverName.c_str());

    // opens the socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        cerr << "Could not open the socket!" << endl;
    }

    // initialises the address struct
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(4444);
    server_addr.sin_addr = *((struct in_addr *) host -> h_addr);
    bzero(&(server_addr.sin_zero),8);

    // connects to the socket
    if (connect(sock, (struct sockaddr *) &server_addr, sizeof(struct sockaddr)) == -1)
    {
    	cerr << "Could not connect to the socket!" << endl;
    }

    string outputLine = event + ";";
    for (int i = 0; i < args.size(); i++)
    {
    	outputLine = outputLine + args[i] + ";";
    }

    //cout << "Publishing " << outputLine << endl;

    // sends the event into the socket
    strcpy(data, outputLine.c_str());
    send(sock, data, strlen(data), 0);

    //closes the socket
    close(sock);
}
