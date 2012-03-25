#include "ModuleUtilityTimer.h"

MODULE_INTERFACE(ModuleUtilityTimer);

const string ModuleUtilityTimer::PARAM_Interval = "Interval";

ModuleUtilityTimer::ModuleUtilityTimer ()
{
	m_eventNo = 0;
}

ModuleUtilityTimer::~ModuleUtilityTimer	()
{
	Timer::stop ();
}

void ModuleUtilityTimer::registerMessages ()
{
	Timer::start ("UtilityTimer");
}

bool ModuleUtilityTimer::configure (ModuleConfiguration& configList)
{
	bool good = true;
	good &= configList.has (PARAM_Interval);
	
	m_timerName = configList.name;

	if (good) {
		m_param_Interval = configList.getLong (PARAM_Interval);
		Timer::setInterval	(m_param_Interval);
	}

	return good;
}

void ModuleUtilityTimer::eventFunction ()
{
	MessageTimer* msg = new MessageTimer ();
	
	msg->setName	(m_timerName);
	msg->setEventNo	(m_eventNo++);

	//MessagingNode::SEND_OPTIONS options = MessagingNode::SEND_OPTIONS::createRemote (MessagingNode::REMOTE_DESTINATIONS_NEIGHBOURS);
	//MessagingNode::sendMessage (msg, options);
	MessagingNode::sendMessage (msg);
}
