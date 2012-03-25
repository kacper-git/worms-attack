#include "MessageAlert.h"

MessageAlert::MessageAlert ()
{
	m_type		= ALERT_TYPE_RAISE_LEVEL;
	m_message	= "Default alert message without details";
	m_stage		= 0;
}

MessageAlert::MessageAlert (ALERT_TYPE type, unsigned short stage, string msg)
:	m_type		(type),
	m_message	(msg),
	m_stage		(stage)
{
}

Message::MESSAGE_TYPE MessageAlert::getType ()
{
	return Message::MESSAGE_TYPE_ALERT;
}

MessageAlert::~MessageAlert ()
{
}

MessageAlert::ALERT_TYPE MessageAlert::getAlertType ()
{
	return m_type;
}

string MessageAlert::getAlertMessage ()
{
	return m_message;
}

unsigned short MessageAlert::getAlertModuleStage ()
{
	return m_stage;
}
