#include "MessageAggregateWatchValues.h"

MessageAggregateWatchValues::MessageAggregateWatchValues ()
{
}

MessageAggregateWatchValues::~MessageAggregateWatchValues ()
{
}

Message::MESSAGE_TYPE MessageAggregateWatchValues::getType ()
{
	return Message::MESSAGE_TYPE_AGGREGATE_WATCH_VALUES;
}

MessageAggregateWatchValues::AGGREGATE_INFOS MessageAggregateWatchValues::getAggregateInfo ()
{
	return m_items;
}

void MessageAggregateWatchValues::add (AGGREGATE_INFO info)
{
	m_items.push_back (info);
}
