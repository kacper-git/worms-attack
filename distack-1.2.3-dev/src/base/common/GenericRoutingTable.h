#ifndef __GENERIC_ROUTING_TABLE_H
#define __GENERIC_ROUTING_TABLE_H

#include <vector>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>
#include "base/protocol/IpPacket.h"
#include "base/common/Helper.h"

#ifdef WIN32
	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>
	#include <Iphlpapi.h>
#endif // WIN32

using std::vector;
using std::ifstream;

#ifdef OMNET_SIMULATION
	#pragma warning (disable : 4244 4800 4267)
		#include <omnetpp.h>
		#include <RoutingTableAccess.h>
		#include <IRoutingTable.h>
	#pragma warning (default : 4244 4800 4267)

	class DistackOmnetModule; // forward decl
#endif // OMNET_SIMULATION

namespace GenericRoutingTable {

	typedef enum _ROUTING_SOURCE {
		ROUTING_SOURCE_SYSTEM,
		ROUTING_SOURCE_FILE,
	} ROUTING_SOURCE;

	typedef struct _ROUTING_ENTRY {
		IP_ADDR	addr;
		IP_ADDR mask;

		_ROUTING_ENTRY (IP_ADDR _addr, IP_ADDR _mask) {
			addr = _addr;	
			mask = _mask;
		}
	} ROUTING_ENTRY, *PROUTING_ENTRY;

	typedef vector<ROUTING_ENTRY>	ROUTING_TABLE;
	typedef ROUTING_TABLE::iterator ROUTING_TABLE_ITERATOR;

#ifdef OMNET_SIMULATION
	ROUTING_TABLE					getRoutingTable			(DistackOmnetModule* module, ROUTING_SOURCE source, string filename = "");
#else
	ROUTING_TABLE					getRoutingTable			(ROUTING_SOURCE source, string filename = "");
#endif // OMNET_SIMULATION

	namespace detail {

		typedef enum _ROUTING_TEXT_FORMAT {
			ROUTING_TEXT_FORMAT_SIMPLE,		// just ip and mask like 127.0.0.1/16
			ROUTING_TEXT_FORMAT_DETAILED,	// text format in /proc/net/route
		} ROUTING_TEXT_FORMAT;

		ROUTING_TABLE					getRoutingTableWin32	();
		ROUTING_TABLE					getRoutingTableLinux	();
		ROUTING_TABLE					getRoutingTableFile		(string filename, ROUTING_TEXT_FORMAT format);

#ifdef OMNET_SIMULATION
		ROUTING_TABLE					getRoutingTableOmnet	(DistackOmnetModule* module);
#endif // OMNET_SIMULATION
	
		bool							isValidDetailedAddress	(string addr);

	} // namespace detail

} // namespace RoutingTable

#endif // __ROUTING_TABLE_H
