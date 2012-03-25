#ifndef __REMOTE_COMM_SYSTEM_OMNET_PATHBASED_H
#define __REMOTE_COMM_SYSTEM_OMNET_PATHBASED_H

#include "base/message/remote/RemoteCommSystem.h"
#include "base/common/Helper.h"
#include "base/protocol/IpPacket.h"
#include "base/common/Log.h"
#include "base/configuration/Configuration.h"
#include <DistackRemoteTCPPayload_m.h>
#include <DistackRAOData_m.h>
#include <IPControlInfo.h>
#include <UDPControlInfo_m.h>
#include <TCPSegment.h>
#include <IPDatagram.h>
#include <UDPPacket.h>
#include <RoutingTable.h>
#include <cstring>
#include <TCPSocket.h>
#include <UDPSocket.h>
#include <DistackTCPSocketMap.h>

class RemoteCommSystemOmnetPathbased : public RemoteCommSystem, public TCPSocket::CallbackInterface, public UDPSocket::CallbackInterface {
public:
	RemoteCommSystemOmnetPathbased	(DistackInfo* info);
	~RemoteCommSystemOmnetPathbased	();

	bool write( DISTACK_REMOTE_DATA data, MessagingNode::SEND_OPTIONS options );
	void handleMessage( cPacket* msg );
	void init							(int stage);

	virtual void			socketDataArrived				(int connId, void* yourPtr, cPacket* msg, bool urgent);
	virtual void			socketFailure					(int connId, void* yourPtr, int code);
	virtual void			socketClosed					(int connId, void* yourPtr);
	virtual void			socketPeerClosed				(int connId, void* yourPtr);
	virtual void			socketEstablished				(int connId, void* yourPtr);
	virtual void			socketStatusArrived				(int connId, void* yourPtr, TCPStatusInfo *status);
	virtual void			socketDatagramArrived			(int sockId, void *yourPtr, cMessage *msg, UDPControlInfo *ctrl);

private:

	bool					write							(DISTACK_REMOTE_DATA* data, TCPSocket* sendSocket);
	void					sendRAORequest					(IPvXAddress target);
	void					handleRAOQuery				(cPacket* msg);

	MessagingNode::IP_ADDR_LIST 	m_neighbors;
	IP_ADDR							m_localIp;
	int								doSend;
	static int						listenPort;
	typedef list<DISTACK_REMOTE_DATA*> RAO_PAYLOAD_LIST;
	typedef RAO_PAYLOAD_LIST::iterator RAO_PAYLOAD_LIST_ITERATOR;
	typedef map<IPvXAddress, RAO_PAYLOAD_LIST> RAO_PAYLOAD_QUEUE;
	RAO_PAYLOAD_QUEUE				sendQueue;
	typedef list<DistackRAOData*>	ESTABLISH_WAIT_LIST;
	typedef ESTABLISH_WAIT_LIST::iterator ESTABLISH_WAIT_LIST_ITERATOR;
	typedef map<int, ESTABLISH_WAIT_LIST> ESTABLISH_WAIT_QUEUE;
	ESTABLISH_WAIT_QUEUE			establishWait;

protected:

	TCPSocket						serverSocket;
	UDPSocket						udpSocket;
	DistackTCPSocketMap				socketMap;
};



#endif // __REMOTE_COMM_SYSTEM_OMNET_PATHBASED_H
