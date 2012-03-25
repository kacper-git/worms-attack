#ifndef __MODULE_ANALYZER_ADDRESS_SPACE_H
#define __MODULE_ANALYZER_ADDRESS_SPACE_H

#include "base/protocol/Packet.h"
#include "base/module/DistackModuleInterface.h"
#include "messages/utility/MessageAlert.h"
#include "messages/attackdetection/MessageAddressDistribution.h"
#include "messages/attackdetection/MessageAggregateIntervalValues.h"
#include "messages/attackdetection/MessageLastSuspiciousAggregate.h"
#include "messages/attackdetection/MessageLastAnomalyType.h"
#include <vector>
#include <boost/thread/mutex.hpp>

using std::vector;

class ModuleAnalyzerAddressSpace : public DistackModuleInterface {
public: 
							ModuleAnalyzerAddressSpace		();
							~ModuleAnalyzerAddressSpace		();

	bool					configure						(ModuleConfiguration& configList);
	void					receiveMessage					(Message* msg);
	void					registerMessages				();

private:

	void					handleSubnetDistributionMsg		(Message* msg);
	void					handleLastSuspiciousAggrMsg		(Message* msg);
	void					handleAggregateIntervalValues	(Message* msg);
	void					handleLastAnomalyMsg			(Message* msg);

	typedef					vector<IP_ADDR>					IP_ADDR_VECTOR;

	void					analyze							();
	IP_ADDR_VECTOR			analyzeFindAttackedSubnets		(unsigned int intervalLastNormal, unsigned int intervalFirstAbnormal);
	bool					analyzeIsDistributedAttack		(unsigned int intervalLastNormal, unsigned int intervalFirstAbnormal);


	static const string		PARAM_SubnetChangePercent;
	static const string		PARAM_ActiveSubnetPackets;
	static const string		PARAM_ActiveSubnetRelation;
	unsigned short			m_param_SubnetChangePercent;
	unsigned int			m_param_ActiveSubnetPackets;
	double					m_param_ActiveSubnetRelation;

	unsigned short			m_stage;
	
	bool					m_haveAggregate;
	bool					m_haveIntervalValues;
	bool					m_haveSubnetTree;

	Packet::PROTOCOL		m_suspiciousAggregateProtocol;
	string					m_suspiciousAggregateDescription;
	MessageLastAnomalyType::ANOMALY_TYPE			m_lastAnomalyType;

	MessageAggregateIntervalValues::INTERVAL_ITEMS	m_intervalValues;
	typedef vector<SubnetCounterTree*>				TREE_VECTOR;
	typedef TREE_VECTOR::iterator					TREE_VECTOR_ITERATOR;
	TREE_VECTOR										m_intervalSubnets;

	boost::mutex			m_analyzerMutex;
};

#endif // __MODULE_ANALYZER_ADDRESS_SPACE_H
