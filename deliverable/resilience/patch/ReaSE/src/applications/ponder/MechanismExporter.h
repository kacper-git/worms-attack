/**
 * @file MechanismExporter.h
 * @brief Header file to support the registration of various instances of managed objects and to export their control mechanisms to Ponder2.
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

#ifndef MECHANISMEXPORTER_H_
#define MECHANISMEXPORTER_H_

#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <boost/thread.hpp>
#include <xmlrpc-c/base.hpp>
#include <xmlrpc-c/registry.hpp>
#include <xmlrpc-c/server_abyss.hpp>
#include "FlowExporter.h"
#include "Classifier.h"
#include "RateLimiter.h"
#include "IDSModule.h"
#include <string>
#include <tr1/unordered_map>

typedef std::tr1::unordered_map<std::string, FlowExporter*> FlowPointerTable;
typedef std::tr1::unordered_map<std::string, Classifier*> ClassifierPointerTable;
typedef std::tr1::unordered_map<std::string, RateLimiter*> RatePointerTable;
typedef std::tr1::unordered_map<std::string, IDSModule*> IDSPointerTable;

class MechanismExporter {
public:
	MechanismExporter();
	virtual ~MechanismExporter();
	virtual void registerFlowExporter(FlowExporter* flow_exporter_pointer, std::string name);
	virtual void registerClassifier(Classifier* classifier_pointer, std::string name);
	virtual void registerRateLimiter(RateLimiter* rate_limiter_pointer, std::string name);
	virtual void registerIDS(IDSModule* ids_pointer, std::string name);
};

extern MechanismExporter mechanism_exporter;

extern FlowPointerTable flow_exporter_pointer_table;
extern ClassifierPointerTable classifier_pointer_table;
extern RatePointerTable rate_limiter_pointer_table;
extern IDSPointerTable ids_pointer_table;

#endif /* MECHANISMEXPORTER_H_ */
