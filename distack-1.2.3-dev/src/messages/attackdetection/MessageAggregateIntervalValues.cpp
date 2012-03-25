#include "MessageAggregateIntervalValues.h"

MessageAggregateIntervalValues::MessageAggregateIntervalValues ()
{
}

MessageAggregateIntervalValues::~MessageAggregateIntervalValues ()
{
}

Message::MESSAGE_TYPE MessageAggregateIntervalValues::getType ()
{
	return Message::MESSAGE_TYPE_AGGREGATE_INTERVAL_VALUES;
}

MessageAggregateIntervalValues::INTERVAL_ITEMS MessageAggregateIntervalValues::getIntervals ()
{
	return m_intervals;
}

Packet::PROTOCOL MessageAggregateIntervalValues::getProtocol ()
{
	return m_protocol;
}

string MessageAggregateIntervalValues::getDescription ()
{
	return m_description;
}

void MessageAggregateIntervalValues::addInterval (COUNT_THRESHOLD_PAIR values)
{
	m_intervals.push_back (values);
}

void MessageAggregateIntervalValues::setProtocol (Packet::PROTOCOL protocol)
{
	m_protocol = protocol;
}

void MessageAggregateIntervalValues::setDescription (string description)
{
	m_description = description;
}
