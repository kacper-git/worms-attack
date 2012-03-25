#include "MessageTimer.h"

MessageTimer::MessageTimer ()
{
}

MessageTimer::~MessageTimer ()
{
}

Message::MESSAGE_TYPE MessageTimer::getType ()
{
	return Message::MESSAGE_TYPE_TIMER;
}

void MessageTimer::setName (string name)
{
	m_timerName = name;
}

string MessageTimer::getName ()
{
	return m_timerName;
}

void MessageTimer::setEventNo (unsigned long no)
{
	m_eventNo = no;
}

unsigned long MessageTimer::getEventNo ()
{
	return m_eventNo;
}
