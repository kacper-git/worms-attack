#ifndef __MESSAGE_PROTOCOL_DISTRIBUTION_H
#define __MESSAGE_PROTOCOL_DISTRIBUTION_H

#include "base/message/Message.h"
#include "base/protocol/Packet.h"
#include <string>

#pragma warning (disable : 4267)
	#include <boost/serialization/vector.hpp>
	#include <boost/serialization/string.hpp>
#pragma warning (default : 4267)

using std::string;
using std::vector;

class MessageAggregateWatchValues : public Message {
public:
					MessageAggregateWatchValues	();
					~MessageAggregateWatchValues	();

	MESSAGE_TYPE			getType				();

	typedef struct _AGGREGATE_INFO {
		string			description;
		Packet::PROTOCOL	protocol;
		unsigned long		count;
		double			average;
		double			deviation;
		double			threshold;

		REMOTE_MESSAGING_BEGIN_BASE(remote)
#ifdef REMOTE_XML
			remote & boost::serialization::make_nvp("Beschreibung", description);
			remote & boost::serialization::make_nvp("Protokoll", protocol);
			remote & boost::serialization::make_nvp("Anzahl_Pakete", count);
			remote & boost::serialization::make_nvp("Durchschnitt", average);
			remote & boost::serialization::make_nvp("Abweichung", deviation);
			remote & boost::serialization::make_nvp("Schwellenwert", threshold);
#else
			remote & description;
			remote & protocol;
			remote & count;
			remote & average;
			remote & deviation;
			remote & threshold;
#endif //REMOTE_XML
		REMOTE_MESSAGING_END

	} AGGREGATE_INFO;
	
	typedef vector<AGGREGATE_INFO>		AGGREGATE_INFOS;
	typedef AGGREGATE_INFOS::iterator	AGGREGATE_INFOS_ITERATOR;

	AGGREGATE_INFOS				getAggregateInfo 	();

	void					add			(AGGREGATE_INFO info);
	
private:

	AGGREGATE_INFOS				m_items; 

	REMOTE_MESSAGING_BEGIN(MessageAggregateWatchValues, remote)
#ifdef REMOTE_XML
	    remote & boost::serialization::make_nvp("Watch_Values",m_items);
#else
	    remote & m_items;
#endif //REMOTE_XML
	REMOTE_MESSAGING_END

};

#endif // __MESSAGE_PROTOCOL_DISTRIBUTION_H
