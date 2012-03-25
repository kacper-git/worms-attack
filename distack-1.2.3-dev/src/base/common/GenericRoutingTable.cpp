#include "GenericRoutingTable.h"

#ifdef OMNET_SIMULATION
GenericRoutingTable::ROUTING_TABLE GenericRoutingTable::getRoutingTable (DistackOmnetModule* module, ROUTING_SOURCE source, string filename)
#else
GenericRoutingTable::ROUTING_TABLE GenericRoutingTable::getRoutingTable (ROUTING_SOURCE source, string filename)
#endif // OMNET_SIMULATION
{
	assert (! (source == ROUTING_SOURCE_FILE && filename.length() == 0));

	ROUTING_TABLE ret;

	if (source == ROUTING_SOURCE_FILE) {
		ret = getRoutingTableFile (filename, detail::ROUTING_TEXT_FORMAT_SIMPLE);
	}

	if (source == ROUTING_SOURCE_SYSTEM) {

		#ifdef OMNET_SIMULATION
			ret = detail::getRoutingTableOmnet (module);
		#else
			#ifdef WIN32
				ret = detail::getRoutingTableWin32 ();
			#else
				ret = detail::getRoutingTableLinux ();
			#endif
		#endif

	} // if (source == ROUTING_SOURCE_SYSTEM)

	return ret;
}

GenericRoutingTable::ROUTING_TABLE GenericRoutingTable::detail::getRoutingTableWin32 ()
{
	ROUTING_TABLE retTable;

#ifdef WIN32

	PMIB_IPFORWARDTABLE table	= NULL;
	ULONG				size	= 0;
	DWORD				ret		= 0;
	BOOL				order	= TRUE;

	do {
		if (size > 0) {
			if (table != NULL) free (table);
			table = (PMIB_IPFORWARDTABLE) malloc (size);
		}

		ret = GetIpForwardTable (table, &size, order);
	
	} while (ret == ERROR_INSUFFICIENT_BUFFER);

	if (ret != NO_ERROR) return retTable;
	if (table == NULL)	 return retTable;
	
	for (DWORD i = 0; i<table->dwNumEntries; i++) {

		MIB_IPFORWARDROW item = table->table[i];
		IP_ADDR			 addr (item.dwForwardDest);
		IP_ADDR			 mask (item.dwForwardMask); 

		retTable.push_back (ROUTING_ENTRY (addr, mask));
	}

	free (table);

#endif // WIN32

	return retTable;
}

GenericRoutingTable::ROUTING_TABLE GenericRoutingTable::detail::getRoutingTableLinux ()
{	
	ROUTING_TABLE retTable;

#ifdef LINUX
	retTable = getRoutingTableFile ("/proc/net/route", ROUTING_TEXT_FORMAT_DETAILED);
#endif

	return retTable;
}

#ifdef OMNET_SIMULATION

GenericRoutingTable::ROUTING_TABLE GenericRoutingTable::detail::getRoutingTableOmnet (DistackOmnetModule* module)
{
	ROUTING_TABLE ret;	

	//
	// find the routing omnet module
	// this is similar to RoutingTableAccess, but there 
	// the simulation context would be wrong
	//
		
	cModule* m = findModuleSomewhereUp ("routingTable", (cModule*)module);
	IRoutingTable* omnetTable = check_and_cast<IRoutingTable*> (m);
	if (omnetTable == NULL) return ret;

	for (int i=0; i<omnetTable->getNumRoutes(); i++) {
		const IPRoute* omnetEntry = omnetTable->getRoute (i);
		if (omnetEntry == NULL) continue;

		IP_ADDR addr = IP_ADDR (omnetEntry->getHost());
		IP_ADDR mask = IP_ADDR (omnetEntry->getNetmask());

		ret.push_back (ROUTING_ENTRY (addr, mask));
	}

	return ret;
}
#endif // OMNET_SIMULATION

GenericRoutingTable::ROUTING_TABLE	GenericRoutingTable::detail::getRoutingTableFile (string filename, ROUTING_TEXT_FORMAT format)
{
	ROUTING_TABLE ret;

	//
	// read the contents of the file
	//

	ifstream file (filename.c_str());
	assert (file.is_open());

	string content = "";

	while (! file.eof ()) {	
		char item;
		file.read (&item, 1);
		if (! file.eof())
			content += item;
	}

	//
	// get the individual lines of the routing table
	//

	typedef vector<string>			STRING_VECTOR;
	typedef STRING_VECTOR::iterator STRING_VECTOR_ITERATOR;
	STRING_VECTOR lines;

	boost::split (lines, content, boost::is_any_of ("\n"));

	STRING_VECTOR_ITERATOR i	= lines.begin ();
	STRING_VECTOR_ITERATOR iend = lines.end	  ();

	for ( ; i != iend; i++) {
	
		string line = *i;
		boost::trim (line);

		IP_ADDR addr, mask;

		//
		// parse the content of each line
		//

		if (format == ROUTING_TEXT_FORMAT_SIMPLE) {

			STRING_VECTOR items;
			boost::split (items, line, boost::is_any_of ("/"));
			if (items.size() != 2) continue;

			addr.fromString (items[0]);
			
			int bits = Helper::stoi (items[1]);
			if (! (bits >= 0 && bits <= 32)) continue;

			IP_ADDR tempMask;
			for (int i=0; i<bits; i++) {					
				unsigned char byte = i / 8;
				tempMask.x[byte] |= (0x1 << (8 - 1 - (i % 8))); 
			}

			mask = tempMask;

		} else if (format == ROUTING_TEXT_FORMAT_DETAILED) {

			typedef enum _PROC_NET_ROUTE_FIELDS {
				PROC_NET_ROUTE_FIELDS_ADDR = 1,
				PROC_NET_ROUTE_FIELDS_MASK = 7,
			} PROC_NET_ROUTE_FIELDS;

			STRING_VECTOR items;
			boost::split (items, line, boost::is_any_of ("\t"));
			if (items.size() < (PROC_NET_ROUTE_FIELDS_MASK+1)) continue;

			boost::trim (items[PROC_NET_ROUTE_FIELDS_ADDR]);
			boost::trim (items[PROC_NET_ROUTE_FIELDS_MASK]);

			if (! isValidDetailedAddress (items[PROC_NET_ROUTE_FIELDS_ADDR])) continue;
			if (! isValidDetailedAddress (items[PROC_NET_ROUTE_FIELDS_MASK])) continue;

			addr = IP_ADDR (Helper::hstoui(items[PROC_NET_ROUTE_FIELDS_ADDR]));
			mask = IP_ADDR (Helper::hstoui(items[PROC_NET_ROUTE_FIELDS_MASK]));

			// If default route 0.0.0.0/0 shouldn't be regarded uncomment the following 2 lines
			//if (addr == IP_ADDR (0)) 
			//	continue;

		} else
			assert (false);

		ret.push_back (ROUTING_ENTRY (addr, mask));

	} // for ( ; i != iend; i++)

	return ret;
}

bool GenericRoutingTable::detail::isValidDetailedAddress (string addr)
{
	string::size_type len = addr.length ();
	if (len != 2*4) return false;

	for (string::size_type i=0; i<len; i++) {

		char character = addr[i];
		bool valid = ((character >= 0x30) && (character <= 0x39)) ||
					 ((character >= 0x41) && (character <= 0x46)) ||
					 ((character >= 0x61) && (character <= 0x66)) ;
					 
		if (! valid) return false;
	}

	return true;
}
