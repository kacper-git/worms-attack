#include "RemoteCommSystemOmnetPathbased.h"
#include "RemoteMessagingSystem.h"
#include "Distack.h"

int RemoteCommSystemOmnetPathbased::listenPort = 12345;

RemoteCommSystemOmnetPathbased::RemoteCommSystemOmnetPathbased (DistackInfo* info)
:	RemoteCommSystem	("omnetpp_pathbased", "path-based remote communication system using tcp, udp and rao via omnetpp", info), doSend( 0 ){
}

void RemoteCommSystemOmnetPathbased::init (int stage)
{
	if (stage != 3) return;
	cModule* rtmod = distackModule->getParentModule()->getSubmodule("routingTable");
	IRoutingTable* rt = check_and_cast<IRoutingTable*>(rtmod);
	m_localIp = rt->getRouterId();

	serverSocket.setOutputGate(distackModule->gate("sigOutTCP"));
	serverSocket.bind(IPvXAddress((m_localIp).toString().c_str()), listenPort);
	serverSocket.listen();

	udpSocket.setOutputGate(distackModule->gate("sigOutUDP"));
	udpSocket.bind(IPvXAddress((m_localIp).toString().c_str()), listenPort);

	logging_info( "messaging server listening at " + distackInfo->modulePath + " with address " + m_localIp.toString() + " on port " + Helper::ltos(listenPort));
}

RemoteCommSystemOmnetPathbased::~RemoteCommSystemOmnetPathbased ()
{
	sendQueue.clear();
	establishWait.clear();
}

void RemoteCommSystemOmnetPathbased::handleMessage (cPacket* msg)
{
	if(msg->getArrivalGate()->getIndex() == 2) {
		handleRAOQuery(msg);
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

void RemoteCommSystemOmnetPathbased::sendRAORequest (IPvXAddress target) {
	DistackRAOData* request = new DistackRAOData();
	request->setRequester(IPvXAddress((m_localIp).toString().c_str()));
	request->setRequesterPort(listenPort);
	request->setTarget(target);
	request->setId(ev.getUniqueNumber());
	request->setByteLength(DISTACK_RAO_PACKET_SIZE);

	UDPPacket* udpPacket = new UDPPacket("Distack_RAO_Query");
	udpPacket->setByteLength(8);
	udpPacket->setSourcePort(listenPort);
	udpPacket->setDestinationPort(listenPort);
	udpPacket->encapsulate(request);

	IPControlInfo* ipControlInfo = new IPControlInfo();
	ipControlInfo->setProtocol(IP_PROT_UDP);
	ipControlInfo->setDestAddr(target.get4());
	ipControlInfo->setInterfaceId(-1);
	udpPacket->setControlInfo(ipControlInfo);

	distackModule->send(udpPacket, "sigOutRAO");
}

void RemoteCommSystemOmnetPathbased::handleRAOQuery (cPacket* msg) {
	cPacket* encMsg = msg->getEncapsulatedMsg()->getEncapsulatedMsg();
	if (encMsg == NULL) {
		ev << "Skipping handling of unknown RAO message.\\n";
		distackModule->send(msg, "sigOutRAO");
		return;
	}
	DistackRAOData* data = dynamic_cast<DistackRAOData*>(encMsg);
	if (data == NULL) {
		ev << "Skipping handling of RAO message with unknown payload.\\n";
		distackModule->send(msg, "sigOutRAO");
		return;
	}
	TCPSocket* socket = socketMap.findSocketFor(data->getRequester());
	if (!socket) {
		data = dynamic_cast<DistackRAOData*>(msg->getEncapsulatedMsg()->decapsulate());
		socket = new TCPSocket();
		socket->setOutputGate(distackModule->gate("sigOutTCP"));
		socket->setCallbackObject(this, socket);
		socketMap.addSocket(socket);
		socket->connect(data->getRequester(), data->getRequesterPort());
		establishWait[socket->getConnectionId()].push_back(data);
	}
	else {
		if (socket->getState() == TCPSocket::CONNECTED) {
			DistackRAOData* request = new DistackRAOData("Distack_RAO_SendRequest");
			request->setId(data->getId());
			request->setTarget(data->getTarget());
			request->setByteLength(DISTACK_RAO_PACKET_SIZE);
			socket->send(request);
		}
		else if (socket->getState() == TCPSocket::CONNECTING) {
			data = dynamic_cast<DistackRAOData*>(msg->getEncapsulatedMsg()->decapsulate());
			establishWait[socket->getConnectionId()].push_back(data);
		}
		else {
			ev << "got RAO query for socket in invalid state" << endl;
		}
	}
	delete msg;
}

void RemoteCommSystemOmnetPathbased::socketDataArrived(int, void* socket, cPacket* msg, bool) {
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

void RemoteCommSystemOmnetPathbased::socketDatagramArrived(int sockId, void *yourPtr, cMessage *msg, UDPControlInfo *ctrl) {
	// nothing should arrive here
	delete ctrl;
	delete msg;
}

void RemoteCommSystemOmnetPathbased::socketFailure(int, void* socket, int code) {
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

void RemoteCommSystemOmnetPathbased::socketClosed (int connId, void*) {
cout << "socket closed" << endl;
}

void RemoteCommSystemOmnetPathbased::socketPeerClosed (int connId, void* socket) {
cout << "socket peer closed" << endl;
}

void RemoteCommSystemOmnetPathbased::socketEstablished (int connId, void* socket) {
//cout << "socket established for connID " << connId << " from " << m_localIp.toString() << " to " << ((TCPSocket*)socket)->remoteAddress().str() << endl;
	while (!establishWait[connId].empty()) {
		DistackRAOData* query = establishWait[connId].front();
		DistackRAOData* request = new DistackRAOData("Distack_RAO_SendRequest");
		request->setId(query->getId());
		request->setTarget(query->getTarget());
		request->setByteLength(DISTACK_RAO_PACKET_SIZE);
		((TCPSocket*)socket)->send(request);
		delete query;
		establishWait[connId].pop_front();
	}
	establishWait.erase(connId);
}

void RemoteCommSystemOmnetPathbased::socketStatusArrived(int, void*, TCPStatusInfo *status) {
cout << "socket status arrived" << endl;
delete status;
}



bool RemoteCommSystemOmnetPathbased::write (DISTACK_REMOTE_DATA data, MessagingNode::SEND_OPTIONS options)
{
	bool ret = true;

	//
	// determine the attack target and send data towards it
	//

	MessagingNode::IP_ADDR_LIST destinations = options.remoteList;;

	if (destinations.begin() != destinations.end()) {
		DISTACK_REMOTE_DATA* dataCopy = new DISTACK_REMOTE_DATA(data.len);
		memcpy(dataCopy->data, data.data, data.len);
		IPvXAddress target((*(destinations.begin())).toString().c_str());
		TCPSocket* socket = socketMap.findSocketFor(target);
		if (!socket) {
			sendQueue[target].push_back(dataCopy);
			doSend++;
			sendRAORequest(target);
			cout << "try to send to " << target.str() << " from " << m_localIp.toString() << endl;
			// should schedule timer, if no one wants this data
		}
		else {
			write(dataCopy, socket);
		}
	}
	else {
		cout << "path based remotecomm was not provided with attack target" << endl;
	}

	return ret;
}

bool RemoteCommSystemOmnetPathbased::write (DISTACK_REMOTE_DATA* data, TCPSocket* sendSocket)
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

