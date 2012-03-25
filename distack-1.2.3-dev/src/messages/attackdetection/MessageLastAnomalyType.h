#ifndef __MESSAGE_LAST_ANOMALY_TYPE_H
#define __MESSAGE_LAST_ANOMALY_TYPE_H

#include "base/message/Message.h"

class MessageLastAnomalyType : public Message {
public:

	typedef enum _ANOMALY_TYPE {
		ANOMALY_TYPE_UNKNOWN	= 0x0,
		ANOMALY_TYPE_DOS		= 0x1,
		ANOMALY_TYPE_WORM		= 0x2,
		ANOMALY_TYPE_ALL		= 0x3,
	} ANOMALY_TYPE;

					MessageLastAnomalyType		();
					MessageLastAnomalyType		(ANOMALY_TYPE anomalyType);
					~MessageLastAnomalyType		();

	MESSAGE_TYPE			getType				();

	ANOMALY_TYPE			getAnomalyType			();

private:

	ANOMALY_TYPE			m_anomalyType;

	REMOTE_MESSAGING_BEGIN(MessageLastAnomalyType, remote)
#ifdef REMOTE_XML
		remote & boost::serialization::make_nvp("Anomalie_Typ", m_anomalyType);
#else
		remote & m_anomalyType;
#endif //REMOTE_XML
	REMOTE_MESSAGING_END

};

#endif // __MESSAGE_LAST_ANOMALY_TYPE_H
