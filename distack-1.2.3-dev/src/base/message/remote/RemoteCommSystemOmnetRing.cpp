#include "RemoteCommSystemOmnetRing.h"
#include "RemoteMessagingSystem.h"
#include "Distack.h"

int RemoteCommSystemOmnetRing::listenPort = 12345;
const int MAX_DISTANCE = 100;

RemoteCommSystemOmnetRing::RemoteCommSystemOmnetRing (DistackInfo* info)
	: RemoteCommSystem( "omnetpp_ring", "ring-based remote communication system using tcp, udp and rao via omnetpp", info), doSend( 0 ){
}

void RemoteCommSystemOmnetRing::init (int stage)
{
	if(stage == 3) {
		//
		// create RingManager
		//
		rm = new RemoteCommSystemOmnetRingManager();
		//
		// determine my ip-address and my port
		//
		IRoutingTable *rt = RoutingTableAccess().get();
		if(rt == NULL)
			opp_error("couldn't find routingtable\n");
		
		m_localIp = rt->getRouterId();
		myIP = rt->getRouterId();
		
		//
		// register at RingManager
		//
		rm->registerRingPeer(distackModule->getFullPath(), myIP, listenPort, distackModule);
		maxHopDistance = 5; //FIXME: parameter
	}
	else if(stage == 4)
	{
		//
		// open the serversocket and start listening
		//
		serverSocket.setOutputGate(distackModule->gate("sigOutTCP"));
		serverSocket.bind(IPvXAddress((m_localIp).toString().c_str()), listenPort);
		serverSocket.listen();
		logging_info( "messaging server listening at " + distackInfo->modulePath + " with address " + m_localIp.toString() + " on port " + Helper::ltos(listenPort));
		
		//
		// ask RingManager for peers
		//
		rm->getRingPeers(allPeers);
		neighborThreadsVector.clear();
		
	}
	else if(stage == 5)
	{
		getNextNeighbors();
	}
	else if(stage == 6)
	{
		//
		// create TCP-Connections to peers
		//
		cout << "peers size: " << allPeers.size() << endl;
		for(int i=0; i<allPeers.size(); i++)
		{
			if(allPeers[i].openConnection)
			{
				//
				// connect to peer
				//
				TCPSocket *socket = new TCPSocket();
				socket->setOutputGate(distackModule->gate("sigOutTCP"));
				socket->setCallbackObject(this);
				socketMap.addSocket(socket);
				cout << "creating socket to " << allPeers[i].address.str() << endl;
				socket->connect(allPeers[i].address, allPeers[i].port);
				otherThreadsVector.push_back(allPeers[i].address);
				threadCount++;
			}
		}
	}
}

RemoteCommSystemOmnetRing::~RemoteCommSystemOmnetRing ()
{
	sendQueue.clear();
	establishWait.clear();
}


void RemoteCommSystemOmnetRing::getNextNeighbors()
{
	int myIndex = 0;
	for(int i=0; i<allPeers.size(); i++)
		if(allPeers[i].address == myIP)
	{
		myIndex = i;
		break;
	}
	for(int i=0; i<allPeers.size(); i++)
	{
		if(i == myIndex)
			continue;
		IPAddress peer = allPeers[i].address;
		IRoutingTable *rt = RoutingTableAccess().get();
		ARP *arp = check_and_cast<ARP*> (findModuleWherever("arp", distackModule));
		cModule *next = NULL;
		int count = 0;
		bool nextHopFound = false;
		//cout<<"currentPeer: "<<currentPeer<<" nextHopFound: "<<nextHopFound<<endl;
		while ((rt->getRouterId() != peer) && (count < maxHopDistance))
		{
			count++;
			next = (arp->gate("nicOut", rt->getInterfaceForDestAddr(peer)->getNetworkLayerGateIndex())->getPathEndGate())->getOwnerModule()->getParentModule();
			next = next->gate("phys$o")->getPathEndGate()->getOwnerModule()->getParentModule();
			rt = check_and_cast<IRoutingTable*> (findModuleSomewhereUp("routingTable", next));
			arp = check_and_cast<ARP*> (findModuleWherever("arp", next));
		}
		if(rt->getRouterId() == peer)
		{
			for(int j=0; j<allPeers.size(); j++)
			{
				if(peer == allPeers[j].address)
				{
					allPeers[j].knowAsPeer = true;
					if(myIP < peer)
					{
						allPeers[j].openConnection = true;
					}
					else
					{
						DistackOmnetModule* otherMod = (DistackOmnetModule*) allPeers[j].module;
						//						//
//						// mark, that the peer should open an connection to me
						//						//
						((RemoteCommSystemOmnetRing*)(otherMod->getDistack()->getModuleManager()->getMessagingSystem()->getRemoteSystem()->getCommSystem()))->allPeers[myIndex].openConnection = true;
					}
					distanceMap.insert(pair<IPAddress, int> (allPeers[j].address, count));
					break;
				}
			}
		}
	}
}

void RemoteCommSystemOmnetRing::removeThread(IPAddress remoteAddr)
{
	delete socketMap.removeSocket(socketMap.findSocketFor(remoteAddr));
	bool threadRemoved = false;
	THREAD_VEC::iterator vecIt = neighborThreadsVector.begin();
	while(vecIt != neighborThreadsVector.end())
	{
		if( *vecIt == remoteAddr )
		{
			vecIt = neighborThreadsVector.erase(vecIt);
			threadRemoved = true;
			break;
		}
		else
			vecIt++;
	}
	if(!threadRemoved)
	{
		vecIt = otherThreadsVector.begin();
		while(vecIt != otherThreadsVector.end())
		{
			if( *vecIt == remoteAddr )
			{
				vecIt = otherThreadsVector.erase(vecIt);
				break;
			}
			else
				vecIt++;
		}
	}
	threadCount--;
}

void RemoteCommSystemOmnetRing::classifyThread(IPAddress remoteAddr)
{
	bool isKnownPeer = false;
	for(int i=0; i<allPeers.size(); i++)
	{
		if(allPeers[i].address == remoteAddr)
		{
			if(allPeers[i].knowAsPeer)
				isKnownPeer = true;
			break;
		}
	}
	if(!isKnownPeer)
		return;
	THREAD_VEC::iterator it = otherThreadsVector.begin();
	while(it != otherThreadsVector.end())
	{
		if(*it == remoteAddr)
		{
			otherThreadsVector.erase(it);
			neighborThreadsVector.push_back(remoteAddr);
			break;
		}
		it++;
	}
}

int RemoteCommSystemOmnetRing::getDistanceTo(IPAddress source)
{
	DISTANCE_MAP::iterator it = distanceMap.find(source);
	if(it != distanceMap.end())
		return it->second;
	else
	{
		IRoutingTable *rt = RoutingTableAccess().get();
		ARP *arp = check_and_cast<ARP*> (findModuleWherever("arp", distackModule));
		cModule *next = NULL;
		int count = 0;
		while ((rt->getRouterId() != source) && (count < MAX_DISTANCE))
		{
			count++;
			next = (arp->gate("nicOut", rt->getInterfaceForDestAddr(source)->getNetworkLayerGateIndex())->getPathEndGate())->getOwnerModule()->getParentModule();
			next = next->gate("phys$o")->getPathEndGate()->getOwnerModule()->getParentModule();
			rt = check_and_cast<IRoutingTable*> (findModuleSomewhereUp("routingTable", next));
			arp = check_and_cast<ARP*> (findModuleWherever("arp", next));
			
		}
		distanceMap.insert(pair<IPAddress, int>(source, count));
		return count;
	}
	opp_error("unreachable code-line");
	return 0;
}

void RemoteCommSystemOmnetRing::sendMessageToNeighbors(cPacket *msg)
{
	DistackRemoteTCPPayload* data = check_and_cast<DistackRemoteTCPPayload*> (msg);
	for(int i=0; i < neighborThreadsVector.size(); i++)
	{
		DistackRemoteTCPPayload* duplicate = (DistackRemoteTCPPayload*) msg->dup();
		//duplicate->setInitiator(myIP);
		//neighborThreadsVector[i]->setDataToSend(duplicate);
	}
	delete msg;
}

void RemoteCommSystemOmnetRing::handleMessage (cPacket* msg)
{
	if(msg->getArrivalGate()->getIndex() == 2) {
		//handleRAOQuery(msg);
	}
	else if(msg->getArrivalGate()->getIndex() == 1) {
		// a query arrived at a target that doesn't listen to rao
		if(msg->getKind() == UDP_I_ERROR)
		{
			UDPControlInfo *error = dynamic_cast<UDPControlInfo*>(msg->removeControlInfo());
			if(error == NULL) {
				opp_error("invalid udp error message received\n");
			}
			int port = error->getDestPort();
			IPvXAddress address = error->getDestAddr();
			RAO_PAYLOAD_LIST_ITERATOR i = sendQueue[address].begin();
			RAO_PAYLOAD_LIST_ITERATOR iend = sendQueue[address].end();
			for ( ; i != iend; i++) {
				doSend--;
//				(*i)->destroy(); //FIXME: check
			}
			sendQueue.erase(address);
			delete error;
			delete msg;
		}
		else {
			ev << "unknown UDP error\\n";
			delete msg;
		}
	}
	else {
		TCPSocket* socket = socketMap.findSocketFor(msg);
		if (!socket) {
			socket = new TCPSocket(msg);
			socket->setOutputGate(distackModule->gate("sigOutTCP"));
			socket->setCallbackObject(this, socket);
			socketMap.addSocket(socket);
		}
		socket->processMessage(msg);
	}
}

void RemoteCommSystemOmnetRing::socketDataArrived(int, void* socket, cPacket* msg, bool) {
	if (dynamic_cast<DistackRemoteTCPPayload*>(msg)) {
		DistackRemoteTCPPayload* payload = check_and_cast<DistackRemoteTCPPayload*> (msg);
	
		DISTACK_REMOTE_HEADER header;
		unsigned char* headstr = (unsigned char*) malloc (payload->getHeaderArraySize());
		unsigned char* ptr = headstr;
		for(unsigned int i = 0; i<payload->getHeaderArraySize(); i++, ptr++) {
			*ptr = payload->getHeader (i);
		}
		memcpy(&header, headstr, sizeof(header));
		free(headstr);
	
		if(! header.valid()) {
			ev << "Invalid Distack Remote Data Header\\n";
			logging_debug( "Recieved Invalid Distack Remote Data Header");
		}
//cout << "remotecomm got msg from " << (header.source).toString() << " to " << (header.dest).toString() << endl;
		DISTACK_REMOTE_DATA distackData (payload->getDataArraySize());
		unsigned char* datastr = (unsigned char*) malloc (payload->getDataArraySize());
		unsigned char* ptr2 = datastr;
		for(unsigned int i = 0; i<payload->getDataArraySize(); i++, ptr2++) {
			*ptr2 = payload->getData (i);
		}
		memcpy(distackData.data, datastr, payload->getDataArraySize());
		distackData.source = header.source;
		distackData.dest = header.dest;
	
		free(datastr);
		delete payload;
	
		read(distackData);
	}
	else {
		DistackRAOData* request = check_and_cast<DistackRAOData*>(msg);
		if (doSend>0) {
			RAO_PAYLOAD_LIST dataList = sendQueue[request->getTarget()];
			RAO_PAYLOAD_LIST_ITERATOR i = dataList.begin();
			RAO_PAYLOAD_LIST_ITERATOR iend = dataList.end();
			for ( ; i != iend; i++) {
				write(*i, (TCPSocket*)socket);
				doSend--;
//				(*i)->destroy(); //FIXME: check
			}
			sendQueue.erase(request->getTarget());
		}
		delete request;
	}
}


void RemoteCommSystemOmnetRing::socketFailure(int, void* socket, int code) {
	if (code==TCP_I_CONNECTION_RESET) {
		ev << "Connection reset!\\n";
		socketMap.removeSocket(((TCPSocket*)socket));
	}
	else if (code==TCP_I_CONNECTION_REFUSED) {
		ev << "Connection refused!\\n";
		socketMap.removeSocket(((TCPSocket*)socket));
	}
	else if (code==TCP_I_TIMED_OUT) {
		ev << "Connection timed out!\\n";
		socketMap.removeSocket(((TCPSocket*)socket));
	}
}

void RemoteCommSystemOmnetRing::socketClosed (int connId, void*) {
cout << "socket closed" << endl;
}

void RemoteCommSystemOmnetRing::socketPeerClosed (int connId, void* socket) {
cout << "socket peer closed" << endl;
}

void RemoteCommSystemOmnetRing::socketEstablished (int connId, void* socket) {
cout << "socket established for connID " << connId << " from " << m_localIp.toString() << " to " << ((TCPSocket*)socket)->getRemoteAddress().str() << endl;
	
}

void RemoteCommSystemOmnetRing::socketStatusArrived(int, void*, TCPStatusInfo *status) {
cout << "socket status arrived" << endl;
delete status;
}



bool RemoteCommSystemOmnetRing::write (DISTACK_REMOTE_DATA data, MessagingNode::SEND_OPTIONS options)
{
	bool ret = true;

	//
	// determine the attack target and send data towards it
	//



	return ret;
}

bool RemoteCommSystemOmnetRing::write (DISTACK_REMOTE_DATA* data, TCPSocket* sendSocket)
{
//cout << "remotecomm send msg from " << m_localIp.toString() << " to " << sendSocket->remoteAddress().str() << endl;
	data->source = m_localIp;
	data->dest	= IP_ADDR(sendSocket->getRemoteAddress().get4());

	DISTACK_REMOTE_HEADER header (data->len);
	header.source = data->source;
	header.dest   = data->dest;

	char* headstr = (char*) malloc (sizeof(header));
	memcpy(headstr, &header, sizeof(header));

	DistackRemoteTCPPayload* payload = new DistackRemoteTCPPayload("DistackRemotePayload", 0);
	payload->setHeaderArraySize (DISTACK_REMOTE_HEADER::headerlen);
	char* ptr = headstr;
	for(int i = 0; i<16; i++, ptr++) {
		payload->setHeader (i, *ptr);
	}
	free(headstr);
	payload->setDataArraySize (data->len);
	unsigned char* ptr2 = data->data;
	for(unsigned int i = 0; i<data->len; i++, ptr2++) {
		payload->setData (i, *ptr2);
	}
	payload->setByteLength(data->len+DISTACK_REMOTE_HEADER::headerlen);
	data->destroy();
	delete data;

	sendSocket->send(payload);

	return true;
}

RemoteCommSystemOmnetRingManager::RemoteCommSystemOmnetRingManager()
{
}

RemoteCommSystemOmnetRingManager::~RemoteCommSystemOmnetRingManager()
{
}

void RemoteCommSystemOmnetRingManager::registerRingPeer(string modulePath, IPAddress &addr, int port, cModule *mod)
{
	RING_PEER peer(addr, port, modulePath, mod);
	bool inserted = false;
	for(int i=0; i<peers.size(); i++)
	{
		inserted |= (peers[i].isEqual(peer));
	}
	cout << endl;
	if(!inserted)
		peers.push_back(peer);
}

void RemoteCommSystemOmnetRingManager::getRingPeers(RING_PEER_VECTOR &allPeers)
{
	allPeers.clear();
	for(int i=0; i<peers.size(); i++)
		allPeers.push_back(peers[i]);
}

