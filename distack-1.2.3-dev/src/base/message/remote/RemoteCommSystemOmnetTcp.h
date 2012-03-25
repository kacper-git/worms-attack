#ifndef __REMOTE_COMM_SYSTEM_OMNET_TCP_H
#define __REMOTE_COMM_SYSTEM_OMNET_TCP_H

#include "base/message/remote/RemoteCommSystem.h"
#include "base/common/Helper.h"
#include "base/protocol/IpPacket.h"
#include "base/common/Log.h"
#include "base/configuration/Configuration.h"
#include <DistackRemoteTCPPayload_m.h>
#include <TCPSegment.h>
#include <IPDatagram.h>
#include <RoutingTable.h>
#include <cstring>
#include <TCPSocket.h>
#include <DistackTCPSocketMap.h>

class RemoteCommSystemOmnetTcp : public RemoteCommSystem, public TCPSocket::CallbackInterface {
public:
	RemoteCommSystemOmnetTcp	(DistackInfo* info);
	~RemoteCommSystemOmnetTcp	();

	bool				write( DISTACK_REMOTE_DATA data, MessagingNode::SEND_OPTIONS options );
	void				handleMessage( cPacket* msg );
	void				init( int stage );

	virtual void			socketDataArrived( int connId, void* yourPtr, cPacket* msg, bool urgent );
	virtual void			socketFailure( int connId, void* yourPtr, int code );
	virtual void			socketClosed( int connId, void* yourPtr );
	virtual void			socketPeerClosed( int connId, void* yourPtr );
	virtual void			socketEstablished( int connId, void* yourPtr );
	virtual void			socketStatusArrived( int connId, void* yourPtr, TCPStatusInfo *status );

private:

	bool write( DISTACK_REMOTE_DATA* data, TCPSocket* sendSocket );

	static int commPort;
	MessagingNode::IP_ADDR_LIST m_neighbors;
	IP_ADDR m_localIp;
	int doSend;
	typedef map<TCPSocket*, DISTACK_REMOTE_DATA*, TCPSOCKET_COMP> PAYLOAD_QUEUE;
	PAYLOAD_QUEUE sendQueue;

protected:

	TCPSocket serverSocket;
	DistackTCPSocketMap socketMap;
};

#endif // __REMOTE_COMM_SYSTEM_OMNET_TCP_H
