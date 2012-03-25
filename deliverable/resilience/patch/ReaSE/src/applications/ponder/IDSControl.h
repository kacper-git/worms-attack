/**
 * @file IDSControl.h
 * @brief Header file to support the control of a Flow Exporter instance from Ponder2.
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

#ifndef IDSCONTROL_H_
#define IDSCONTROL_H_

#include <stdio.h>
#include <iostream>
#include <xmlrpc-c/base.hpp>
#include <xmlrpc-c/registry.hpp>
#include <xmlrpc-c/server_abyss.hpp>

using namespace std;

class IDSControl: public xmlrpc_c::method {
public:
	IDSControl();
	virtual ~IDSControl();
	void execute(xmlrpc_c::paramList const& paramList,
			xmlrpc_c::value * const retvalP);
};

#endif /* IDSCONTROL_H_ */
