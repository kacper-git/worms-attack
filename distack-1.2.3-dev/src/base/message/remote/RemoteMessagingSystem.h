#ifndef __REMOTE_MESSAGING_SYSTEM_H
#define __REMOTE_MESSAGING_SYSTEM_H

#include "base/common/Log.h"
#include "base/message/MessagingNode.h"
#include "base/message/remote/RemoteCommSystem.h"
#include "base/message/remote/RemoteCommSystemNone.h"

#ifdef OMNET_SIMULATION
  #include "base/message/remote/RemoteCommSystemOmnetTcp.h"
  #include "base/message/remote/RemoteCommSystemOmnetPathbased.h"
  #include "base/message/remote/RemoteCommSystemOmnetRing.h"
#else
  #include "base/message/remote/RemoteCommSystemTcpSocket.h"
  #include "base/message/remote/RemoteCommSystemGist.h"
#endif //OMNET_SIMULATION

#include "base/message/Message.h"
#include "messages/attackdetection/MessageAddressDistribution.h"
#include "messages/attackdetection/MessageAggregateIntervalValues.h"
#include "messages/attackdetection/MessageAggregateWatchValues.h"
#include "messages/attackdetection/MessageLastAnomalyType.h"
#include "messages/attackdetection/MessageLastSuspiciousAggregate.h"
#include "messages/utility/MessageTimer.h"
#include "messages/utility/MessageAlert.h"

#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/utility.hpp> 
#include <boost/serialization/serialization.hpp> 
#include <boost/serialization/tracking.hpp>	
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/factory.hpp>
#ifdef REMOTE_XML
  #include <boost/archive/xml_iarchive.hpp>
  #include <boost/archive/xml_oarchive.hpp>
#endif //REMOTE_XML

#include <string>
#include <sstream>
#include <ios>

using std::ios_base;
using std::string;
using std::stringstream;
using std::istringstream;
using std::ostringstream;
using std::stringbuf;
using std::ostream;

BOOST_CLASS_TRACKING(Message, boost::serialization::track_never)

//
// here is the macro to add a message class for remote messaging
// see the RemoteMessagingSystem.cpp file at top. this is where
// to include your message classes
//

#define	REMOTE_MESSAGING_REGISTER(x)	BOOST_CLASS_EXPORT(x); \
					BOOST_CLASS_TRACKING(x, boost::serialization::track_never);

class MessagingSystem; // forward decl

class RemoteMessagingSystem {

	friend class RemoteCommSystem;

public:
	RemoteMessagingSystem( MessagingSystem* system, DistackInfo* info );
	~RemoteMessagingSystem();

	void sendMessage( Message* msg, MessagingNode::SEND_OPTIONS options );
	RemoteCommSystem* getCommSystem();

protected:

	void reveiveMessage( Message* msg );
	void receiveBytes( DISTACK_REMOTE_DATA data );

private:

	MessagingSystem* m_messagingSystem;
	RemoteCommSystem* m_commSystem;
	DistackInfo* distackInfo;

	string serialize( Message* msg );
	Message* deserialize( string data );

	//string compressString( string data );
	//string decompressString( string data );
};

#endif // __REMOTE_MESSAGING_SYSTEM_H
