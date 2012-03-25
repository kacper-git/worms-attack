#ifndef __MODULE_FILTER_PROTOCOL_H
#define __MODULE_FILTER_PROTOCOL_H

#include "base/module/DistackModuleInterface.h"
#include "base/protocol/Packet.h"
#include "base/protocol/ProtocolNameResolver.h"

class ModuleFilterProtocol : public DistackModuleInterface {
public:
					ModuleFilterProtocol		();
					 ~ModuleFilterProtocol		();

	bool				configure			(ModuleConfiguration& configList);
	bool				frameCall			(Frame& frame);

private:

	static const string		PARAM_Protocol;
	static const string		PARAM_Inverse;

	Packet::PROTOCOL		m_param_Protocol;
	bool				m_param_Inverse;

};

#endif // __MODULE_FILTER_PROTOCOL_H
