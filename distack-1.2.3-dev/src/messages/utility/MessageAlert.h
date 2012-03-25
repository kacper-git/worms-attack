#ifndef __MESSAGE_ALERT_H
#define __MESSAGE_ALERT_H

#include "base/message/Message.h"
#include <boost/serialization/string.hpp>

using std::string;

class MessageAlert : public Message {
public:
	
	typedef enum _ALERT_TYPE {
		ALERT_TYPE_RAISE_LEVEL,
		ALERT_TYPE_LOWER_LEVEL,
	} ALERT_TYPE;

						MessageAlert		();
						MessageAlert		(ALERT_TYPE type, unsigned short stage, string msg);
						~MessageAlert		();

	MESSAGE_TYPE				getType			();

	ALERT_TYPE				getAlertType		();
	string					getAlertMessage		();	
	unsigned short				getAlertModuleStage 	();

private:

	ALERT_TYPE				m_type;
	string					m_message;
	unsigned short				m_stage;
		
	REMOTE_MESSAGING_BEGIN(MessageAlert, remote)
#ifdef REMOTE_XML
		remote & boost::serialization::make_nvp("Alerttyp", m_type);
		remote & boost::serialization::make_nvp("Warnung", m_message);
		remote & boost::serialization::make_nvp("Stufe", m_stage);
#else
		remote & m_type;
		remote & m_message;
		remote & m_stage;
#endif //REMOTE_XML
	REMOTE_MESSAGING_END

};

#endif // __MESSAGE_ALERT_H
