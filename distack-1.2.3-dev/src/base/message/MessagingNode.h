#ifndef __MESSAGING_NODE_H
#define __MESSAGING_NODE_H

#include <queue>
#include <list>
#include <iostream>
#include <boost/signal.hpp>
#include "base/message/Message.h"
#include "base/protocol/IpPacket.h"

using std::list;
using std::queue;
using std::cout;

/** @class MessagingNode
  * 
  */
class MessagingNode {
public:
						MessagingNode			()
	{
	}
	
	virtual 			~MessagingNode			()
	{
	}

	typedef enum _SEND_SYNC_MODE {
		SEND_SYNC_MODE_ASYNC,
		SEND_SYNC_MODE_SYNC,
	} SEND_SYNC_MODE;

	typedef enum _SEND_REMOTE_MODE {
		SEND_REMOTE_MODE_LOCAL	= 0x1,
		SEND_REMOTE_MODE_REMOTE = 0x2,
		SEND_REMOTE_MODE_BOTH   = 0x3,
	} SEND_REMOTE_MODE;

	typedef enum _REMOTE_DESTINATIONS {
		REMOTE_DESTINATIONS_NONE,
		REMOTE_DESTINATIONS_LIST,
		REMOTE_DESTINATIONS_NEIGHBOURS,
	} REMOTE_DESTINATIONS;

	typedef list<IP_ADDR>			IP_ADDR_LIST;
	typedef IP_ADDR_LIST::iterator	IP_ADDR_LIST_ITERATOR;

	typedef struct _SEND_OPTIONS {
		SEND_SYNC_MODE		syncMode;
		SEND_REMOTE_MODE	remoteMode;
		REMOTE_DESTINATIONS	remoteDest;
		IP_ADDR_LIST		remoteList;

		_SEND_OPTIONS () {
			syncMode	= SEND_SYNC_MODE_SYNC;
			remoteMode	= SEND_REMOTE_MODE_LOCAL;
			remoteDest	= REMOTE_DESTINATIONS_NONE;
			remoteList.clear ();
		}

		static struct _SEND_OPTIONS createLocalSync () {
			struct _SEND_OPTIONS ret;
			
			ret.syncMode	= SEND_SYNC_MODE_SYNC;
			ret.remoteMode	= SEND_REMOTE_MODE_LOCAL;
			ret.remoteDest	= REMOTE_DESTINATIONS_NONE;
			ret.remoteList.clear ();

			return ret;
		}

		static struct _SEND_OPTIONS createLocalAsync () {
			struct _SEND_OPTIONS ret;
			
			ret.syncMode	= SEND_SYNC_MODE_ASYNC;
			ret.remoteMode	= SEND_REMOTE_MODE_LOCAL;
			ret.remoteDest	= REMOTE_DESTINATIONS_NONE;
			ret.remoteList.clear ();

			return ret;
		}

		static struct _SEND_OPTIONS createRemote (REMOTE_DESTINATIONS mode, IP_ADDR_LIST dest=IP_ADDR_LIST()) {
			struct _SEND_OPTIONS ret;
			
			ret.syncMode	= SEND_SYNC_MODE_ASYNC;
			ret.remoteMode	= SEND_REMOTE_MODE_REMOTE;
			ret.remoteDest	= mode;
			ret.remoteList	= dest;

			return ret;
		}

		static struct _SEND_OPTIONS createBothAsync (REMOTE_DESTINATIONS mode, IP_ADDR_LIST dest=IP_ADDR_LIST()) {
			struct _SEND_OPTIONS ret;
			
			ret.syncMode	= SEND_SYNC_MODE_ASYNC;
			ret.remoteMode	= SEND_REMOTE_MODE_BOTH;
			ret.remoteDest	= mode;
			ret.remoteList	= dest;

			return ret;
		}

	} SEND_OPTIONS;

	typedef boost::signal<void(Message*, SEND_OPTIONS)>					MESSAGE_SEND_FUNC;
	typedef boost::signal<void(MessagingNode*, Message::MESSAGE_TYPE)>	MESSAGE_SUBSCRIBE_FUNC;
	typedef boost::signal<void(MessagingNode*, Message::MESSAGE_TYPE)>	MESSAGE_UNSUBSCRIBE_FUNC;
	typedef boost::signal<void(MessagingNode*)>							MESSAGE_UNSUBSCRIBEALL_FUNC;
	
	void				configure				(MESSAGE_SEND_FUNC::slot_function_type			 sendFunc			, 
												 MESSAGE_SUBSCRIBE_FUNC::slot_function_type		 subscribeFunc		, 
												 MESSAGE_SUBSCRIBE_FUNC::slot_function_type		 unsubscribeFunc	,
												 MESSAGE_UNSUBSCRIBEALL_FUNC::slot_function_type unsubscribeAllFunc	)
	{
		m_conSendFunc	   = m_sendFunction.connect			  (sendFunc);
		m_conSubscFunc	   = m_subscribeFunction.connect	  (subscribeFunc);
		m_conUnsubFunc	   = m_unsubscribeFunction.connect	  (unsubscribeFunc);
		m_conUnsubAllFunc  = m_unsubscribeAllFunction.connect (unsubscribeAllFunc);

		assert (m_conSendFunc.connected	  ());
		assert (m_conSubscFunc.connected	  ());
		assert (m_conUnsubFunc.connected	  ());
		assert (m_conUnsubAllFunc.connected());
	}

	virtual void		receiveMessage			(Message* msg)
	{
	}

	virtual void		registerMessages		()
	{
	}

protected:

	void				sendMessage				(Message* msg)
	{
		sendMessage (msg, MessagingNode::SEND_OPTIONS::createLocalAsync());
	}

	void				sendMessage				(Message* msg, SEND_OPTIONS options)
	{
		assert (m_conSendFunc.connected ());
		m_sendFunction (msg, options);
	}

	void				subscribeMessage		(Message::MESSAGE_TYPE type)
	{
		assert (m_conSubscFunc.connected ());
		m_subscribeFunction (this, type);
	}

	void				unsubscribeMessage		(Message::MESSAGE_TYPE type)
	{
		assert (m_conUnsubFunc.connected ());
		m_unsubscribeFunction (this, type);
	}

	void				unsubscribeAllMessages	()
	{
		assert (m_conUnsubAllFunc.connected());
		m_unsubscribeAllFunction (this);
	}

private:

	MESSAGE_SEND_FUNC				m_sendFunction;
	MESSAGE_SUBSCRIBE_FUNC			m_subscribeFunction;
	MESSAGE_UNSUBSCRIBE_FUNC		m_unsubscribeFunction;
	MESSAGE_UNSUBSCRIBEALL_FUNC		m_unsubscribeAllFunction;

	boost::signals::connection		m_conSendFunc;	 
	boost::signals::connection		m_conSubscFunc;	 
	boost::signals::connection		m_conUnsubFunc;	 
	boost::signals::connection		m_conUnsubAllFunc;

};

#endif // __MESSAGING_NODE_H
