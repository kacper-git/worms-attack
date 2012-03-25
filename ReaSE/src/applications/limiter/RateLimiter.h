/**
 * @file RateLimiter.h
 * @brief Header file to support the implementation of the Rate Limiter Managed Object.
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

#ifndef RATELIMITER_H_
#define RATELIMITER_H_

#include "INETDefs.h"
#include "IPAddress.h"
#include <string>

using namespace std;

class INET_API RateLimiter : public cSimpleModule
{
protected:
    virtual void initialize(int stage);
    virtual void handleMessage(cMessage *msg);
	virtual void finish();
	string generateKey(string source, string destination, int protocol);
	unsigned int DJBHash(const std::string& str);
	long blocked;
	long allowed;
	double count;
	long seen;
	long unseen;

public:
	virtual void addLinkBlock(int index, int rate);
	virtual void addIPBlock(string ip, int rate);
	virtual void addFlowBlock(string source, string destination, int protocol, int rate);

};

#endif /* RATELIMITER_H_ */


