/**
 * @file RateLimiterControlFlow.cc
 * @brief Used to control a Rate Limiter instance from Ponder2. Specifically, the limiting of individual flows.
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

#include "RateLimiterControlFlow.h"
#include "RateLimiter.h"
#include "MechanismExporter.h"

RateLimiterControlFlow::RateLimiterControlFlow()
{
	// signature and help strings are documentation -- the client
	// can query this information with a system.methodSignature and
	// system.methodHelp RPC.
	this->_signature = "S:ii";
	// method's result and two arguments are integers
	this->_help = "This method prints a message";

}

RateLimiterControlFlow::~RateLimiterControlFlow()
{
	// TODO Auto-generated destructor stub
}

void RateLimiterControlFlow::execute(xmlrpc_c::paramList const& paramList,
		xmlrpc_c::value * const retvalP) {

	string const name(paramList.getString(0));
	paramList.verifyEnd(5);
	RatePointerTable::iterator iter;


	iter = rate_limiter_pointer_table.find(name);
	if (iter != rate_limiter_pointer_table.end()) {
		int protocol = atoi(paramList.getString(3).c_str());
			iter->second->addFlowBlock(paramList.getString(1),paramList.getString(2),protocol,paramList.getInt(4));
			//cerr << "Flow Block: " << paramList.getString(1) << " " << paramList.getString(2) << " " << protocol << " " << paramList.getInt(4) << endl;
	}

   *retvalP = xmlrpc_c::value_int(0);
}
