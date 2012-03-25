#ifndef __REMOTE_COMM_SYSTEM_OMNET_RING_H
#define __REMOTE_COMM_SYSTEM_OMNET_RING_H

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
#include <map>
#include <vector>
#include <IPAddress.h>
#include <iostream>
#include <string>
#include <ModuleAccess.h>
#include <RoutingTable.h>
#include <RoutingTableAccess.h>
#include <ARP.h>

using std::endl;
using std::map;
using std::pair;
using std::vector;
using std::string;

typedef struct _RPEER
{
	_RPEER()
	{
		this->port = -1;
		this->distance = INT_MAX;
		openConnection = false;
		knowAsPeer = false;
		module = NULL;
	}
	_RPEER(string fullPath)
	{
		this->port = -1;
		this->moduleFullPath = fullPath;
		this->distance = INT_MAX;
		openConnection = false;
		knowAsPeer = false;
		module = NULL;
	}
	_RPEER(const _RPEER &other)
	{
		this->port = other.port;
		this->address.set(other.address.getInt());
		this->moduleFullPath = other.moduleFullPath;
		this->distance = other.distance;
		this->openConnection = other.openConnection;
		this->knowAsPeer = other.knowAsPeer;
		module = other.module;
	}
	_RPEER(IPAddress &addr)
	{
		this->address = addr;
		this->port = -1;
		this->distance = INT_MAX;
		openConnection = false;
		knowAsPeer = false;
		module = NULL;
	}
	_RPEER(IPAddress &addr, int port, string fullPath)
	{
		this->address = addr;
		this->port = port;
		this->moduleFullPath = fullPath;
		this->distance = INT_MAX;
		openConnection = false;
		knowAsPeer = false;
		module = NULL;
	}
	_RPEER(IPAddress &addr, int port, string fullPath, cModule *mod)
	{
		this->address = addr;
		this->port = port;
		this->moduleFullPath = fullPath;
		this->distance = INT_MAX;
		openConnection = false;
		knowAsPeer = false;
		module = mod;
	}
	_RPEER(IPAddress addr, string fullPath)
	{
		this->address = addr;
		this->port = -1;
		this->moduleFullPath = fullPath;
		this->distance = INT_MAX;
		openConnection = false;
		knowAsPeer = false;
		module = NULL;
	}
	void setPort(int port)
	{
		this->port = port;
	}
	void setAddress(IPAddress &addr)
	{
		this->address = addr;
	}
	void setDistance(int dist)
	{
		this->distance = dist;
	}
	bool isEqual(_RPEER other)
	{
		if( (this->moduleFullPath == other.moduleFullPath) &&
				   (this->address == other.address) &&
				   (this->port == other.port))
			return true;
		return false;
	}
	int distance;
	string moduleFullPath;
	IPAddress address;
	int port;
	bool openConnection;
	bool knowAsPeer;
	cModule *module;
} RING_PEER;

typedef vector<RING_PEER> RING_PEER_VECTOR;

class RemoteCommSystemOmnetRingManager {
	protected:
		RING_PEER_VECTOR peers;
	public:
		RemoteCommSystemOmnetRingManager();
		virtual ~RemoteCommSystemOmnetRingManager();
		void registerRingPeer(string modulePath, IPAddress &ip, int listenPort, cModule* mod);
		void getRingPeers(RING_PEER_VECTOR &ringPeers);
};

typedef vector<IPAddress> THREAD_VEC;
typedef map<IPAddress, int> DISTANCE_MAP;

class RemoteCommSystemOmnetRing : public RemoteCommSystem, public TCPSocket::CallbackInterface {
public:
	RemoteCommSystemOmnetRing( DistackInfo* info );
	~RemoteCommSystemOmnetRing();

	bool write( DISTACK_REMOTE_DATA data, MessagingNode::SEND_OPTIONS options );
	void handleMessage( cPacket* msg );
	void init( int stage );

	virtual void socketDataArrived( int connId, void* yourPtr, cPacket* msg, bool urgent );
	virtual void socketFailure( int connId, void* yourPtr, int code );
	virtual void socketClosed( int connId, void* yourPtr );
	virtual void socketPeerClosed( int connId, void* yourPtr );
	virtual void socketEstablished( int connId, void* yourPtr );
	virtual void socketStatusArrived( int connId, void* yourPtr, TCPStatusInfo *status );

private:

	bool write( DISTACK_REMOTE_DATA* data, TCPSocket* sendSocket );

	//
	// peers i have discovered
	//
	THREAD_VEC neighborThreadsVector;

	//
	// peers who know me, but i don't know them
	//
	THREAD_VEC otherThreadsVector;

	int maxHopDistance;
	DISTANCE_MAP distanceMap;
	RING_PEER_VECTOR allPeers;
	int nslpId, threadCount;
	
	IPAddress myIP;
	
	void removeThread(IPAddress remoteAddr);
	int getDistanceTo(IPAddress source);
	void sendMessageToPeers(cPacket *msg);
	void classifyThread(IPAddress remoteAddr);
	void getNextNeighbors();
	void sendMessageToNeighbors(cPacket *data);
	
	MessagingNode::IP_ADDR_LIST m_neighbors;
	IP_ADDR	m_localIp;
	int doSend;
	static int listenPort;
	typedef list<DISTACK_REMOTE_DATA*> RAO_PAYLOAD_LIST;
	typedef RAO_PAYLOAD_LIST::iterator RAO_PAYLOAD_LIST_ITERATOR;
	typedef map<IPvXAddress, RAO_PAYLOAD_LIST> RAO_PAYLOAD_QUEUE;
	RAO_PAYLOAD_QUEUE sendQueue;
	typedef list<DistackRAOData*> ESTABLISH_WAIT_LIST;
	typedef ESTABLISH_WAIT_LIST::iterator ESTABLISH_WAIT_LIST_ITERATOR;
	typedef map<int, ESTABLISH_WAIT_LIST> ESTABLISH_WAIT_QUEUE;
	ESTABLISH_WAIT_QUEUE establishWait;
	RemoteCommSystemOmnetRingManager* rm;

protected:
	TCPSocket serverSocket;
	DistackTCPSocketMap socketMap;
};

#endif // __REMOTE_COMM_SYSTEM_OMNET_RING_H
