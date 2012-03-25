#ifndef __MODULE_FILTER_PROTOCOL_H
#define __MODULE_FILTER_PROTOCOL_H

#include "base/module/DistackModuleInterface.h"
#include "base/protocol/IpPacket.h"

class ModuleFilterSubnet : public DistackModuleInterface {
public:
					ModuleFilterSubnet	();
					~ModuleFilterSubnet	();

	bool				configure		(ModuleConfiguration& configList);
	bool				frameCall		(Frame& frame);

private:

	bool				matches			(IP_ADDR addr);

	static const string		PARAM_Address;
	static const string		PARAM_SubnetMask;
	static const string		PARAM_Inverse;

	IP_ADDR				m_param_Address;
	IP_ADDR				m_param_SubnetMask;
	bool				m_param_Inverse;

};

#endif // __MODULE_FILTER_PROTOCOL_H
