#ifndef __REMOTE_COMM_SYSTEM_H
#define __REMOTE_COMM_SYSTEM_H

#include <string>
#include "base/protocol/IpPacket.h"
#include "base/message/MessagingNode.h"

#ifdef OMNET_SIMULATION
  #include <TCPSocket.h>
  #include <omnetpp.h>
#endif // OMNET_SIMULATION

using std::string;

// the distack magic. 4 bytes that nearly looks like distack :)
#define DISTACK_REMOTE_MESSAGING_MAGIC 0xd15fac30 

typedef struct _DISTACK_REMOTE_DATA {
	IP_ADDR		source;
	IP_ADDR		dest;

	unsigned char*	data;
	unsigned long	len;

	_DISTACK_REMOTE_DATA (int length = 0) {
		if (length > 0) data = (unsigned char*) malloc (length);
		else data = 0;

		len = length;
	}

	void destroy () {
		free (data);
	}
} DISTACK_REMOTE_DATA;

typedef struct _DISTACK_REMOTE_HEADER {
	unsigned long			magic;
	unsigned long			payloadlen;
	IP_ADDR				source;
	IP_ADDR				dest;
	static const unsigned long	headerlen = 16;

	_DISTACK_REMOTE_HEADER () {
		_DISTACK_REMOTE_HEADER (0);
	}

	_DISTACK_REMOTE_HEADER (unsigned long len) {
		magic		= DISTACK_REMOTE_MESSAGING_MAGIC;
		payloadlen	= len;
	}
	
	unsigned long totalLen () {
		return  headerlen + payloadlen;
	}

	bool valid () {
		return (magic == DISTACK_REMOTE_MESSAGING_MAGIC);
	}
} DISTACK_REMOTE_HEADER;

#ifdef OMNET_SIMULATION
struct TCPSOCKET_COMP {
	bool operator() (TCPSocket* one, TCPSocket* two) const {
		return one->getConnectionId() < two->getConnectionId();
	}
};
#endif // OMNET_SIMULATION

class RemoteMessagingSystem; // forward decl
#ifdef OMNET_SIMULATION
class DistackOmnetModule; // forward decl
#endif // OMNET_SIMULATION

class RemoteCommSystem {
public:
	RemoteCommSystem( string name, string description, DistackInfo* info);
	virtual ~RemoteCommSystem();

	void setMessagingSystem( RemoteMessagingSystem* system );

	//
	// write data to the network. this function must return as fast
	// as possible! If the write takes a long time, the implemented
	// RemoteCommSystem must buffer the data and write it later.
	// The DATA.data buffer is destroyed by the RemoteMessagingSystem
	// as soon as the function returns! If doing async writes the 
	// implemented RemoteCommSystem must create a copy of the data!
	virtual bool write( DISTACK_REMOTE_DATA data, MessagingNode::SEND_OPTIONS options ) = 0;

	//
	// call this function from your ReadCommSystem implementation
	// when you got data read and ready to transfer to upper layers
	void read( DISTACK_REMOTE_DATA data );

	string getName();
	string getDescription();

#ifdef OMNET_SIMULATION
	virtual void handleMessage( cPacket* msg ) = 0;
	virtual void init( int stage ) = 0;
	void setDistackModule( DistackOmnetModule* module );
#endif // OMNET_SIMULATION

protected:
	DistackInfo* distackInfo;

#ifdef OMNET_SIMULATION
	DistackOmnetModule* distackModule;
#endif // OMNET_SIMULATION

private:
	string m_name;
	string m_description;
	RemoteMessagingSystem* m_messagingSystem;
};

#endif // __REMOTE_COMM_SYSTEM_H
