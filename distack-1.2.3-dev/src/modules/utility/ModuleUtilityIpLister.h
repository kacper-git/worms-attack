#ifndef __MODULE_UTILITY_IP_LISTER_H
#define __MODULE_UTILITY_IP_LISTER_H

#include "base/protocol/IpPacket.h"
#include "base/protocol/Packet.h"
#include "base/module/DistackModuleInterface.h"
#include <fstream>
#include <map>

using std::map;
using std::pair;
using std::ofstream;

class ModuleUtilityIpLister : public DistackModuleInterface {
public:
						ModuleUtilityIpLister		();
						~ModuleUtilityIpLister		();

	bool					configure			(ModuleConfiguration& configList);
	bool					frameCall			(Frame& frame);

private:

	typedef pair<IP_ADDR, unsigned int>	IP_COUNTER_PAIR;
	typedef map<IP_ADDR, unsigned int>	IP_COUNTER_MAP;
	typedef IP_COUNTER_MAP::iterator	IP_COUNTER_MAP_ITERATOR;

	IP_COUNTER_MAP				m_counterMap;	

	static const string			PARAM_OutFilename;
	static const string			PARAM_SubnetMasking;

	unsigned int				m_param_OutFilename;
	IP_ADDR					m_param_SubnetMasking;

	ofstream				m_outFile;

};

#endif // __MODULE_UTILITY_IP_LISTER_H
