#include "ModuleAnalyzerAddressSpace.h"

MODULE_INTERFACE(ModuleAnalyzerAddressSpace);

const string ModuleAnalyzerAddressSpace::PARAM_SubnetChangePercent  = "SubnetChangePercent";
const string ModuleAnalyzerAddressSpace::PARAM_ActiveSubnetPackets  = "ActiveSubnetPackets";
const string ModuleAnalyzerAddressSpace::PARAM_ActiveSubnetRelation = "ActiveSubnetRelation";

ModuleAnalyzerAddressSpace::ModuleAnalyzerAddressSpace ()
{
	m_haveAggregate		 = false;
	m_haveIntervalValues = false;
	m_haveSubnetTree	 = false;
}

ModuleAnalyzerAddressSpace::~ModuleAnalyzerAddressSpace ()
{
}

bool ModuleAnalyzerAddressSpace::configure (ModuleConfiguration& configList)
{
	m_stage = configList.stage;

	bool good = true;
	good &= configList.has (PARAM_SubnetChangePercent);
	good &= configList.has (PARAM_ActiveSubnetPackets);
	good &= configList.has (PARAM_ActiveSubnetRelation);

	if (good) {
		
		long value = configList.getLong (PARAM_SubnetChangePercent);
		good &= (value >= 0 && value <= 100);
		if (good) m_param_SubnetChangePercent = (short) value;

		m_param_ActiveSubnetPackets  = configList.getLong	(PARAM_ActiveSubnetPackets);
		m_param_ActiveSubnetRelation = configList.getDouble	(PARAM_ActiveSubnetRelation);
	}

	return good;
}

void ModuleAnalyzerAddressSpace::registerMessages ()
{
	//
	// register for address distribution message
	// register for last suspicious aggregate message
	//
	// send out a request for all the registered messages
	// but not for the interval-values. we need
	// the last suspicious aggregate first so we can use it
	// in the request message
	//

	subscribeMessage (Message::MESSAGE_TYPE_ADDRESS_DISTRIBUTION		);
	subscribeMessage (Message::MESSAGE_TYPE_AGGREGATE_LAST_SUSPICIOUS	);
	subscribeMessage (Message::MESSAGE_TYPE_AGGREGATE_INTERVAL_VALUES	);
	subscribeMessage (Message::MESSAGE_TYPE_ANOMALY_TYPE				);

	MessageAddressDistribution*		distribMsg	= new MessageAddressDistribution	 ();
	MessageLastSuspiciousAggregate* suspMsg		= new MessageLastSuspiciousAggregate ();
	
	distribMsg->setKind (Message::MESSAGE_KIND_REQUEST);
	suspMsg->setKind	(Message::MESSAGE_KIND_REQUEST);

	sendMessage (distribMsg);
	sendMessage (suspMsg);
}	

void ModuleAnalyzerAddressSpace::receiveMessage (Message* msg)
{
	//
	// handle the appropriate message in special handlers
	//

	if (msg->getType() == Message::MESSAGE_TYPE_ADDRESS_DISTRIBUTION)
		handleSubnetDistributionMsg (msg);
	else if (msg->getType() == Message::MESSAGE_TYPE_AGGREGATE_LAST_SUSPICIOUS)
		handleLastSuspiciousAggrMsg (msg);
	else if (msg->getType() == Message::MESSAGE_TYPE_AGGREGATE_INTERVAL_VALUES)
		handleAggregateIntervalValues (msg);
	else if (msg->getType() == Message::MESSAGE_TYPE_ANOMALY_TYPE)
		handleLastAnomalyMsg (msg);

	//
	// if we have got all the information we need, start analyzing
	//

	if (m_haveAggregate && m_haveIntervalValues && m_haveSubnetTree)
		analyze ();
}						
						
void ModuleAnalyzerAddressSpace::handleLastAnomalyMsg (Message* msg)
{
	if (! msg->isRequest()) return;
	
	MessageLastAnomalyType* reply = new MessageLastAnomalyType (m_lastAnomalyType);
	sendMessage (reply);
}

void ModuleAnalyzerAddressSpace::handleSubnetDistributionMsg (Message* msg)
{
	if (! msg->isReply()) return;
	boost::mutex::scoped_lock scopedLock (m_analyzerMutex);
	MessageAddressDistribution* distMsg = (MessageAddressDistribution*) msg;
	
	TREE_VECTOR_ITERATOR oldBegin = m_intervalSubnets.begin ();
	TREE_VECTOR_ITERATOR oldEnd   = m_intervalSubnets.end   ();

	for ( ; oldBegin != oldEnd; oldBegin++)
		delete *oldBegin;
	
	m_intervalSubnets.clear ();

	for (unsigned int i=0; i<distMsg->getSubnetDistribCount(); i++) {
		
		SubnetCounterTree* treeCopy = distMsg->getSubnetDistrib(i)->copy ();
		m_intervalSubnets.push_back (treeCopy);

	}

	m_haveSubnetTree = true;
}

void ModuleAnalyzerAddressSpace::handleLastSuspiciousAggrMsg (Message* msg)
{
	if (! msg->isReply()) return;
	boost::mutex::scoped_lock scopedLock (m_analyzerMutex);
	MessageLastSuspiciousAggregate* inMsg = (MessageLastSuspiciousAggregate*)msg;

	//
	// save the last suspicious aggregate
	//

	m_suspiciousAggregateProtocol	 = inMsg->getProtocol ();
	m_suspiciousAggregateDescription = inMsg->getDescription ();
	if (inMsg->suspiciousAggregateExists ())
		m_haveAggregate					 = true;

	assert (m_haveAggregate == true);

	//
	// send out a request for the last interval values for this aggregate
	//

	MessageAggregateIntervalValues* outMsg = new MessageAggregateIntervalValues ();
	
	outMsg->setKind		   (Message::MESSAGE_KIND_REQUEST);
	outMsg->setProtocol    (inMsg->getProtocol ());
	outMsg->setDescription (inMsg->getDescription ());

	MessagingNode::sendMessage (outMsg);
}

void ModuleAnalyzerAddressSpace::handleAggregateIntervalValues (Message* msg)
{
	if (! msg->isReply()) return;
	boost::mutex::scoped_lock scopedLock (m_analyzerMutex);
	MessageAggregateIntervalValues* inMsg = (MessageAggregateIntervalValues*)msg;
	
	//
	// save the last interval count/threshold values
	// for the aggregate we already now
	//

	m_intervalValues = MessageAggregateIntervalValues::INTERVAL_ITEMS (inMsg->getIntervals ());
	m_haveIntervalValues = true;
}

void ModuleAnalyzerAddressSpace::analyze ()
{
	boost::mutex::scoped_lock scopedLock (m_analyzerMutex);
	//
	// find the first interval where the frame counter exceeded the thresold
	//

	int intervalLastNormal		= -1;
	int intervalFirstAbnormal	= -1;

	TREE_VECTOR_ITERATOR intervalBegin = m_intervalSubnets.begin ();
	TREE_VECTOR_ITERATOR intervalEnd   = m_intervalSubnets.end   ();

	assert (m_intervalSubnets.size() <= m_intervalValues.size());

	for (unsigned int i=0; intervalBegin != intervalEnd; i++, intervalBegin++) {

		//
		// read count and threshold value of interval i
		//

		MessageAggregateIntervalValues::COUNT_THRESHOLD_PAIR values	= m_intervalValues[i];

		//
		// if count is bigger than threshold we found the first abnormal interval
		//

		if (values.first > values.second) {
			intervalLastNormal	  = i - 1;
			intervalFirstAbnormal = i;
			break;
		} 
	}

	//
	// no abnormal intervals were found or we have no normal reference interval. exit
	//

	if (intervalFirstAbnormal < 0 || intervalLastNormal < 0) {
		MessageAlert* alertMsg = new MessageAlert (
			MessageAlert::ALERT_TYPE_LOWER_LEVEL, 
			m_stage, 
			"invalid alert, no abnormal intervals found"
			);
		MessagingNode::sendMessage (alertMsg);	
		//
		// SA-Eitzen-Armin:
		// Messages muessen auch an VNA zur Visualisierung gesendet werden
		// TODO: LISTE mit der IP der VNA-Instanz uebergeben
		// MessagingNode::sendMessage (alertMsg, MessagingNode::SEND_OPTIONS::createBothAsync (MessagingNode::REMOTE_DESTINATIONS_NEIGHBOURS));
		//

		return;
	}

	//
	// find the attacked subnets
	//

	IP_ADDR_VECTOR attackedSubnets = analyzeFindAttackedSubnets (intervalLastNormal, intervalFirstAbnormal);

	//
	// check if the attack is a distributed attack
	//

	bool distributed = analyzeIsDistributedAttack (intervalLastNormal, intervalFirstAbnormal);

	//
	// if we found an attacked subnet or a distributed attack we 
	// raise a positive alert, else a negative alert
	//

	MessageAlert::ALERT_TYPE alertType;
	string					 alertMsg;
	
	m_lastAnomalyType = MessageLastAnomalyType::ANOMALY_TYPE_UNKNOWN;

	// THOMAS: Waere es nicht sinnvoll, in jedem Fall die 3. Stufe zu laden (Wurmausbreitung aus vereinzelten Subnetzen)
	if (attackedSubnets.size() >= 1 || distributed) {
		alertType = MessageAlert::ALERT_TYPE_RAISE_LEVEL;
	
		if (attackedSubnets.size() == 1) {
			alertMsg = "found attack on subnet " + attackedSubnets[0].toString();
			m_lastAnomalyType = MessageLastAnomalyType::ANOMALY_TYPE_DOS;
		} else if (distributed) {
			alertMsg = "found distributed attack";
			m_lastAnomalyType = MessageLastAnomalyType::ANOMALY_TYPE_WORM;
		}

		if (attackedSubnets.size() > 1)
			m_lastAnomalyType = MessageLastAnomalyType::ANOMALY_TYPE_WORM;

	} else {
		alertType = MessageAlert::ALERT_TYPE_LOWER_LEVEL;
		alertMsg  = "no attacked subnet or distributed attack found. lowering alert level";
	}	

	MessageAlert* alertObj = new MessageAlert (alertType, m_stage, alertMsg);
	MessagingNode::sendMessage (alertObj);

	//
	// SA-Eitzen-Armin:
	// Messages muessen auch an VNA zur Visualisierung gesendet werden
	// TODO: LISTE mit der IP der VNA-Instanz uebergeben
	// MessagingNode::sendMessage (alertObj, MessagingNode::SEND_OPTIONS::createBothAsync (MessagingNode::REMOTE_DESTINATIONS_NEIGHBOURS));
	//

}

ModuleAnalyzerAddressSpace::IP_ADDR_VECTOR ModuleAnalyzerAddressSpace::analyzeFindAttackedSubnets (unsigned int intervalLastNormal, unsigned int intervalFirstAbnormal)
{
	IP_ADDR_VECTOR attackedSubnets;

	//
	// get the subnet distribution of the last normal interval
	// it will be used as reference against the abnormal intervals
	//

	SubnetCounterTree* normalTree = m_intervalSubnets [intervalLastNormal];
	SubnetCounterTree::SUBNET_DISTRIBUTION_NODE_LIST normalSubnets = normalTree->getSubnets ();

	//
	// iterate all abnormal intervals and find subnets that are responsible
	// for the increase in aggregate counters
	//

	for (unsigned int i=intervalFirstAbnormal; i<m_intervalSubnets.size(); i++) {

		SubnetCounterTree* curTree = m_intervalSubnets [i];
		MessageAggregateIntervalValues::COUNT_THRESHOLD_PAIR curValues  = m_intervalValues  [i];

		SubnetCounterTree::SUBNET_DISTRIBUTION_NODE_LIST curSubnets = curTree->getSubnets ();
		assert (normalSubnets.size() == curSubnets.size());

		//
		// how much did the count exceed the threshold in percent?
		// e.g.: count=50, thres=25 -> (50/25)-1 = 1 --> 100% exceeding
		// if the result is <= 0, there is no exceeding in this interval
		// so we skip it as it is a normal interval
		//

		double threshExceeding = 0.;
		if (curValues.second != 0) threshExceeding = (curValues.first / curValues.second) - 1;
		if (threshExceeding <= 0) continue;	

		SubnetCounterTree::SUBNET_DISTRIBUTION_NODE_LIST_ITERATOR normalBegin = normalSubnets.begin ();
		SubnetCounterTree::SUBNET_DISTRIBUTION_NODE_LIST_ITERATOR normalEnd   = normalSubnets.end   ();

		SubnetCounterTree::SUBNET_DISTRIBUTION_NODE_LIST_ITERATOR curBegin    = curSubnets.begin	();
		SubnetCounterTree::SUBNET_DISTRIBUTION_NODE_LIST_ITERATOR curEnd      = curSubnets.end		();

		//
		// check all current subnets from this interval against the (same) normal subnets
		// from the last normal interval, which showed no anomaly
		//

		for ( ; normalBegin != normalEnd && curBegin != curEnd; normalBegin++, curBegin++) {

			// must be the same subnet ip address
			assert ((*normalBegin)->GetKey() == (*curBegin)->GetKey());
			IP_ADDR subnetAddr = (*normalBegin)->GetKey();

			SubnetCounterTree::ADDR_COUNTER normalCount  = (*normalBegin)->GetData	();			
			SubnetCounterTree::ADDR_COUNTER curCount	 = (*curBegin)->GetData		();			
			
			double subnetExceeding = 0;
			if (normalCount.dstCount != 0)
				subnetExceeding = ((double)curCount.dstCount / (double)normalCount.dstCount) - 1;

			//
			// An attacked subnet must see at least X packets in an interval - otherwise it might as well be a random deviation
			//

			if (curCount.dstCount < m_param_ActiveSubnetPackets) { 
				subnetExceeding = 0;
			}

			bool suspicious = subnetExceeding > (((double)m_param_SubnetChangePercent / 100) * threshExceeding);

			if (suspicious) {
				
				//
				// if this is a new suspicious subnet, insert it into the found ones
				//

				if (find (attackedSubnets.begin(), attackedSubnets.end(), subnetAddr) == attackedSubnets.end())
					attackedSubnets.push_back (subnetAddr);

			} // if (suspicious)

		} // for ( ; normalBegin != normalEnd && curBegin != curEnd; normalBegin++, curBegin++)
	
	} // for (unsigned int i=intervalFirstAbnormal; i<distMsg->getSubnetDistribCount(); i++)

	return attackedSubnets;
}

bool ModuleAnalyzerAddressSpace::analyzeIsDistributedAttack (unsigned int intervalLastNormal, unsigned int intervalFirstAbnormal)
{
	//
	// walk the intervals starting from the first abnormal interval till the end
	//

	unsigned int normalIntervals					= 0;
	unsigned int abnormalIntervals					= 0;
	unsigned int activeSubnetsInNormalIntervals		= 0;
	unsigned int activeSubnetsInAbnormalIntervals	= 0;

	for (unsigned int i=intervalLastNormal; i<m_intervalSubnets.size(); i++) {

		SubnetCounterTree*									 curTree	= m_intervalSubnets [i];
		MessageAggregateIntervalValues::COUNT_THRESHOLD_PAIR values		= m_intervalValues  [i];
	
		//
		// an interval is normal if the threshold is bigger than the counter
		//

		bool normalInterval = values.second >= values.first;

		if (normalInterval)	normalIntervals++;
		else				abnormalIntervals++;

		//
		// count the active subnets in this interval
		//
		
		unsigned int activeSubnets = 0;

		SubnetCounterTree::SUBNET_DISTRIBUTION_NODE_LIST			curSubnets	 = curTree->getSubnets ();
		SubnetCounterTree::SUBNET_DISTRIBUTION_NODE_LIST_ITERATOR	subnetsBegin = curSubnets.begin	  ();
		SubnetCounterTree::SUBNET_DISTRIBUTION_NODE_LIST_ITERATOR	subnetsEnd	 = curSubnets.end	  ();

		for ( ; subnetsBegin != subnetsEnd; subnetsBegin++) {
			
			if ((*subnetsBegin)->GetData().srcCount > m_param_ActiveSubnetPackets)
				activeSubnets++;
	
		} // for ( ; subnetsBegin != subnetsEnd; subnetsBegin++)

		if (normalInterval) activeSubnetsInNormalIntervals   += activeSubnets;
		else				activeSubnetsInAbnormalIntervals += activeSubnets;

	} // for (unsigned int i=intervalFirstAbnormal; i<m_intervalSubnets.size(); i++)

	//
	// analyze the collected number of active, non active subnets
	//
	
	assert(normalIntervals > 0);
	assert(abnormalIntervals > 0);

	double averageNormal	= (double)activeSubnetsInNormalIntervals   / (double)normalIntervals;
	double averageAbnormal	= (double)activeSubnetsInAbnormalIntervals / (double)abnormalIntervals;

	return (averageAbnormal >= (m_param_ActiveSubnetRelation * averageNormal));
}
