#include "MessageLastSuspiciousAggregate.h"

MessageLastSuspiciousAggregate::MessageLastSuspiciousAggregate ()
{
}


MessageLastSuspiciousAggregate::MessageLastSuspiciousAggregate (bool suspiciousAggregateExists, Packet::PROTOCOL protocol, string description) {
	m_suspiciousAggregateExists = suspiciousAggregateExists;
	if (m_suspiciousAggregateExists == true) {
		m_protocol = protocol;
		m_description = description;
	} else {
		m_protocol = Packet::PROTO_NONE;
		m_description = "";
	}
}

MessageLastSuspiciousAggregate::~MessageLastSuspiciousAggregate ()
{
}

Message::MESSAGE_TYPE MessageLastSuspiciousAggregate::getType ()
{
	return Message::MESSAGE_TYPE_AGGREGATE_LAST_SUSPICIOUS;
}

bool MessageLastSuspiciousAggregate::suspiciousAggregateExists () {
	return m_suspiciousAggregateExists;
}

Packet::PROTOCOL MessageLastSuspiciousAggregate::getProtocol () {
	return m_protocol;
}

string MessageLastSuspiciousAggregate::getDescription () {
	return m_description;
}
