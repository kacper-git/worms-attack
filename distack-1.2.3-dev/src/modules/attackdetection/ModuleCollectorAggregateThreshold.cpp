#include "ModuleCollectorAggregateThreshold.h"

MODULE_INTERFACE(ModuleCollectorAggregateThreshold);

const string ModuleCollectorAggregateThreshold::PARAM_HistoryLength = "HistoryLength";

ModuleCollectorAggregateThreshold::ModuleCollectorAggregateThreshold ()
{
}

ModuleCollectorAggregateThreshold::~ModuleCollectorAggregateThreshold ()
{
}

bool ModuleCollectorAggregateThreshold::configure (ModuleConfiguration& configList)
{
	bool good = true;
	good &= configList.has (PARAM_HistoryLength);

	if (good) {
		m_param_HistoryLength = configList.getLong (PARAM_HistoryLength);
	}

	return good;
}

void ModuleCollectorAggregateThreshold::registerMessages ()
{
	MessagingNode::subscribeMessage (Message::MESSAGE_TYPE_AGGREGATE_WATCH_VALUES);
	MessagingNode::subscribeMessage (Message::MESSAGE_TYPE_AGGREGATE_INTERVAL_VALUES);
}

void ModuleCollectorAggregateThreshold::receiveMessage (Message* msg)
{
	if (msg->getType() == Message::MESSAGE_TYPE_AGGREGATE_WATCH_VALUES) {
		handleInputValuesMsg (msg);
	}
	
	if (msg->getType() == Message::MESSAGE_TYPE_AGGREGATE_INTERVAL_VALUES) {
		handleRequestValuesMsg (msg);
	}
}

void ModuleCollectorAggregateThreshold::handleInputValuesMsg (Message* msg)
{
	MessageAggregateWatchValues* msgValues = (MessageAggregateWatchValues*)msg;

	{
	        boost::mutex::scoped_lock scopedLock (m_intervalsMutex);

		if (m_intervals.size() >= m_param_HistoryLength) m_intervals.pop();
		INTERVAL_COUNT_ITEMS intervalItems;

		MessageAggregateWatchValues::AGGREGATE_INFOS aggregateInfo = msgValues->getAggregateInfo ();

		MessageAggregateWatchValues::AGGREGATE_INFOS_ITERATOR i	= aggregateInfo.begin ();
		MessageAggregateWatchValues::AGGREGATE_INFOS_ITERATOR iend = aggregateInfo.end ();

		for ( ; i != iend; i++) {
		        COUNT_THRESHOLD_ITEM item;
	    
			item.count		 = i->count;
			item.threshold	 = i->threshold;
			item.protocol	 = i->protocol;
			item.description = i->description;
	    
			intervalItems.push_back (item);
		}

		m_intervals.push (intervalItems);
	}

	//
	// SA-Eitzen-Armin: Temporaere Aenderung, die dafuer sorgt, dass die Intervall-Werte eines bestimmten Aggregates an eine VNA-Instanz uebermittelt werden
	//
	// createValuesMsgRemote(Packet::PROTO_TCP);
	// //	createValuesMsgRemote(Packet::PROTO_UDP);
	//
}

void ModuleCollectorAggregateThreshold::handleRequestValuesMsg (Message* msg)
{
	if (! msg->isRequest()) return;

	MessageAggregateIntervalValues* inMsg  = (MessageAggregateIntervalValues*)msg;
	MessageAggregateIntervalValues* outMsg = new MessageAggregateIntervalValues ();
	
	//
	// find the aggregate interval values that the request contains
	// and create a new message with the count/threshold values for the aggregate
	//

	{
		boost::mutex::scoped_lock scopedLock (m_intervalsMutex);

		INTERVAL_QUEUE::size_type intervals = m_intervals.size ();

		for (INTERVAL_QUEUE::size_type i=0; i<intervals; i++) {
			INTERVAL_COUNT_ITEMS items = m_intervals.front ();
		
			INTERVAL_COUNT_ITEMS_ITERATOR itemsBegin = items.begin ();
			INTERVAL_COUNT_ITEMS_ITERATOR itemsEnd   = items.end   ();
			
			for ( ; itemsBegin != itemsEnd; itemsBegin++) {
	
				if (itemsBegin->protocol == inMsg->getProtocol () && itemsBegin->description == inMsg->getDescription ()) {
					MessageAggregateIntervalValues::COUNT_THRESHOLD_PAIR values (itemsBegin->count, itemsBegin->threshold);
					outMsg->addInterval (values);
				}

			} // for ( ; itemsBegin != itemsEnd; itemsBegin++)

			m_intervals.pop  ();
			m_intervals.push (items);

		} // for (INTERVAL_QUEUE::size_type i=0; i<intervals; i++)
	}

	MessagingNode::sendMessage (outMsg);
}

//
// SA-Eitzen-Armin: Temporaere Aenderung, die dafuer sorgt, dass die Intervall-Werte eines bestimmten Aggregates an eine VNA-Instanz uebermittelt werden
// TODO: Die Anbindung von VNA sollte in ein eigenes Modul ausgelagert werden, welches sich fuer die interessanten Nachrichten registriert und diese
//       an die VNA-Instanz uebermittelt.
//

void ModuleCollectorAggregateThreshold::createValuesMsgRemote (Packet::PROTOCOL proto)
{
	MessageAggregateIntervalValues* outMsg = new MessageAggregateIntervalValues ();

	bool valuesExist = false;
	
	//
	// find the aggregate interval values that the request contains
	// and create a new message with the count/threshold values for the aggregate
	//

	{
		boost::mutex::scoped_lock scopedLock (m_intervalsMutex);

		INTERVAL_QUEUE::size_type intervals = m_intervals.size ();

		for (INTERVAL_QUEUE::size_type i=0; i<intervals; i++) {
			INTERVAL_COUNT_ITEMS items = m_intervals.front ();
		
			INTERVAL_COUNT_ITEMS_ITERATOR itemsBegin = items.begin ();
			INTERVAL_COUNT_ITEMS_ITERATOR itemsEnd   = items.end   ();
			
			for ( ; itemsBegin != itemsEnd; itemsBegin++) {
	
				if (itemsBegin->protocol == proto) {
					MessageAggregateIntervalValues::COUNT_THRESHOLD_PAIR values (itemsBegin->count, itemsBegin->threshold);
					outMsg->addInterval (values);
					if(valuesExist == false) {
						valuesExist = true;
						outMsg->setProtocol (itemsBegin->protocol);
						outMsg->setDescription (itemsBegin->description);
					}
				}

			} // for ( ; itemsBegin != itemsEnd; itemsBegin++)

			m_intervals.pop  ();
			m_intervals.push (items);

		} // for (INTERVAL_QUEUE::size_type i=0; i<intervals; i++)
	}

	if(valuesExist)
	    MessagingNode::sendMessage (outMsg, MessagingNode::SEND_OPTIONS::createRemote (MessagingNode::REMOTE_DESTINATIONS_NEIGHBOURS));
}

