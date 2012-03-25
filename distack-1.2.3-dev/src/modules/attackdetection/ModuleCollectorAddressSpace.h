#ifndef __MODULE_COLLECTOR_ADDRESS_SPACE_H
#define __MODULE_COLLECTOR_ADDRESS_SPACE_H

#include "base/module/DistackModuleInterface.h"
#include "base/common/GenericRoutingTable.h"
#include "messages/attackdetection/MessageAddressDistribution.h"
#include "messages/utility/MessageTimer.h"
#include "base/common/SubnetCounterTree.h"
#include <boost/thread/mutex.hpp>
#include <queue>

using std::queue;

class ModuleCollectorAddressSpace : public DistackModuleInterface {
public: 
								ModuleCollectorAddressSpace		();
								~ModuleCollectorAddressSpace	();

	bool						configure						(ModuleConfiguration& configList);
	bool						frameCall						(Frame& frame);
	void						receiveMessage					(Message* msg);
	void						registerMessages				();

private:

	void						handleTimerMsg					();
	void						handleCollectionRequestMsg		();

	static const string			PARAM_RoutingTableFilename;
	static const string			PARAM_TimerModule;
	static const string			PARAM_HistoryLength;

	string						m_param_RoutingTableFilename;
	string						m_param_TimerModule;
	unsigned int				m_param_HistoryLength;

	unsigned short				m_stage;
	
	SubnetCounterTree						m_subnetTemplate;
	SubnetCounterTree*						m_currentCounterTree;
	typedef queue<SubnetCounterTree*>		SUBNET_COUNTER_QUEUE;
	SUBNET_COUNTER_QUEUE					m_addressDistributions;
	boost::mutex							m_addressDistributionsMutex;

};

#endif // __MODULE_COLLECTOR_ADDRESS_SPACE_H
