#include "RemoteCommSystemOmnetTcp.h"
#include "RemoteMessagingSystem.h"
#include "Distack.h"

/**
 * the port used for all communication attempts
 */
int RemoteCommSystemOmnetTcp::commPort = 12345;

/**
 * Constructor
 * Constructs a new RemoteCommSystemOmnetTcp
 * This specific CommSystem provides an implementation of a simple neighbor based communication system with fixed neighbors
 */
RemoteCommSystemOmnetTcp::RemoteCommSystemOmnetTcp (DistackInfo* info)
:	RemoteCommSystem ("omnetpp_tcp", "remote communication system to fixed neighbors using tcp via omnetpp", info), doSend( 0 ) {
	
}

/**
 * Called upon complete initialization of the distack module
 * Retrieves the IP Address of the associated distack module and saves it.
 * Reads all fixed neighbor communication targets from Configuration.
 * Sets up the serversocket that listens for communication attempts
 */
void RemoteCommSystemOmnetTcp::init (int stage)
{
	if (stage != 3) return;
	cModule* rtmod = distackModule->getParentModule()->getSubmodule("routingTable");
	IRoutingTable* rt = check_and_cast<IRoutingTable*>(rtmod);
	m_localIp = rt->getRouterId();

	//
	// read the neighbors from configuration
	//

	Triggerconf::STRING_LIST ips = Configuration::instance(distackInfo)->getRemoteNeighbors ();
	for (Triggerconf::STRING_LIST_ITERATOR i = ips.begin(); i != ips.end(); i++) {
		IP_ADDR addr;

		if (addr.fromString (*i)) {
			if (addr != m_localIp) {
				m_neighbors.push_back (addr);
			}
		}
		else
			logging_error( "invalid remote neighbor ip address " + *i);
	}

	serverSocket.setOutputGate(distackModule->gate("sigOutTCP"));
	serverSocket.bind(IPvXAddress((m_localIp).toString().c_str()), commPort);
	serverSocket.listen();

	logging_info( "messaging server listening at " + distackInfo->modulePath + " with address " + m_localIp.toString() + " on port " + Helper::ltos(commPort));
}

/**
 * Destructor
 */
RemoteCommSystemOmnetTcp::~RemoteCommSystemOmnetTcp ()
{

}

void RemoteCommSystemOmnetTcp::handleMessage (cPacket* msg)
{
//cout << "message with name " << msg->name() << " kind " << msg->kind() << " on arrivalgate " << (msg->arrivalGate() ? msg->arrivalGate()->name() : "no gate") << " with index " << (msg->arrivalGate() ? msg->arrivalGate()->index() : NULL) << " at " << m_localIp.toString() << endl;

	TCPSocket *socket = socketMap.findSocketFor(msg);
	if (!socket)
	{
		socket = new TCPSocket(msg);
		socket->setOutputGate(distackModule->gate("sigOutTCP"));
		socket->setCallbackObject(this, socket);
		socketMap.addSocket(socket);
	}
	socket->processMessage(msg);

}

void RemoteCommSystemOmnetTcp::socketDataArrived(int, void* socket, cPacket* msg, bool) {
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

void RemoteCommSystemOmnetTcp::socketFailure(int, void* socket, int code) {
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

void RemoteCommSystemOmnetTcp::socketClosed (int connId, void*) {
cout << "socket closed" << endl;
}

void RemoteCommSystemOmnetTcp::socketPeerClosed (int connId, void* socket) {
cout << "socket peer closed" << endl;
}

void RemoteCommSystemOmnetTcp::socketEstablished (int connId, void* socket) {
//cout << "socket established for connID " << connId << " from " << m_localIp.toString() << " to " << ((TCPSocket*)socket)->remoteAddress().str() << endl;
	socketMap.addSocket((TCPSocket*)socket);
	if (doSend>0) {
		DISTACK_REMOTE_DATA* data = sendQueue[(TCPSocket*)socket];
		if (data) {
			write(data, (TCPSocket*)socket);
			doSend--;
		}
	}
}

void RemoteCommSystemOmnetTcp::socketStatusArrived(int, void*, TCPStatusInfo *status) {
cout << "socket status arrived" << endl;
delete status;
}



bool RemoteCommSystemOmnetTcp::write (DISTACK_REMOTE_DATA data, MessagingNode::SEND_OPTIONS options)
{
	bool ret = true;

	//
	// determine the destination endpoints and send the data
	// to each of them
	//
	// destinations given in a list or all neighbors, determine the list
	//

	MessagingNode::IP_ADDR_LIST destinations;

	if (options.remoteDest == MessagingNode::REMOTE_DESTINATIONS_LIST) {
		destinations = options.remoteList;
	}
	else if (options.remoteDest == MessagingNode::REMOTE_DESTINATIONS_NEIGHBOURS) {
		destinations = m_neighbors;
	}
	else
		assert (false);

	MessagingNode::IP_ADDR_LIST_ITERATOR i    = destinations.begin ();
	MessagingNode::IP_ADDR_LIST_ITERATOR iend = destinations.end   ();

	for ( ; i != iend; i++) {
		DISTACK_REMOTE_DATA* dataCopy = new DISTACK_REMOTE_DATA(data.len);
		memcpy(dataCopy->data, data.data, data.len);
		TCPSocket* socket = socketMap.findSocketFor(IPvXAddress((*i).toString().c_str()));
		if (!socket) {
			socket = new TCPSocket();
			socket->setOutputGate(distackModule->gate("sigOutTCP"));
			socket->setCallbackObject(this, socket);
			socket->connect(IPvXAddress((*i).toString().c_str()), commPort);
			sendQueue[socket] = dataCopy;
			doSend++;
		}
		else {
			write(dataCopy, socket);
		}
	}
	return ret;
}

bool RemoteCommSystemOmnetTcp::write (DISTACK_REMOTE_DATA* data, TCPSocket* sendSocket)
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

