#include "ModuleAnalyzerProtocolAnomaly.h"

MODULE_INTERFACE( ModuleAnalyzerProtocolAnomaly )

const string ModuleAnalyzerProtocolAnomaly::PARAM_Interval  = "Interval";
const string ModuleAnalyzerProtocolAnomaly::PARAM_Anomalies = "Anomalies";

ModuleAnalyzerProtocolAnomaly::ModuleAnalyzerProtocolAnomaly ()
: m_currentAnomalyGroup (MessageLastAnomalyType::ANOMALY_TYPE_UNKNOWN)
{
	#define INSERT_ANOMALIE(x) m_anomalyNameValues.insert(ANOMALY_NAME_VALUE_PAIR(#x,x))

	INSERT_ANOMALIE( ANOMALY_KIND_TCP_COUNT_ANOMALY	 );
	INSERT_ANOMALIE( ANOMALY_KIND_TCP_IN_SYNACK_ANOMALY );
	INSERT_ANOMALIE( ANOMALY_KIND_TCP_OUT_SYNACK_ANOMALY );
	INSERT_ANOMALIE( ANOMALY_KIND_TCP_FIN_ANOMALY );
	INSERT_ANOMALIE( ANOMALY_KIND_TCP_RST_ANOMALY );
	INSERT_ANOMALIE( ANOMALY_KIND_UDP_ECHO_ANOMALY );
	INSERT_ANOMALIE( ANOMALY_KIND_ICMP_REQUEST_REPLY_ANOMALY );
	INSERT_ANOMALIE( ANOMALY_KIND_ICMP_REPLY_REQUEST_ANOMALY );
	INSERT_ANOMALIE( ANOMALY_KIND_ICMP_PORT_UNREACHABLE_ANOMALY );	
	INSERT_ANOMALIE( ANOMALY_KIND_ICMP_ERROR_MESSAGE_ANOMALY );
	INSERT_ANOMALIE( ANOMALY_KIND_ICMP_HOST_UNREACHABLE_ANOMALY );	
}

ModuleAnalyzerProtocolAnomaly::~ModuleAnalyzerProtocolAnomaly ()
{
	Timer::stop ();

	boost::mutex::scoped_lock scopedLock (m_hostAnomaliesMutex);	
	
	//
	// delete all the anomalies for all hosts
	//

	HOSTS_ANOMALIES::NODE_LIST nodes = m_hostAnomalies.GetNodeList ();
	HOSTS_ANOMALIES::NODE_LIST_ITERATOR i	  = nodes.begin ();
	HOSTS_ANOMALIES::NODE_LIST_ITERATOR iend  = nodes.end();

	for ( ; i != iend; i++) {
		ANOMALY_VECTOR anomalies = (*i)->GetData ();
		ANOMALY_VECTOR_ITERATOR anomBegin = anomalies.begin ();
		ANOMALY_VECTOR_ITERATOR anomEnd   = anomalies.end   ();

		for ( ; anomBegin != anomEnd; anomBegin++)
			delete *anomBegin;
	}
}

void ModuleAnalyzerProtocolAnomaly::registerMessages ()
{
	//
	// if no anomalies are given in the config, we query them
	//

	// THOMAS: Wenn die Anfrage in jedem Fall gemacht w�rde, 
	// k�nnte man auch von den konfigurierten Anomalien nur die ben�tigten laden
	if (m_param_Anomalies.length() <= 0) {

		MessagingNode::subscribeMessage (Message::MESSAGE_TYPE_ANOMALY_TYPE);
		
		MessageLastAnomalyType* request = new MessageLastAnomalyType ();
		request->setKind			(Message::MESSAGE_KIND_REQUEST);
		MessagingNode::sendMessage  (request);
	
	} // if (m_param_Anomalies.length() <= 0)
}

void ModuleAnalyzerProtocolAnomaly::receiveMessage (Message* msg)
{
	if (msg->getType() != Message::MESSAGE_TYPE_ANOMALY_TYPE) return;
	if (msg->getKind() != Message::MESSAGE_KIND_REPLY) return;

	MessageLastAnomalyType* msganomType = (MessageLastAnomalyType*)msg;
	m_currentAnomalyGroup = msganomType->getAnomalyType ();
}

bool ModuleAnalyzerProtocolAnomaly::configure (ModuleConfiguration& configList)
{
	m_stage = configList.stage;

	bool good = true;
	good &= configList.has (PARAM_Interval);
	configList.has (PARAM_Anomalies); // does not have to be available

	if (good) {

		m_param_Anomalies = configList.get(PARAM_Anomalies);

		//
		// check if all anomalies are known
		//

		Helper::STRING_LIST sanoms = Helper::split (m_param_Anomalies, ",");
		Helper::STRING_LIST_ITERATOR	i	= sanoms.begin  ();
		Helper::STRING_LIST_ITERATOR	iend	= sanoms.end    ();

		for ( ; i != iend; i++) {
			string anomname = *i;
			string::size_type found = anomname.find_first_of ("(");
			if (found != string::npos) anomname = anomname.substr (0, found); 

			ANOMALY_NAME_VALUE_MAP_ITERATOR item = m_anomalyNameValues.find (anomname);
			good &= (item != m_anomalyNameValues.end());
		}
		
		//
		// get the timer interval and start the timer
		//

		m_param_Interval  = configList.getLong (PARAM_Interval);

		Timer::setInterval (m_param_Interval);
		Timer::start ("AnalyzerProtocolAnomaly");
	}

	return good;
}

bool ModuleAnalyzerProtocolAnomaly::frameCall (Frame& frame)
{
	//
	// if the anomaly-group is not yet specified 
	// we can not analyze the frame. if the anomalies are
	// manually configured we can anyway
	//

	if (m_currentAnomalyGroup == MessageLastAnomalyType::ANOMALY_TYPE_UNKNOWN &&
		m_param_Anomalies.length() == 0	)
			return true;

	//
	// check all protocol layers until we have found an IP layer
	//

	frame.parsePackets ();
	IpPacket* ipPacket = NULL;

	for (Packet* i=frame.payloadpacket; i != NULL; i=i->getNextPacket()) {
		if (i->getProtocol() == Packet::PROTO_IP) {
			ipPacket = (IpPacket*)i;
			break;
		}
	}
	
	//
	// if we did not find any IP-packets we can not 
	// perform an in-depth analysis. exit and give 
	// other modules the chance to look at the frame (return true)
	//

	if (ipPacket == NULL) return true;

	//
	// find the anomaly vector in the patricia trie 
	// for the source and/or destination ip address
	//

	IP_ADDR sourceIp = ipPacket->getSourceip ();
	IP_ADDR destIp   = ipPacket->getDestip   ();

	{
		boost::mutex::scoped_lock scopedLock (m_hostAnomaliesMutex);

		HOSTS_ANOMALIES_NODE sourceNode = m_hostAnomalies.LookupNode (sourceIp);
		HOSTS_ANOMALIES_NODE destNode   = m_hostAnomalies.LookupNode (destIp);

		if (sourceNode != NULL) { 
			updateAnomalies (ipPacket, sourceNode->GetData(), false, sourceIp, destIp);	
		} else {
			ANOMALY_VECTOR anomalies = instanceAnomalies (
				m_anomalyNameValues, m_currentAnomalyGroup, m_param_Anomalies);
			m_hostAnomalies.Insert (sourceIp, anomalies);
		}

		if (destNode != NULL) { 
			updateAnomalies (ipPacket, destNode->GetData(), true, sourceIp, destIp);	
		} else {
			ANOMALY_VECTOR anomalies = instanceAnomalies (
				m_anomalyNameValues, m_currentAnomalyGroup, m_param_Anomalies);
			m_hostAnomalies.Insert (sourceIp, anomalies);
		}
	}

	return true;
}

void ModuleAnalyzerProtocolAnomaly::updateAnomalies (IpPacket* ipPacket, ANOMALY_VECTOR anomalies, bool incoming, IP_ADDR sourceIp, IP_ADDR destIp)
{
	for (Packet* pkt=ipPacket; pkt!=NULL; pkt=pkt->getNextPacket()) {
		
		Packet::PROTOCOL protocol = pkt->getProtocol ();

		//
		// update all the anomalies that registered for the given protocol
		//

		ANOMALY_VECTOR_ITERATOR anomBegin = anomalies.begin ();
		ANOMALY_VECTOR_ITERATOR anomEnd   = anomalies.end   ();

		for ( ; anomBegin != anomEnd; anomBegin++) {
				PPROTOCOL_ANOMALY anomaly = *anomBegin;

				if (anomaly->protocol == Packet::PROTO_MAXIMUM	||
					anomaly->protocol == Packet::PROTO_NONE	||
					anomaly->protocol == protocol)		{
					
					anomaly->analyze (pkt, incoming);
				}
				
		} // for ( ; anomBegin != anomEnd; anomBegin++)
	} // for (Packet* pkt=ipPacket; pkt!=NULL; pkt=pkt->getNextPacket())
}

ModuleAnalyzerProtocolAnomaly::ANOMALY_VECTOR ModuleAnalyzerProtocolAnomaly::instanceAnomalies (ANOMALY_NAME_VALUE_MAP anomNames, MessageLastAnomalyType::ANOMALY_TYPE group, string manualAnomalies)
{
	ANOMALY_VECTOR ret;

	//
	// we either instance over the anomaly group or by manually configured anomalies
	//

	if (!((group == MessageLastAnomalyType::ANOMALY_TYPE_UNKNOWN) ^ (manualAnomalies.length() == 0))) {
		logging_error( "don't know which protocol anomalies to create. invalid state");
		return ret;
	}

	if (group != MessageLastAnomalyType::ANOMALY_TYPE_UNKNOWN) {

		//
		// instance anomalies through an anomaly group
		//

		if ((group & MessageLastAnomalyType::ANOMALY_TYPE_DOS) == MessageLastAnomalyType::ANOMALY_TYPE_DOS) {

			ret.push_back (new TCP_COUNT_ANOMALY		());
			ret.push_back (new TCP_IN_SYNACK_ANOMALY	());
			ret.push_back (new TCP_OUT_SYNACK_ANOMALY	());
			ret.push_back (new TCP_FIN_ANOMALY		());
			ret.push_back (new TCP_RST_ANOMALY		(MessageLastAnomalyType::ANOMALY_TYPE_DOS));
			ret.push_back (new UDP_ECHO_ANOMALY		());
			ret.push_back (new ICMP_REQUEST_REPLY_ANOMALY	());
			ret.push_back (new ICMP_REPLY_REQUEST_ANOMALY	());
			ret.push_back (new ICMP_PORT_UNREACHABLE_ANOMALY(MessageLastAnomalyType::ANOMALY_TYPE_DOS));
			ret.push_back (new ICMP_ERROR_MESSAGE_ANOMALY	(MessageLastAnomalyType::ANOMALY_TYPE_DOS));
		
		} // if ((group & MessageLastAnomalyType::ANOMALY_TYPE_DOS) == MessageLastAnomalyType::ANOMALY_TYPE_DOS)

		if ((group & MessageLastAnomalyType::ANOMALY_TYPE_WORM) == 
				MessageLastAnomalyType::ANOMALY_TYPE_WORM) {

			ret.push_back (new TCP_RST_ANOMALY(
				MessageLastAnomalyType::ANOMALY_TYPE_WORM));
			ret.push_back (new ICMP_PORT_UNREACHABLE_ANOMALY(
				MessageLastAnomalyType::ANOMALY_TYPE_WORM));
			ret.push_back (new ICMP_ERROR_MESSAGE_ANOMALY(
				MessageLastAnomalyType::ANOMALY_TYPE_WORM));
			ret.push_back (new ICMP_HOST_UNREACHABLE_ANOMALY());

		} // if ((group & MessageLastAnomalyType::ANOMALY_TYPE_WORM) == MessageLastAnomalyType::ANOMALY_TYPE_WORM)

	} // if (m_currentAnomalyGroup != ANOMALY_TYPE_UNKNOWN)

	if (manualAnomalies.length() != 0) {
		
		//
		// instance anomalies through manual configuration
		//

		Helper::STRING_LIST sanoms = Helper::split (manualAnomalies, ",");
		Helper::STRING_LIST_ITERATOR i    = sanoms.begin ();
		Helper::STRING_LIST_ITERATOR iend = sanoms.end   ();

		for ( ; i != iend; i++) {

			string content  = *i;
			string anomName = "";
			string anomType = "";

			string::size_type found = content.find_first_of ("(");
			if (found != string::npos) {
				anomName = content.substr (0, found);
				anomType = content.substr (found+1, content.length()-found-2);
			} else {
				anomName = content;
				anomType = "";
			}

			ANOMALY_NAME_VALUE_MAP_ITERATOR item = anomNames.find (anomName);
			if (item == anomNames.end()) {
				logging_error( "anomaly " + *i + " not found");
				continue;
			}

			MessageLastAnomalyType::ANOMALY_TYPE group = MessageLastAnomalyType::ANOMALY_TYPE_ALL;

			if (anomType.length() > 0) {

				if (anomType == "DDOS") group = MessageLastAnomalyType::ANOMALY_TYPE_DOS;
				else if (anomType == "WORM") group = MessageLastAnomalyType::ANOMALY_TYPE_WORM;
				else logging_warn( "unknown anomaly group " + anomType + "... using ALL type instead");
			
			} // if (anomType.length() > 0)

			PPROTOCOL_ANOMALY anomalyObj = NULL;

			// THOMAS: Werden hier nicht auch falsche Anomalien instanziiert (z.B. Wurmanomalien, obwohl group == DOS ist)?
			switch (item->second) {
				case ANOMALY_KIND_TCP_COUNT_ANOMALY:
					anomalyObj = new TCP_COUNT_ANOMALY (); break;
				case ANOMALY_KIND_TCP_IN_SYNACK_ANOMALY:
					anomalyObj = new TCP_IN_SYNACK_ANOMALY (); break;
				case ANOMALY_KIND_TCP_OUT_SYNACK_ANOMALY:			
					anomalyObj = new TCP_OUT_SYNACK_ANOMALY (); break;
				case ANOMALY_KIND_TCP_FIN_ANOMALY:
					anomalyObj = new TCP_FIN_ANOMALY (); break;
				case ANOMALY_KIND_TCP_RST_ANOMALY:
					anomalyObj = new TCP_RST_ANOMALY (group); break;
				case ANOMALY_KIND_UDP_ECHO_ANOMALY:
					anomalyObj = new UDP_ECHO_ANOMALY (); break;
				case ANOMALY_KIND_ICMP_REQUEST_REPLY_ANOMALY:
					anomalyObj = new ICMP_REQUEST_REPLY_ANOMALY (); break;
				case ANOMALY_KIND_ICMP_REPLY_REQUEST_ANOMALY:
					anomalyObj = new ICMP_REPLY_REQUEST_ANOMALY (); break;
				case ANOMALY_KIND_ICMP_PORT_UNREACHABLE_ANOMALY:
					anomalyObj = new ICMP_PORT_UNREACHABLE_ANOMALY (group);	break;
				case ANOMALY_KIND_ICMP_ERROR_MESSAGE_ANOMALY:
					anomalyObj = new ICMP_ERROR_MESSAGE_ANOMALY (group); break;
				case ANOMALY_KIND_ICMP_HOST_UNREACHABLE_ANOMALY:
					anomalyObj = new ICMP_HOST_UNREACHABLE_ANOMALY (); break;
				default: assert (false); break;
			}

			ret.push_back (anomalyObj);
		}

	} // if (m_param_Anomalies.length() != 0)

	return ret;
}

void ModuleAnalyzerProtocolAnomaly::eventFunction ()
{
	//
	// check all the anomalies for all hosts for abnomalies
	//

	boost::mutex::scoped_lock scopedLock (m_hostAnomaliesMutex);

	HOSTS_ANOMALIES::NODE_LIST nodes = m_hostAnomalies.GetNodeList ();
	HOSTS_ANOMALIES::NODE_LIST::iterator i	  = nodes.begin ();
	HOSTS_ANOMALIES::NODE_LIST::iterator iend = nodes.end	();

	for ( ; i != iend; i++) {
		
		HOSTS_ANOMALIES_NODE node = *i;
		IP_ADDR	addr = node->GetKey ();

		//
		// walk the anomalies for the host and check for abnormal stuff
		//

		ANOMALY_VECTOR anomalies = node->GetData ();
		ANOMALY_VECTOR_ITERATOR iAnom	 = anomalies.begin ();
		ANOMALY_VECTOR_ITERATOR iEndAnom = anomalies.end   ();

		for ( ; iAnom != iEndAnom; iAnom++) {
			
			PROTOCOL_ANOMALY* anomaly = *iAnom;

			if (! anomaly->balanced()) {

				MessageAlert::ALERT_TYPE type = MessageAlert::ALERT_TYPE_RAISE_LEVEL;
				string strmsg = "protocol anomaly "				+
								getAnomalyName (anomaly->kind)	+ 
								" found for host "		+ 
								addr.toString()			;

				MessageAlert* alertMsg = new MessageAlert (type, m_stage, strmsg);
				sendMessage (alertMsg);

			}

		} // for ( ; iAnom != iEndAnom; iAnom++)

	} // for ( ; i != iend; i++)
}

string ModuleAnalyzerProtocolAnomaly::getAnomalyName (ANOMALY_KIND kind)
{
	ANOMALY_NAME_VALUE_MAP_ITERATOR i		= m_anomalyNameValues.begin ();
	ANOMALY_NAME_VALUE_MAP_ITERATOR iend	= m_anomalyNameValues.end	();

	for ( ; i != iend; i++)
		if (i->second == kind) return i->first;

	return "unknown";
}
