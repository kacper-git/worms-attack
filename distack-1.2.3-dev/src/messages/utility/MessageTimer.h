#ifndef __MESSAGE_TIMER_H
#define __MESSAGE_TIMER_H

#include "base/message/Message.h"
#include <boost/serialization/string.hpp>

using std::string;

class MessageTimer : public Message {
public:
				MessageTimer			();
				~MessageTimer			();
	
	void			setName				(string name);
	string			getName				();

	void			setEventNo			(unsigned long no);
	unsigned long		getEventNo			();
	MESSAGE_TYPE		getType				();

private:

	string			m_timerName;
	unsigned long		m_eventNo;

	REMOTE_MESSAGING_BEGIN(MessageTimer, remote)
#ifdef REMOTE_XML
		remote & boost::serialization::make_nvp("Timer_Name", m_timerName);
		remote & boost::serialization::make_nvp("Ereignis_Nr", m_eventNo);
#else
		remote & m_timerName;
		remote & m_eventNo;
#endif //REMOTE_XML
	REMOTE_MESSAGING_END

};

#endif // __MESSAGE_TIMER_H
