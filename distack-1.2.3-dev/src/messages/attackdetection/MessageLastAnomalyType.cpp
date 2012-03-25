#include "MessageLastAnomalyType.h"

MessageLastAnomalyType::MessageLastAnomalyType ()
:	m_anomalyType (ANOMALY_TYPE_UNKNOWN)
{
}

MessageLastAnomalyType::MessageLastAnomalyType (ANOMALY_TYPE anomalyType)
:	m_anomalyType (anomalyType)
{
}

MessageLastAnomalyType::~MessageLastAnomalyType ()
{
}

MessageLastAnomalyType::ANOMALY_TYPE MessageLastAnomalyType::getAnomalyType ()
{
	return m_anomalyType;
}

Message::MESSAGE_TYPE MessageLastAnomalyType::getType ()
{
	return Message::MESSAGE_TYPE_ANOMALY_TYPE;
}
