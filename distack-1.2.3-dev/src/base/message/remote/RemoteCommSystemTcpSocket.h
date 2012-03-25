#ifndef __REMOTE_COMM_SYSTEM_TCP_SOCKET_H
#define __REMOTE_COMM_SYSTEM_TCP_SOCKET_H

#include <exception>
#include <cstring>

#include "base/common/Helper.h"
#include "base/common/Log.h"
#include "base/protocol/IpPacket.h"
#include "base/configuration/Configuration.h"
#include "base/message/remote/RemoteCommSystem.h"

#pragma warning (disable : 4267 4996 4005)
	// WinXP (see http://msdn2.microsoft.com/en-us/library/aa383745.aspx)
	#define _WIN32_WINNT 0x0501
	// FD_SETSIZE redefinition compiler warning is a known issue and can be ignored (http://svn.boost.org/trac/boost/ticket/710)
	#include <boost/asio.hpp>
	#include <boost/bind.hpp>
	#include <boost/shared_ptr.hpp>
	#include <boost/enable_shared_from_this.hpp>
	#include <boost/thread/thread.hpp>
#pragma warning (default : 4267 4996 4005)

// this enables easy switching between the
// boost::asio and the asio standalone version
// just comment this line out for the asio 
// standalone version that is not in the boost ns
using namespace boost;
using asio::ip::tcp;

// = 53599. first part of distack hextalk
#define DISTACK_SERVER_PORT 0xd15f

class RemoteCommSystemTcpSocket : public RemoteCommSystem {
public:
	RemoteCommSystemTcpSocket( DistackInfo* info );
	~RemoteCommSystemTcpSocket();

	bool write( DISTACK_REMOTE_DATA data, MessagingNode::SEND_OPTIONS options );

private:

	bool write( DISTACK_REMOTE_DATA data, IP_ADDR dest );

	class tcpConnection : public boost::enable_shared_from_this<tcpConnection> {
	public:
		typedef boost::shared_ptr<tcpConnection> pointer;

		static pointer create( asio::io_service& io_service, RemoteCommSystem* commSystem ) {
			return pointer( new tcpConnection(io_service, commSystem) );
		}

		tcp::socket& socket() {
			return tcpSocket;
		}

		void start() {

			//
			// read in the distack header
			//

			char cheader [DISTACK_REMOTE_HEADER::headerlen];
			size_t headerread = 0;

			while (headerread < DISTACK_REMOTE_HEADER::headerlen){
				headerread += boost::asio::read( tcpSocket, boost::asio::buffer (cheader+headerread, 
					DISTACK_REMOTE_HEADER::headerlen-headerread) );
			}

			DISTACK_REMOTE_HEADER header;
			memcpy( &header, &cheader, DISTACK_REMOTE_HEADER::headerlen );
			if(! header.valid()) return;

			//
			// read in header.payloadlen bytes to form the message
			//

			DISTACK_REMOTE_DATA distackData( header.payloadlen );
			size_t payloadread = 0;

			while (payloadread < header.payloadlen){
				payloadread += boost::asio::read( tcpSocket, boost::asio::buffer (distackData.data+payloadread, 
					header.payloadlen-payloadread) );
			}

			//
			// include endpoints addresses into payload for processing by distack modules
			//

			distackData.source = header.source;
			distackData.dest   = header.dest;

			//
			// push it up the next layer where it will be handled
			//
	
			m_commSystem->read( distackData );
		}

	private:

		RemoteCommSystem* m_commSystem;
		tcp::socket tcpSocket;

		tcpConnection( asio::io_service& io_service, RemoteCommSystem* commSystem ) 
			: tcpSocket( io_service ), m_commSystem( commSystem ) {
		}

		//void handle_write(const asio::error& e, size_t bytes_transferred) {
		//}

	}; // class tcp_connection

	class tcpServer {
	public:
		tcpServer( asio::io_service& io_service, RemoteCommSystemTcpSocket* commSystem )
			:	tcpAcceptor( io_service, tcp::endpoint(tcp::v4(), DISTACK_SERVER_PORT) ),
				m_commSystem( commSystem ) {
			
			start_accept();
		}

		IP_ADDR get_ip_address () {

			//
			// resolve the ip address
			//
			
			tcp::resolver resolver( tcpAcceptor.io_service() );
			tcp::resolver::query	query( boost::asio::ip::host_name(), "" );
			tcp::resolver::iterator iter = resolver.resolve( query );
			tcp::resolver::iterator end;

			//
			// in the following multiple endpoints may be found
			// which ip address should we use? Currently: Take the first endpoint with IPv4 address
			//

			IP_ADDR ret;
			bool foundEndpointIp = false;
			
			for (; iter != end; iter++) {
				tcp::endpoint endpoint = *iter;
				if (! endpoint.address().is_v4()) continue;
				
				string address = endpoint.address().to_v4().to_string();
				ret.fromString (address);
				foundEndpointIp = true;
			} 
			
			if (!foundEndpointIp) {
				Log::error( m_commSystem->distackInfo, "no local ip addresses found" );
			}

			return ret;
		}

	private:

		RemoteCommSystemTcpSocket* m_commSystem;

		void start_accept() {
			tcpConnection::pointer newConnection = tcpConnection::create(tcpAcceptor.io_service(), m_commSystem);

			tcpAcceptor.async_accept(
				newConnection->socket(),
				boost::bind(&tcpServer::handle_accept, this, newConnection,
				boost::asio::placeholders::error)
				);
		}

		void handle_accept( tcpConnection::pointer newConnection, const boost::system::error_code& error ){
			if( !error ){
				newConnection->start();
				start_accept();
			}
		}

		tcp::acceptor tcpAcceptor;

	}; // class tcpServer 

	MessagingNode::IP_ADDR_LIST m_neighbors;
	asio::io_service m_service;
	tcpServer m_server;
	IP_ADDR m_localIp;

	static void serviceThreadFunc( RemoteCommSystemTcpSocket* obj );
	boost::thread* m_serviceThread;

};

#endif // __REMOTE_COMM_SYSTEM_TCP_SOCKET_H
