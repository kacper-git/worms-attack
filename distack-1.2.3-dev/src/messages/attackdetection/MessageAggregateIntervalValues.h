#ifndef __MESSAGE_AGGREGATE_INTERVAL_VALUES_H
#define __MESSAGE_AGGREGATE_INTERVAL_VALUES_H

#include "base/protocol/Packet.h"
#include "base/message/Message.h"


#pragma warning (disable : 4267)
	#include <boost/serialization/vector.hpp>
	#include <boost/serialization/string.hpp>
	#include <boost/serialization/utility.hpp>
#pragma warning (default : 4267)

using std::string;
using std::pair;
using std::vector;

class MessageAggregateIntervalValues : public Message {
public:
					MessageAggregateIntervalValues		();
					~MessageAggregateIntervalValues		();
	
	MESSAGE_TYPE		getType						();

	typedef pair<unsigned int, double>	COUNT_THRESHOLD_PAIR;
	typedef vector<COUNT_THRESHOLD_PAIR>	INTERVAL_ITEMS;
	typedef INTERVAL_ITEMS::iterator	INTERVAL_ITEMS_ITERATOR;

	INTERVAL_ITEMS			getIntervals		();
	Packet::PROTOCOL		getProtocol		();
	string				getDescription		();

	void				addInterval		(COUNT_THRESHOLD_PAIR values);
	void				setProtocol		(Packet::PROTOCOL);
	void				setDescription		(string description);

private:

	INTERVAL_ITEMS						m_intervals;

	//
	// aggregate identifiers
	//

	Packet::PROTOCOL					m_protocol;
	string							m_description;

	REMOTE_MESSAGING_BEGIN(MessageAggregateIntervalValues, remote)
#ifdef REMOTE_XML
		remote & boost::serialization::make_nvp("Intervall", m_intervals);
		remote & boost::serialization::make_nvp("Protokoll", m_protocol);
		remote & boost::serialization::make_nvp("Beschreibung", m_description);
#else
		remote & m_intervals;
		remote & m_protocol;
		remote & m_description;
#endif //REMOTE_XML
	REMOTE_MESSAGING_END

};

#endif // __MESSAGE_AGGREGATE_INTERVAL_VALUES_H
