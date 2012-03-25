#include "MessagingSystem.h"

MessagingSystem::MessagingSystem (DistackInfo* info) 
: m_threadRunning(false)
{
	distackInfo = info;
	m_remoteMessaging = new RemoteMessagingSystem (this, distackInfo);

#ifndef OMNET_SIMULATION
	m_threadRunning = true;
	m_distributionThread = new boost::thread (boost::bind (&MessagingSystem::distributionThreadFunc, this));
#endif
}

MessagingSystem::~MessagingSystem ()
{
#ifndef OMNET_SIMULATION
	m_threadRunning = false;
	m_distributionThread->join ();

	delete m_distributionThread;
	m_distributionThread = NULL;
#endif

	delete m_remoteMessaging;
}

void MessagingSystem::distributionThreadFunc (MessagingSystem* obj)
{
	while (obj->m_threadRunning) {

		{
			//
			// check if we have any messages to distribute
			// if not, sleep some time (TODO: should be done using signals)
			//

			bool empty = true;

			{
				//
				// check for items in the queue and immediately release the mutex
				// so that we do not sleep with the mutex owned!
				//

				boost::mutex::scoped_lock scopedLock (obj->m_queueMutex);
				empty = obj->m_queue.empty ();
			}

			if (empty) {
				Helper::sleep (50); // TODO: // TODO:  use boost::condition.
				continue;
			}
		}

		{
			//
			// get the next message out of the queue
			//

			MESSAGE_OPTIONS_PAIR msgpair;
			msgpair.first = NULL;

			{
				boost::mutex::scoped_lock scopedLock (obj->m_queueMutex);
				msgpair = obj->m_queue.front ();
				obj->m_queue.pop ();
			}

			//
			// send the message out syncronously (from the thread view)
			//

			msgpair.second.syncMode = MessagingNode::SEND_SYNC_MODE_SYNC;
			obj->sendMessage (msgpair.first, msgpair.second);
		}
	}
}

void MessagingSystem::sendMessage (Message* msg, MessagingNode::SEND_OPTIONS options)
{
	if (msg == NULL) return;

	
	assert (options.syncMode == MessagingNode::SEND_SYNC_MODE_ASYNC	|| 
			options.syncMode == MessagingNode::SEND_SYNC_MODE_SYNC	);

	assert (options.remoteMode == MessagingNode::SEND_REMOTE_MODE_LOCAL  ||
			options.remoteMode == MessagingNode::SEND_REMOTE_MODE_REMOTE ||
			options.remoteMode == MessagingNode::SEND_REMOTE_MODE_BOTH	 );

	//
	// asyncronous message sending
	//

	if (options.syncMode == MessagingNode::SEND_SYNC_MODE_ASYNC) {

		//
		// put the message into the message queue
		// TODO: work with boost::condition and signal that the queue is non empty now
		//

		boost::mutex::scoped_lock scopedLock (m_queueMutex);
		m_queue.push (MESSAGE_OPTIONS_PAIR(msg, options));

		return;
	} // if (sendType == MessagingSystem::SEND_SYNC_MODE_ASYNC)

	//
	// if we end up here, the message has to be sent synchronously
	// so we send it out locally and remotely
	//

	//
	// syncronous message sending
	//

	if ((options.remoteMode & MessagingNode::SEND_REMOTE_MODE_LOCAL) == MessagingNode::SEND_REMOTE_MODE_LOCAL) {
		
		//
		// local message sending
		//		

		if (options.syncMode == MessagingNode::SEND_SYNC_MODE_SYNC) {

			//
			// send the message directly to the subscribers
			//
			// find the nodes that have subscribed to the message
			//

			typedef vector<MessagingNode*> NODE_LIST;
			NODE_LIST deliveryNodes;
		
			{
			boost::mutex::scoped_lock scopedLock (m_messagingTableMutex);	
			MESSAGING_TABLE_ITERATOR it = m_messagingTable.find (msg->getType());
			
			if (it != m_messagingTable.end()) {
			
				//
				// send the message to the subscribed nodes
				//

				MESSAGING_NODES_ITERATOR nodesBegin	= it->second.begin  ();
				MESSAGING_NODES_ITERATOR nodesEnd	= it->second.end	();

				for ( ; nodesBegin != nodesEnd; nodesBegin++) {
					MessagingNode* node = *nodesBegin;
						deliveryNodes.push_back (node);
				}

			} // if (it != m_messagingTable.end())
			}

			NODE_LIST::iterator ideliver = deliveryNodes.begin();
			NODE_LIST::iterator ienddeliver = deliveryNodes.end();
			
			for ( ; ideliver != ienddeliver; ideliver++)
				(*ideliver)->receiveMessage (msg);	

		} // if (sendType == MessagingSystem::SEND_SYNC_MODE_SYNC)

	} // if ((remoteMode & MessagingNode::SEND_REMOTE_MODE_LOCAL) == MessagingNode::SEND_REMOTE_MODE_LOCAL)

	//
	// remote message sending
	//

	if ((options.remoteMode & MessagingNode::SEND_REMOTE_MODE_REMOTE) == MessagingNode::SEND_REMOTE_MODE_REMOTE) {
		if (options.syncMode == MessagingNode::SEND_SYNC_MODE_SYNC)
			Log::warning (distackInfo, "cannot send message with SEND_SYNC_MODE_SYNC to remote host. remote sending is done with SEND_SYNC_MODE_ASYNC");
		
		m_remoteMessaging->sendMessage (msg, options);

	} // if ((remoteMode & MessagingNode::SEND_REMOTE_MODE_REMOTE) == MessagingNode::SEND_REMOTE_MODE_REMOTE)

	//
	// we are responsible for the deletion of the message
	// the sender creates it and we delete it
	//

	delete msg;
}

void MessagingSystem::subscribe (MessagingNode* node, Message::MESSAGE_TYPE type)
{
	if (node == NULL) return;

	//
	// is the subscribed message valid?
	//

	if (! (type > Message::MESSAGE_TYPE_INVALID_FIRST && type < Message::MESSAGE_TYPE_INVALID_LAST)) {
		logging_warn( "can not subscribe the node "			+
						Helper::ptos<MessagingNode*> (node)		+
						" because the message type is invalid"	);
		return;
	}

	boost::mutex::scoped_lock scopedLock (m_messagingTableMutex);

	//
	// check if there are already some nodes registered to the message type at all
	// if so, we use the found nodes' vector
	//

	MESSAGING_TABLE_ITERATOR	it = m_messagingTable.find (type);
	MESSAGING_NODES				nodes;

	if (it != m_messagingTable.end()) {
		nodes = it->second;
		m_messagingTable.erase (it);
	}
	
	//
	// is the given node already registered? if no, register it
	//

	MESSAGING_NODES_ITERATOR i = find (nodes.begin(), nodes.end(), node);

	if (i == nodes.end()) {
	
		nodes.push_back (node);

	}else {
	
		logging_warn( "the node "										+ 
						Helper::ptos<MessagingNode*>(node)				+ 
						" is already subscribed to the message-type "	+ 
						Helper::ultos(type)								);
	}

	m_messagingTable.insert (MESSAGING_PAIR (type, nodes));
}

void MessagingSystem::unsubscribe (MessagingNode* node, Message::MESSAGE_TYPE type)
{
	if (node == NULL) return;

	boost::mutex::scoped_lock scopedLock (m_messagingTableMutex);
	MESSAGING_TABLE_ITERATOR it = m_messagingTable.find (type);
	
	string errMsg = "can not unsubscribe the node "			+ 
					Helper::ptos<MessagingNode*>(node)		+ 
					" from the message-type "				+ 
					Helper::ultos(type)						+ 
					" because it has not subscribed to it"	;

	//
	// if subscription list for this message type is empty, return with error
	//

	if (it == m_messagingTable.end()) {
		logging_warn( errMsg);
		return;
	} 

	//
	// find the node in the registered nodes
	//

	MESSAGING_NODES_ITERATOR foundNode = find (it->second.begin(), it->second.end(), node);
	if (foundNode == it->second.end()) {
		logging_warn( errMsg);
		return;
	}

	//
	// finally erase the node
	//

	it->second.erase (foundNode);
}

void MessagingSystem::unsubscribeAll (MessagingNode* node)
{
	if (node == NULL) return;

	boost::mutex::scoped_lock scopedLock (m_messagingTableMutex);

	MESSAGING_TABLE_ITERATOR i	  = m_messagingTable.begin  ();
	MESSAGING_TABLE_ITERATOR iend = m_messagingTable.end	();

	for ( ; i != iend; i++) {
		
		MESSAGING_NODES_ITERATOR item = find (i->second.begin(), i->second.end(), node);
		if (item != i->second.end())
			i->second.erase (item);
		
	} // for ( ; i != iend; i++)
}

void MessagingSystem::flush ()
{
	while (true) {

		{
			//
			// check if we have any messages to distribute
			//

			bool empty = true;

			{
				//
				// check for items in the queue and immediately release the mutex
				//

				boost::mutex::scoped_lock scopedLock (m_queueMutex);
				empty = m_queue.empty ();
			}

			//
			// if the queue is empty, we are done flushing
			//

			if (empty) break;
		}

		{
			//
			// get the next message out of the queue
			//

			MESSAGE_OPTIONS_PAIR msgpair;
			msgpair.first = NULL;

			{
				boost::mutex::scoped_lock scopedLock (m_queueMutex);
				msgpair	= m_queue.front ();
				m_queue.pop ();
			}

			//
			// send the message out syncronously (from the thread view)
			//

			msgpair.second.syncMode = MessagingNode::SEND_SYNC_MODE_SYNC;
			sendMessage (msgpair.first, msgpair.second);
		}
	
	} // while (true) {
}

RemoteMessagingSystem* MessagingSystem::getRemoteSystem ()
{
	return m_remoteMessaging;
}
