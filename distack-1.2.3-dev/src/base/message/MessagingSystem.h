#ifndef __MESSAGING_SYSTEM_H
#define __MESSAGING_SYSTEM_H

#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include <fstream>
#include "base/common/Helper.h"
#include "base/common/Log.h"
#include "base/message/MessagingNode.h"
#include "base/message/Message.h"
#include "base/message/remote/RemoteMessagingSystem.h"
#include "base/common/Timer.h"
#include <boost/thread/mutex.hpp>
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>

using std::map;
using std::find;
using std::queue;
using std::vector;
using std::pair;
using std::ofstream;

class MessagingSystem {
	friend class RemoteMessagingSystem;
public:
	MessagingSystem( DistackInfo* info );
	~MessagingSystem();

	void subscribe( MessagingNode* node, Message::MESSAGE_TYPE type );
	void unsubscribe( MessagingNode* node, Message::MESSAGE_TYPE type );
	void unsubscribeAll( MessagingNode* node );
	void sendMessage( Message* msg, MessagingNode::SEND_OPTIONS options );
	void flush();
	RemoteMessagingSystem* getRemoteSystem();

private:
	DistackInfo* distackInfo;

	typedef vector<MessagingNode*> MESSAGING_NODES;
	typedef MESSAGING_NODES::iterator MESSAGING_NODES_ITERATOR;
	typedef pair<Message::MESSAGE_TYPE, MESSAGING_NODES> MESSAGING_PAIR;
	typedef map<Message::MESSAGE_TYPE, MESSAGING_NODES> MESSAGING_TABLE;
	typedef MESSAGING_TABLE::iterator MESSAGING_TABLE_ITERATOR;

	MESSAGING_TABLE m_messagingTable;
	boost::mutex m_messagingTableMutex;

	bool m_threadRunning;
	static void distributionThreadFunc( MessagingSystem* obj );
	boost::thread* m_distributionThread;

	typedef pair<Message*, MessagingNode::SEND_OPTIONS> MESSAGE_OPTIONS_PAIR;
	typedef queue<MESSAGE_OPTIONS_PAIR> MESSAGE_QUEUE;
	MESSAGE_QUEUE m_queue;
	boost::mutex m_queueMutex;

	RemoteMessagingSystem* m_remoteMessaging;
};

#endif // __MESSAGING_SYSTEM_H
