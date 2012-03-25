#ifndef __MODULE_ANALYZER_PROTOCOL_ANOMALY_H
#define __MODULE_ANALYZER_PROTOCOL_ANOMALY_H

#include "base/common/Log.h"
#include "base/protocol/Packet.h"
#include "base/protocol/Frame.h"
#include "base/protocol/TcpPacket.h"
#include "base/protocol/IcmpPacket.h"
#include "base/protocol/UdpPacket.h"
#include "messages/attackdetection/MessageLastAnomalyType.h"
#include "messages/utility/MessageAlert.h"
#include "base/module/DistackModuleInterface.h"
#include "base/common/PatriciaTrie.h"
#include "base/common/Timer.h"

#define MIN_PACKET_COUNT	100

class ModuleAnalyzerProtocolAnomaly : public DistackModuleInterface {
public:
	ModuleAnalyzerProtocolAnomaly();
	~ModuleAnalyzerProtocolAnomaly();

	void registerMessages();
	void receiveMessage( Message* msg );

	bool configure( ModuleConfiguration& configList );
	bool frameCall( Frame& frame );

	void eventFunction();

private:

	static const string	PARAM_Interval;
	static const string	PARAM_Anomalies;

	unsigned int		m_param_Interval;
	string			m_param_Anomalies;

	typedef enum _ANOMALY_KIND {
		ANOMALY_KIND_NONE				, // <-- BEGIN delimiter
		ANOMALY_KIND_TCP_COUNT_ANOMALY			,
		ANOMALY_KIND_TCP_IN_SYNACK_ANOMALY		,
		ANOMALY_KIND_TCP_OUT_SYNACK_ANOMALY		,
		ANOMALY_KIND_TCP_FIN_ANOMALY			,
		ANOMALY_KIND_TCP_RST_ANOMALY			,
		ANOMALY_KIND_UDP_ECHO_ANOMALY			,
		ANOMALY_KIND_ICMP_REQUEST_REPLY_ANOMALY		,
		ANOMALY_KIND_ICMP_REPLY_REQUEST_ANOMALY		,
		ANOMALY_KIND_ICMP_PORT_UNREACHABLE_ANOMALY	,
		ANOMALY_KIND_ICMP_ERROR_MESSAGE_ANOMALY		,
		ANOMALY_KIND_ICMP_HOST_UNREACHABLE_ANOMALY	,
		ANOMALY_KIND_MAX				, // <-- END delimiter
	} ANOMALY_KIND; 

	typedef pair<string, ANOMALY_KIND>		ANOMALY_NAME_VALUE_PAIR;
	typedef map<string,  ANOMALY_KIND>		ANOMALY_NAME_VALUE_MAP;
	typedef ANOMALY_NAME_VALUE_MAP::iterator	ANOMALY_NAME_VALUE_MAP_ITERATOR;

	ANOMALY_NAME_VALUE_MAP m_anomalyNameValues;
	string getAnomalyName( ANOMALY_KIND kind );
		
	typedef struct _PROTOCOL_ANOMALY {
		Packet::PROTOCOL			protocol;
		ANOMALY_KIND				kind;
		MessageLastAnomalyType::ANOMALY_TYPE	anomGroup;
		unsigned int				countLeft;
		unsigned int				countRight;

		_PROTOCOL_ANOMALY () {
			protocol  = Packet::PROTO_NONE;
			countLeft = countRight = 0;
			kind	  = ANOMALY_KIND_NONE;
		}

		virtual bool balanced () {
			if (countLeft < MIN_PACKET_COUNT || countRight < MIN_PACKET_COUNT) 
				return true;

			return !(countLeft > (getLambda() * countRight));
		}

		void analyze (Packet* pkt, bool incoming) {

			//
			// depending on the anomaly group we 
			// have to take the direction of the
			// packet into account or not
			//

			if (anomGroup == MessageLastAnomalyType::ANOMALY_TYPE_DOS) {

				if ( incoming && acceptLeft (pkt)) countLeft++;
				if (!incoming && acceptRight(pkt)) countRight++;	
			
			} else if (anomGroup == MessageLastAnomalyType::ANOMALY_TYPE_WORM) {
					
				if (acceptLeft  (pkt)) countLeft++;
				if (acceptRight (pkt)) countRight++;

			}
		}

		virtual bool	acceptLeft  (Packet* pkt)	= 0;
		virtual bool	acceptRight (Packet* pkt)	= 0;
		virtual double	getLambda   ()			= 0;

	} PROTOCOL_ANOMALY, *PPROTOCOL_ANOMALY;  

	typedef vector<PROTOCOL_ANOMALY*>			ANOMALY_VECTOR;
	typedef ANOMALY_VECTOR::iterator			ANOMALY_VECTOR_ITERATOR;
	typedef PatriciaTrie<IP_ADDR, ANOMALY_VECTOR>		HOSTS_ANOMALIES;
	typedef PatriciaTrieNode<IP_ADDR, ANOMALY_VECTOR>*	HOSTS_ANOMALIES_NODE;
	boost::mutex						m_hostAnomaliesMutex;
	HOSTS_ANOMALIES						m_hostAnomalies;


	MessageLastAnomalyType::ANOMALY_TYPE			m_currentAnomalyGroup;
	unsigned short						m_stage;

	ANOMALY_VECTOR instanceAnomalies( 
		ANOMALY_NAME_VALUE_MAP anomNames, 
		MessageLastAnomalyType::ANOMALY_TYPE group, 
		string manualAnomalies
		);

	void updateAnomalies( 
		IpPacket* ipPacket, 
		ANOMALY_VECTOR anomalies, 
		bool incoming, 
		IP_ADDR sourceIp, 
		IP_ADDR destIp
		);

	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// IN(TCP) > OUT(TCP)
	//
	typedef struct _TCP_COUNT_ANOMALY : public PROTOCOL_ANOMALY{
		_TCP_COUNT_ANOMALY () {
			protocol  = Packet::PROTO_TCP;
			kind      = ModuleAnalyzerProtocolAnomaly::ANOMALY_KIND_TCP_COUNT_ANOMALY;
			anomGroup = MessageLastAnomalyType::ANOMALY_TYPE_DOS;
		}
		bool acceptLeft (Packet* pkt) {
			return true;
		}
		bool acceptRight (Packet* pkt) {
			return acceptLeft (pkt);
		}
		double getLambda () {
			return 1.05;
		}
	} TCP_COUNT_ANOMALY;

	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// IN(TCP.SYN-ACK) > OUT(TCP.SYN)
	//
	typedef struct _TCP_IN_SYNACK_ANOMALY : public PROTOCOL_ANOMALY {
		_TCP_IN_SYNACK_ANOMALY () {
			protocol  = Packet::PROTO_TCP;
			kind	  = ModuleAnalyzerProtocolAnomaly::ANOMALY_KIND_TCP_IN_SYNACK_ANOMALY;
			anomGroup = MessageLastAnomalyType::ANOMALY_TYPE_DOS;
		}
		bool acceptLeft (Packet* pkt) {
			TcpPacket* tcpPkt = (TcpPacket*)pkt;
			return (tcpPkt->isFlagSet(TcpPacket::TCP_FLAG_SYN)	&& 
					tcpPkt->isFlagSet(TcpPacket::TCP_FLAG_ACK)	);
		}
		bool acceptRight (Packet* pkt) {
			TcpPacket* tcpPkt = (TcpPacket*)pkt;
			return (   tcpPkt->isFlagSet(TcpPacket::TCP_FLAG_SYN)	&& 
					 (!tcpPkt->isFlagSet(TcpPacket::TCP_FLAG_ACK))	);
		}
		double getLambda () {
			return 1.05;
		}
	} TCP_IN_SYNACK_ANOMALY;

	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// IN(TCP.SYN) > OUT (TCP.SYN-ACK)
	//
	typedef struct _TCP_OUT_SYNACK_ANOMALY : public PROTOCOL_ANOMALY {
		_TCP_OUT_SYNACK_ANOMALY () {
			protocol  = Packet::PROTO_TCP;
			kind	  = ModuleAnalyzerProtocolAnomaly::ANOMALY_KIND_TCP_OUT_SYNACK_ANOMALY;
			anomGroup = MessageLastAnomalyType::ANOMALY_TYPE_DOS;
		}
		bool acceptLeft (Packet* pkt) {
			TcpPacket* tcpPkt = (TcpPacket*)pkt;
			return (   tcpPkt->isFlagSet(TcpPacket::TCP_FLAG_SYN)	&& 
					 (!tcpPkt->isFlagSet(TcpPacket::TCP_FLAG_ACK))	);
		}
		bool acceptRight (Packet* pkt) {
			TcpPacket* tcpPkt = (TcpPacket*)pkt;
			return (tcpPkt->isFlagSet(TcpPacket::TCP_FLAG_SYN)	&& 
					tcpPkt->isFlagSet(TcpPacket::TCP_FLAG_ACK)	);
		}
		double getLambda () {
			return 1.05;
		}
	} TCP_OUT_SYNACK_ANOMALY;

	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// IN(TCP.FIN) > OUT(TCP.FIN)
	//
	typedef struct _TCP_FIN_ANOMALY : public PROTOCOL_ANOMALY {
		_TCP_FIN_ANOMALY () {
			protocol  = Packet::PROTO_TCP;
			kind	  = ModuleAnalyzerProtocolAnomaly::ANOMALY_KIND_TCP_FIN_ANOMALY;
			anomGroup = MessageLastAnomalyType::ANOMALY_TYPE_DOS;
		}
		bool acceptLeft (Packet* pkt) {
			TcpPacket* tcpPkt = (TcpPacket*)pkt;
			return tcpPkt->isFlagSet (TcpPacket::TCP_FLAG_FIN);
		}
		bool acceptRight (Packet* pkt) {
			return acceptLeft (pkt);
		}
		double getLambda () {
			return 1.05;
		}
	} TCP_FIN_ANOMALY;

	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// IN (TCP.RST) > lambda * OUT(TCP) (in case of group == ANOMALY_TYPE_DOS)
	// ALL(TCP.RST) > lambda * ALL(TCP) (in case of group == ANOMALY_TYPE_WORM)
	//
	typedef struct _TCP_RST_ANOMALY : public PROTOCOL_ANOMALY {
		_TCP_RST_ANOMALY (MessageLastAnomalyType::ANOMALY_TYPE group) {
			protocol  = Packet::PROTO_TCP;
			kind	  = ModuleAnalyzerProtocolAnomaly::ANOMALY_KIND_TCP_RST_ANOMALY;
			anomGroup = group;
		}
		bool acceptLeft (Packet* pkt) {
			TcpPacket* tcpPkt = (TcpPacket*)pkt;
			return tcpPkt->isFlagSet (TcpPacket::TCP_FLAG_RST);
		}
		bool acceptRight (Packet* pkt) {
			return true;
		}
		double getLambda () {
			return 1.5;
		}
	} TCP_RST_ANOMALY;

	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// IN(UDP.Echo) > OUT(UDP.Echo)
	//
	typedef struct _UDP_ECHO_ANOMALY : public PROTOCOL_ANOMALY {
		_UDP_ECHO_ANOMALY () {
			protocol  = Packet::PROTO_UDP;
			kind	  = ModuleAnalyzerProtocolAnomaly::ANOMALY_KIND_UDP_ECHO_ANOMALY;
			anomGroup = MessageLastAnomalyType::ANOMALY_TYPE_DOS;
		}
		bool acceptLeft (Packet* pkt) {
			UdpPacket* udpPkt = (UdpPacket*)pkt;
			return (udpPkt->getDestport() == 0x7);
		}
		bool acceptRight (Packet* pkt) {
			UdpPacket* udpPkt = (UdpPacket*)pkt;
			return (udpPkt->getSourceport() == 0x7);
		}
		double getLambda () {
			return 1.05;
		}
	} UDP_ECHO_ANOMALY;

	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// IN(ICMP.Reply) > OUT(ICMP.Request)
	//
	typedef struct _ICMP_REQUEST_REPLY_ANOMALY : public PROTOCOL_ANOMALY {
		_ICMP_REQUEST_REPLY_ANOMALY () {
			protocol  = Packet::PROTO_ICMP;
			kind	  = ModuleAnalyzerProtocolAnomaly::ANOMALY_KIND_ICMP_REQUEST_REPLY_ANOMALY;
			anomGroup = MessageLastAnomalyType::ANOMALY_TYPE_DOS;
		}
		bool acceptLeft (Packet* pkt) {
			IcmpPacket* icmpPkt = (IcmpPacket*)pkt;
			return (icmpPkt->getType() == IcmpPacket::ICMP_TYPE_ECHO_REPLY);
		}
		bool acceptRight (Packet* pkt) {
			IcmpPacket* icmpPkt = (IcmpPacket*)pkt;
			return (icmpPkt->getType() == IcmpPacket::ICMP_TYPE_ECHO_REQUEST);
		}
		double getLambda () {
			return 1.05;
		}
	} ICMP_REQUEST_REPLY_ANOMALY;

	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// IN(ICMP.Request) > OUT(ICMP.Reply)
	//
	typedef struct _ICMP_REPLY_REQUEST_ANOMALY : public PROTOCOL_ANOMALY {
		_ICMP_REPLY_REQUEST_ANOMALY () {
			protocol  = Packet::PROTO_ICMP;
			kind	  = ModuleAnalyzerProtocolAnomaly::ANOMALY_KIND_ICMP_REPLY_REQUEST_ANOMALY;
			anomGroup = MessageLastAnomalyType::ANOMALY_TYPE_DOS;
		}
		bool acceptLeft (Packet* pkt) {
			IcmpPacket* icmpPkt = (IcmpPacket*)pkt;
			return (icmpPkt->getType() == IcmpPacket::ICMP_TYPE_ECHO_REQUEST);
		}
		bool acceptRight (Packet* pkt) {
			IcmpPacket* icmpPkt = (IcmpPacket*)pkt;
			return (icmpPkt->getType() == IcmpPacket::ICMP_TYPE_ECHO_REPLY);
		}
		double getLambda () {
			return 1.05;
		}
	} ICMP_REPLY_REQUEST_ANOMALY ;

	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// IN (ICMP.Port-unreachable) > lambda * OUT(UDP) (in case of group == ANOMALY_TYPE_DOS)
	// ALL(ICMP.Port-unreachable) > lambda * ALL(UDP) (in case of group == ANOMALY_TYPE_WORM)
	//
	typedef struct _ICMP_PORT_UNREACHABLE_ANOMALY : public PROTOCOL_ANOMALY {
		_ICMP_PORT_UNREACHABLE_ANOMALY (MessageLastAnomalyType::ANOMALY_TYPE group) {
			protocol  = Packet::PROTO_NONE; // get all protocols. we filter on our own
			kind	  = ModuleAnalyzerProtocolAnomaly::ANOMALY_KIND_ICMP_PORT_UNREACHABLE_ANOMALY;
			anomGroup = group;
		}
		bool acceptLeft (Packet* pkt) {
			if (pkt->getProtocol() != Packet::PROTO_ICMP) return false;
			IcmpPacket* icmpPkt = (IcmpPacket*)pkt;
			
			return (icmpPkt->getType() == IcmpPacket::ICMP_TYPE_DEST_UNREACHABLE &&
				icmpPkt->getCode() == IcmpPacket::ICMP_DEST_UNREACHABLE_CODE_PORT_UNREACHABLE);
		}
		bool acceptRight (Packet* pkt) {
			return (pkt->getProtocol() == Packet::PROTO_UDP);
		}
		double getLambda () {
			return 0.50;
		}
	} ICMP_PORT_UNREACHABLE_ANOMALY;

	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// IN(ICMP.erromsg) > lambda * OUT(UDP | TCP) (in case of group == ANOMALY_TYPE_DOS)
	// ALL(ICMP.erromsg) > lambda * ALL(UDP | TCP) (in case of group == ANOMALY_TYPE_WORM)
	//
	typedef struct _ICMP_ERROR_MESSAGE_ANOMALY : public PROTOCOL_ANOMALY {
		_ICMP_ERROR_MESSAGE_ANOMALY (MessageLastAnomalyType::ANOMALY_TYPE group) {
			protocol  = Packet::PROTO_NONE; // get all protocol. filter ourself
			kind	  = ModuleAnalyzerProtocolAnomaly::ANOMALY_KIND_ICMP_ERROR_MESSAGE_ANOMALY;
			anomGroup = group;
		}
		bool acceptLeft (Packet* pkt) {
			if (pkt->getProtocol() != Packet::PROTO_ICMP) return false;
			IcmpPacket* icmpPkt = (IcmpPacket*)pkt;
			unsigned char type = icmpPkt->getType ();

			return (type == IcmpPacket::ICMP_TYPE_DEST_UNREACHABLE	||
					type == IcmpPacket::ICMP_TYPE_TIME_EXCEEDED		||
					type == IcmpPacket::ICMP_TYPE_PARAM_PROBLEM		||
					type == IcmpPacket::ICMP_TYPE_CONVERSION_ERROR	);
		}
		bool acceptRight (Packet* pkt) {
			return (pkt->getProtocol() == Packet::PROTO_TCP	||
					pkt->getProtocol() == Packet::PROTO_UDP	);
		}
		double getLambda () {
			return 1.05;
		}
	} ICMP_ERROR_MESSAGE_ANOMALY;

	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// ALL(ICMP.host_unreachable) > lambda * ALL (UDP | TCP)
	//
	typedef struct _ICMP_HOST_UNREACHABLE_ANOMALY : public PROTOCOL_ANOMALY {
		_ICMP_HOST_UNREACHABLE_ANOMALY () {
			protocol  = Packet::PROTO_NONE; // get all protocol. filter ourself
			kind	  = ModuleAnalyzerProtocolAnomaly::ANOMALY_KIND_ICMP_HOST_UNREACHABLE_ANOMALY;
			anomGroup = MessageLastAnomalyType::ANOMALY_TYPE_WORM;
		}
		bool acceptLeft (Packet* pkt) {
			if (pkt->getProtocol() != Packet::PROTO_ICMP) return false;
			IcmpPacket* icmpPkt = (IcmpPacket*)pkt;
			unsigned char type = icmpPkt->getType ();
			unsigned char code = icmpPkt->getCode ();

			return (type == IcmpPacket::ICMP_TYPE_DEST_UNREACHABLE ||
					code == IcmpPacket::ICMP_DEST_UNREACHABLE_CODE_HOST_UNREACHABLE	);
		}
		bool acceptRight (Packet* pkt) {
			return (pkt->getProtocol() == Packet::PROTO_TCP	||
					pkt->getProtocol() == Packet::PROTO_UDP	);
		}
		double getLambda () {
			return 1.05;
		}
	} ICMP_HOST_UNREACHABLE_ANOMALY;

};

#endif // __MODULE_ANALYZER_PROTOCOL_ANOMALY_H
