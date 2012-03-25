#ifndef __MESSAGE_LAST_SUSPICIOUS_AGGREGATE_H
#define __MESSAGE_LAST_SUSPICIOUS_AGGREGATE_H

#include "base/message/Message.h"
#include "base/protocol/Packet.h"
#include <boost/serialization/string.hpp>

using std::string;

class MessageLastSuspiciousAggregate : public Message {
public:
				MessageLastSuspiciousAggregate		();
				MessageLastSuspiciousAggregate		(bool suspiciousAggregateExists, Packet::PROTOCOL protocol = Packet::PROTO_NONE, string description = "");
				~MessageLastSuspiciousAggregate		();

	MESSAGE_TYPE		getType					();

	bool			suspiciousAggregateExists		();
	Packet::PROTOCOL	getProtocol				();
	string			getDescription				();

private:

	bool			m_suspiciousAggregateExists;
	Packet::PROTOCOL	m_protocol;
	string			m_description;

	REMOTE_MESSAGING_BEGIN(MessageLastSuspiciousAggregate, remote)
#ifdef REMOTE_XML
		remote & boost::serialization::make_nvp("Existenz_verdaechtiges_Aggregat", m_suspiciousAggregateExists);
		remote & boost::serialization::make_nvp("Protokoll", m_protocol);
		remote & boost::serialization::make_nvp("Beschreibung", m_description);
#else
		remote & m_suspiciousAggregateExists;
		remote & m_protocol;
		remote & m_description;
#endif //REMOTE_XML
	REMOTE_MESSAGING_END

};

#endif // __MESSAGE_LAST_SUSPICIOUS_AGGREGATE_H
