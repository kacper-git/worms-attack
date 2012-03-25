/**
 * @file IDSControl.cc
 * @brief Used to control an IDS instance from Ponder2.
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

#include "IDSControl.h"
#include "MechanismExporter.h"

IDSControl::IDSControl()
{
	// signature and help strings are documentation -- the client
	// can query this information with a system.methodSignature and
	// system.methodHelp RPC.
	this->_signature = "S:ii";
	// method's result and two arguments are integers
	this->_help = "This method prints a message";

}

IDSControl::~IDSControl()
{
	// TODO Auto-generated destructor stub
}

void IDSControl::execute(xmlrpc_c::paramList const& paramList,
		xmlrpc_c::value * const retvalP) {
	paramList.verifyEnd(2);
	IDSPointerTable::iterator iter;


	iter = ids_pointer_table.find(paramList.getString(0));
	if (iter != ids_pointer_table.end()) {

		iter->second->setReport(paramList.getString(1));
	}
	*retvalP = xmlrpc_c::value_int(0);
}
