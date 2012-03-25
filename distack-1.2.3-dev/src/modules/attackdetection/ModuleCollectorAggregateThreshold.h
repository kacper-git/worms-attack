#ifndef __MODULE_COLLECTOR_AGGREGATE_THRESHOLD_H
#define __MODULE_COLLECTOR_AGGREGATE_THRESHOLD_H

#include "base/protocol/Packet.h"
#include "base/module/DistackModuleInterface.h"
#include "messages/attackdetection/MessageAggregateWatchValues.h"
#include "messages/attackdetection/MessageAggregateIntervalValues.h"
#include <map>
#include <string>

using std::string;
using std::map;
using std::pair;

class ModuleCollectorAggregateThreshold : public DistackModuleInterface {
public:
							ModuleCollectorAggregateThreshold	();
							~ModuleCollectorAggregateThreshold	();

	bool					configure							(ModuleConfiguration& configList);
	void					registerMessages					();
	void					receiveMessage						(Message* msg);

private:

	void					handleInputValuesMsg				(Message* msg);
	void					handleRequestValuesMsg				(Message* msg);

	//
	// SA-Eitzen-Armin: Temporaere Aenderung, die dafuer sorgt, dass die Intervall-Werte eines bestimmten Aggregates an eine VNA-Instanz uebermittelt werden
	//
	void					createValuesMsgRemote				(Packet::PROTOCOL proto);

	static const string		PARAM_HistoryLength;
	unsigned int			m_param_HistoryLength;

	typedef struct _COUNT_THRESHOLD_ITEM {
		unsigned int		count;
		double				threshold;
		Packet::PROTOCOL	protocol;
		string				description;
	} COUNT_THRESHOLD_ITEM; 

	typedef vector<COUNT_THRESHOLD_ITEM>						INTERVAL_COUNT_ITEMS;
	typedef INTERVAL_COUNT_ITEMS::iterator						INTERVAL_COUNT_ITEMS_ITERATOR;
	typedef	queue<INTERVAL_COUNT_ITEMS>							INTERVAL_QUEUE;

	boost::mutex												m_intervalsMutex;
	INTERVAL_QUEUE												m_intervals;
};

#endif // __MODULE_COLLECTOR_AGGREGATE_THRESHOLD_H
