#include "ModuleAnalyzerAggregateWatch.h"

MODULE_INTERFACE( ModuleAnalyzerAggregateWatch )

const string ModuleAnalyzerAggregateWatch::PARAM_TimerModule = "TimerModule";
const string ModuleAnalyzerAggregateWatch::PARAM_FrameSizeBorders = "FrameSizeBorders";
const string ModuleAnalyzerAggregateWatch::PARAM_AlphaAvg = "AlphaAvg";
const string ModuleAnalyzerAggregateWatch::PARAM_AlphaDev = "AlphaDev";
const string ModuleAnalyzerAggregateWatch::PARAM_Beta = "Beta";
const string ModuleAnalyzerAggregateWatch::PARAM_AlphaRed = "AlphaRed";
const string ModuleAnalyzerAggregateWatch::PARAM_AlphaLearn = "AlphaLearn";
const string ModuleAnalyzerAggregateWatch::PARAM_ExceedThreshold = "ExceedThreshold";
const string ModuleAnalyzerAggregateWatch::PARAM_LearningIntervals = "LearningIntervals";

ModuleAnalyzerAggregateWatch::ModuleAnalyzerAggregateWatch ()
: m_lastSuspicious (NULL)
{
}

ModuleAnalyzerAggregateWatch::~ModuleAnalyzerAggregateWatch ()
{
}

bool ModuleAnalyzerAggregateWatch::configure (ModuleConfiguration& configList)
{
	boost::mutex::scoped_lock scopedLock (m_counterMutex);

	bool good = true;

	m_stage = configList.stage;

	good &= configList.has (PARAM_AlphaAvg			);
	good &= configList.has (PARAM_AlphaDev			);
	good &= configList.has (PARAM_AlphaLearn		);
	good &= configList.has (PARAM_AlphaRed			);
	good &= configList.has (PARAM_Beta				);
	good &= configList.has (PARAM_ExceedThreshold	);
	good &= configList.has (PARAM_FrameSizeBorders	);
	good &= configList.has (PARAM_TimerModule		);
	good &= configList.has (PARAM_LearningIntervals	);

	if (good) {

		//
		// get the frame size aggregate borders and 
		// create the counters for the intervals
		//

		string sizeborders = configList.get (PARAM_FrameSizeBorders);
		
		typedef vector<string>			STRING_VECTOR;
		typedef STRING_VECTOR::iterator STRING_VECTOR_ITERATOR;
		
		STRING_VECTOR borders;
		boost::split (borders, sizeborders, boost::is_any_of (","));

		//
		// get the alpha, beta, ... values
		//
		params = AGGREGATE_WATCH_PARAMS(
			configList.getDouble (PARAM_AlphaAvg),
			configList.getDouble (PARAM_AlphaDev),
			configList.getDouble (PARAM_AlphaRed),
			configList.getDouble (PARAM_AlphaLearn),
			configList.getDouble (PARAM_Beta),
			configList.getLong (PARAM_ExceedThreshold),
			configList.getLong (PARAM_LearningIntervals) );

		//
		// we need to have more than two items (lower and upper bound)
		//
		
		if (borders.size() >= 2) {

			STRING_VECTOR_ITERATOR i = borders.begin ();
			STRING_VECTOR_ITERATOR iend = borders.end	();

			unsigned int lowerBound = 0;
			unsigned int upperBound = 0;

			lowerBound = Helper::stol (*i++);

			for ( ; i != iend; i++) {
				string item = *i;
				boost::trim (item);
				upperBound = Helper::stol (item);

				if (lowerBound > upperBound) 
					return false;

				AGGREGATE_WATCH_ITEM::AGGREGATE_TYPE type = AGGREGATE_WATCH_ITEM::AGGREGATE_TYPE_SIZE;
				string descr = "size aggregate for " + 
						Helper::ultos(lowerBound) +	 
						" - " + 
						Helper::ultos(upperBound)	;

				m_sizeCountMap.insert (SIZE_COUNT_PAIR (SIZE_RANGE (lowerBound, upperBound), 
														AGGREGATE_WATCH_ITEM (type, descr, params)));
				lowerBound = upperBound + 1;
			}

		} // if (borders.size() >= 2) 
		
		//
		// start the timer for the inspection of the aggregates
		//

		m_param_TimerModule = configList.get (PARAM_TimerModule);

	}

	return good;
}

bool ModuleAnalyzerAggregateWatch::frameCall(Frame& frame)
{
	boost::mutex::scoped_lock scopedLock (m_counterMutex);

	//
	// we need to get a hand on the complete protocols, so we parse all the payload
	//

	frame.parsePackets ();
	if (frame.payloadpacket == NULL) return true;

	//
	// update all the protocol counters
	//

	for (Packet* packet = frame.payloadpacket; packet != NULL; packet = packet->getNextPacket()) {

		Packet::PROTOCOL			protocol = packet->getProtocol ();
		if (protocol <= Packet::PROTO_NONE || protocol >= Packet::PROTO_MAXIMUM) continue;

		PROTOCOL_COUNT_MAP_ITERATOR item	 = m_protocolCountMap.find (protocol);
		unsigned long				count	 = 0;
		
		//
		// create new PROTOCOL_COUNT_MAP if no map exists for current protocol
		//

		if (item == m_protocolCountMap.end ()) {

			AGGREGATE_WATCH_ITEM::AGGREGATE_TYPE	type  = AGGREGATE_WATCH_ITEM::AGGREGATE_TYPE_PROTOCOL;
			string									descr = "aggregate for protocol " + Packet::getProtocolNameFromId (protocol);
			pair<PROTOCOL_COUNT_MAP_ITERATOR, bool> insertItem;

			insertItem = m_protocolCountMap.insert (PROTOCOL_COUNT_PAIR (protocol, AGGREGATE_WATCH_ITEM (type, descr, params)));
			assert (insertItem.second == true);

			insertItem.first->second.counter++;
			insertItem.first->second.protocol = protocol;

		} else
			item->second.counter++;
			
	} // for (Packet* packet = frame.payloadpacket; packet != NULL; packet = packet->getNextPacket())

	//
	// update size statistics
	// walk the map and find the size range where to update the counter
	//

	SIZE_COUNT_MAP_ITERATOR i	 = m_sizeCountMap.begin ();
	SIZE_COUNT_MAP_ITERATOR iend = m_sizeCountMap.end	();
	unsigned int			size = frame.payloadpacket->getSize ();

	for ( ; i != iend; i++) {
		SIZE_RANGE range = i->first;
		
		if (size >= range.first && size <= range.second)
			i->second.counter++;
	}

	//
	// analyzer modules _never_ drop any packets from further channel-processing!
	//

	return true;
}

void ModuleAnalyzerAggregateWatch::handleTimerMsg ()
{
	boost::mutex::scoped_lock scopedLock (m_counterMutex);

	{
		//
		// send out the current statistical values for all aggregates
		//
		
		MessageAggregateWatchValues* msg = new MessageAggregateWatchValues ();
	
		{
			//
			// add all protocol aggregates
			//

			PROTOCOL_COUNT_MAP_ITERATOR i = m_protocolCountMap.begin();
			PROTOCOL_COUNT_MAP_ITERATOR iend = m_protocolCountMap.end();

			for ( ; i != iend; i++) {
				MessageAggregateWatchValues::AGGREGATE_INFO info;
				
				info.description = i->second.description;
				info.protocol = i->second.protocol;
				info.count = i->second.counter;
				info.average = i->second.average;
				info.deviation = i->second.deviation;
				info.threshold = i->second.threshold;

				msg->add (info);
			}
		}
		
		{
			//
			// add the size aggregates
			//
			
			SIZE_COUNT_MAP_ITERATOR i	 = m_sizeCountMap.begin ();
			SIZE_COUNT_MAP_ITERATOR iend = m_sizeCountMap.end	();

			for ( ; i != iend; i++) {
				MessageAggregateWatchValues::AGGREGATE_INFO info;
				
				info.description	= i->second.description;
				info.protocol		= i->second.protocol;
				info.count			= i->second.counter;
				info.average		= i->second.average;
				info.deviation		= i->second.deviation;
				info.threshold		= i->second.threshold;

				msg->add (info);
			}
		}

		MessagingNode::sendMessage (msg);
	}

	//
	// check all counter against their current average
	// clear all counters and update averages
	//
	
	AGGREGATE_WATCH_ITEM::AGGREGATE_RESULT	exceeded	 = AGGREGATE_WATCH_ITEM::AGGREGATE_RESULT_NOTHING;
	string									alertMessage = "";
	
	{
		PROTOCOL_COUNT_MAP_ITERATOR i	 = m_protocolCountMap.begin ();
		PROTOCOL_COUNT_MAP_ITERATOR iend = m_protocolCountMap.end	();

		for ( ; i != iend; i++) {

			AGGREGATE_WATCH_ITEM::AGGREGATE_RESULT result = i->second.exceeded ();		
			exceeded = AGGREGATE_WATCH_ITEM::AGGREGATE_RESULT (exceeded | result);

			if (result == AGGREGATE_WATCH_ITEM::AGGREGATE_RESULT_RAISEALERT) {
				alertMessage += " | counter exceeded: protocol "				+ 
								Packet::getProtocolNameFromId (i->first) + " | ";
				m_lastSuspicious = &(i->second);
			} else if (result == AGGREGATE_WATCH_ITEM::AGGREGATE_RESULT_LOWERALERT) {
				alertMessage += " | counter undercut: protocol "				+ 
								Packet::getProtocolNameFromId (i->first) + " | ";
			}

		} // for ( ; i != iend; i++) 
	}

	{
		SIZE_COUNT_MAP_ITERATOR i	 = m_sizeCountMap.begin ();
		SIZE_COUNT_MAP_ITERATOR iend = m_sizeCountMap.end	();

		for ( ; i != iend; i++) {

			AGGREGATE_WATCH_ITEM::AGGREGATE_RESULT result = i->second.exceeded ();		
			exceeded = AGGREGATE_WATCH_ITEM::AGGREGATE_RESULT (exceeded | result);

			if (result == AGGREGATE_WATCH_ITEM::AGGREGATE_RESULT_RAISEALERT) {
				alertMessage += "counter exceeded: size " + 
								Helper::ultos(i->first.first)	+ "-"	+
								Helper::ultos(i->first.second)	+ " | "	;
				m_lastSuspicious = &(i->second);
			} else if (result == AGGREGATE_WATCH_ITEM::AGGREGATE_RESULT_LOWERALERT) {
				alertMessage += "counter undercut: size " + 
								Helper::ultos(i->first.first)	+ "-"	+
								Helper::ultos(i->first.second)	+ " | "	;
			}

		} // for ( ; i != iend; i++) 
	}

	//
	// if _any_ of the counters exceeded, send out an alert message
	// so the module manager can raise detection granularity and load additional stages
	//

	if ((exceeded & AGGREGATE_WATCH_ITEM::AGGREGATE_RESULT_RAISEALERT) == AGGREGATE_WATCH_ITEM::AGGREGATE_RESULT_RAISEALERT) {
		MessageAlert* msg = new MessageAlert (MessageAlert::ALERT_TYPE_RAISE_LEVEL, m_stage, alertMessage);
		MessagingNode::sendMessage (msg);
		//
		// SA-Eitzen-Armin:
		// Messages muessen auch an VNA zur Visualisierung gesendet werden
		// TODO: LISTE mit der IP der VNA-Instanz uebergeben
		// MessagingNode::sendMessage (msg, MessagingNode::SEND_OPTIONS::createBothAsync (MessagingNode::REMOTE_DESTINATIONS_NEIGHBOURS));
		//
	}

	//
	// if all counters lower the alarm level or have nothing to say,
	// we tell the module manager to lower the level and unload channels
	//

	if ((exceeded & AGGREGATE_WATCH_ITEM::AGGREGATE_RESULT_LOWERALERT) == AGGREGATE_WATCH_ITEM::AGGREGATE_RESULT_LOWERALERT) {
		MessageAlert* msg = new MessageAlert (MessageAlert::ALERT_TYPE_LOWER_LEVEL, m_stage, alertMessage);
		MessagingNode::sendMessage (msg);
		//
		// SA-Eitzen-Armin:
		// Messages muessen auch an VNA zur Visualisierung gesendet werden
		// TODO: LISTE mit der IP der VNA-Instanz uebergeben
		// MessagingNode::sendMessage (msg, MessagingNode::SEND_OPTIONS::createBothAsync (MessagingNode::REMOTE_DESTINATIONS_NEIGHBOURS));
	}
}


void ModuleAnalyzerAggregateWatch::registerMessages ()
{
	MessagingNode::subscribeMessage (Message::MESSAGE_TYPE_TIMER);
	MessagingNode::subscribeMessage (Message::MESSAGE_TYPE_AGGREGATE_LAST_SUSPICIOUS);
}

void ModuleAnalyzerAggregateWatch::receiveMessage (Message* msg)
{
	if (msg->getType() == Message::MESSAGE_TYPE_TIMER) {
		if (((MessageTimer*)msg)->getName() == m_param_TimerModule)
			handleTimerMsg ();
	}

	if (msg->getType() == Message::MESSAGE_TYPE_AGGREGATE_LAST_SUSPICIOUS) {
		handleSuspiciousAggregateMsg (msg);
	}
}

void ModuleAnalyzerAggregateWatch::handleSuspiciousAggregateMsg (Message* msg)
{
	if (! msg->isRequest()) return;
	
	MessageLastSuspiciousAggregate* outMsg = NULL;

	if (m_lastSuspicious != NULL) {
		outMsg = new MessageLastSuspiciousAggregate (
			true, m_lastSuspicious->protocol, m_lastSuspicious->description);
	} else {
		outMsg = new MessageLastSuspiciousAggregate (false);
	}

	MessagingNode::sendMessage (outMsg);
}
