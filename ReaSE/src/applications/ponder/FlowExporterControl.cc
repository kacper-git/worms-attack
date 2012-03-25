/**
 * @file FlowExporterControl.cc
 * @brief Used to control a Flow Exporter instance from Ponder2.
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

#include "FlowExporterControl.h"
#include "FlowExporter.h"
#include "MechanismExporter.h"

FlowExporterControl::FlowExporterControl()
{
	// signature and help strings are documentation -- the client
	// can query this information with a system.methodSignature and
	// system.methodHelp RPC.
	this->_signature = "S:ii";
	// method's result and two arguments are integers
	this->_help = "This method prints a message";

}

FlowExporterControl::~FlowExporterControl()
{
	// TODO Auto-generated destructor stub
}

void FlowExporterControl::execute(xmlrpc_c::paramList const& paramList,
		xmlrpc_c::value * const retvalP) {

	string const name(paramList.getString(0));
	paramList.verifyEnd(3);
	FlowPointerTable::iterator iter;

	iter = flow_exporter_pointer_table.find(name);
	if (iter != flow_exporter_pointer_table.end()) {
		iter->second->setTimeouts(paramList.getInt(1), paramList.getInt(2));
	}

	*retvalP = xmlrpc_c::value_int(0);
}
