#include "RemoteCommSystemTcpSocket.h"
#include "RemoteMessagingSystem.h"

RemoteCommSystemTcpSocket::RemoteCommSystemTcpSocket (DistackInfo* info )
:	RemoteCommSystem	("tcp socket", "remote communication system using tcp sockets and based on the asio boost compliant network library", info ),
	m_server			(m_service, this)
{
	//
	// read the neighbors from configuration
	//

	Triggerconf::STRING_LIST ips = Configuration::instance(info)->getRemoteNeighbors ();
	for (Triggerconf::STRING_LIST_ITERATOR i = ips.begin(); i != ips.end(); i++) {
		IP_ADDR addr; 
		
		if (addr.fromString (*i))
			m_neighbors.push_back (addr); 
		else
			logging_error( "invalid remote neithbor ip address " + *i);
	}

	//
	// start the server thread
	//

	m_serviceThread = new boost::thread (boost::bind (&RemoteCommSystemTcpSocket::serviceThreadFunc, this));
	m_localIp = m_server.get_ip_address ();

	logging_info( "messaging server listening on "		+	 
				asio::ip::host_name()				+
				" address "							+
				m_localIp.toString()				+
				" port "							+ 
				Helper::ultos(DISTACK_SERVER_PORT)	);
}

RemoteCommSystemTcpSocket::~RemoteCommSystemTcpSocket ()
{
	m_service.stop();
	m_serviceThread->join();
	delete m_serviceThread;
}

void RemoteCommSystemTcpSocket::serviceThreadFunc (RemoteCommSystemTcpSocket* obj)
{
	obj->m_service.run ();
}

bool RemoteCommSystemTcpSocket::write (DISTACK_REMOTE_DATA data, MessagingNode::SEND_OPTIONS options)
{
	bool ret = true;

	//
	// determine the destination endpoints and send the data
	// to each of them
	//
	// destinations given in a list or all neighbors, determine the list
	//

	MessagingNode::IP_ADDR_LIST destinations;

	if (options.remoteDest == MessagingNode::REMOTE_DESTINATIONS_LIST)
		destinations = options.remoteList;
	else if (options.remoteDest == MessagingNode::REMOTE_DESTINATIONS_NEIGHBOURS)
		destinations = m_neighbors;
	else
		assert (false);
			
	MessagingNode::IP_ADDR_LIST_ITERATOR i    = destinations.begin ();
	MessagingNode::IP_ADDR_LIST_ITERATOR iend = destinations.end   ();

	for ( ; i != iend; i++) {
		ret &= write (data, *i);
	}

	return ret;
}

bool RemoteCommSystemTcpSocket::write (DISTACK_REMOTE_DATA data, IP_ADDR dest)
{
	data.source = m_localIp;
	data.dest = dest;

	//
	// determine the remote entpoint
	//

	asio::io_service clientService;
	tcp::resolver resolver( clientService );
	tcp::resolver::query query( data.dest.toString(), 
		Helper::ultos(DISTACK_SERVER_PORT), 
		tcp::resolver::query::passive | 
		tcp::resolver::query::address_configured | 
		tcp::resolver::query::numeric_service);

	//
	// connect to one of the available endpoints found
	//

	tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
	tcp::resolver::iterator end;

	tcp::socket socket( clientService );
    	boost::system::error_code err = asio::error::host_not_found;

	while (err && endpoint_iterator != end) {
		socket.close	();
		socket.connect	(*endpoint_iterator++, err);
	}

	if (err) return false;

	//
	// send the header over the network
	//

	try {

		DISTACK_REMOTE_HEADER header (data.len);
		header.source = data.source;
		header.dest   = data.dest;

		size_t writtenHeader = 0;
		while (writtenHeader < DISTACK_REMOTE_HEADER::headerlen)
			writtenHeader += socket.write_some (
				asio::buffer(&header+writtenHeader,
				DISTACK_REMOTE_HEADER::headerlen-writtenHeader));

	} catch (std::exception e) {
		return false;
	}

	//
	// send the data over the network
	//

	try {
	
		size_t writtenData = 0;
		while (writtenData < data.len)
			writtenData += socket.write_some (
				asio::buffer(data.data+writtenData, 
				data.len-writtenData));

	} catch (std::exception e) {
		return false;
	}

	return true;
}
