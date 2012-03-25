#ifndef __PACKET_H
#define __PACKET_H

#include <iostream>
#include <sstream>
#include <cstring>
#include <string>
#include <iomanip>
#include <map>
#include <cassert>
#include "ProtocolNameResolver.h"

class DistackInfo;

using std::map;
using std::ostringstream;
using std::cout;
using std::pair;
using std::string;

#define swap16(x) (((x & 0xff) << 8) | ((x & 0xff00) >> 8))
#define swap32(x) ((x << 24) | ((x & 0xff00) << 8) | ((x & 0xff0000) >> 8) | (x >> 24))

class Packet 
{
public:
	Packet();
	virtual ~Packet();

	bool createNextLayer( DistackInfo* info );
	unsigned int getSize();
	void setSize ( unsigned int len, bool pseudo = false );
	unsigned char* getBuffer();

	virtual bool parsePacket() = 0;
	virtual string toString() = 0;
	virtual unsigned int getMinProtocolSize() = 0;

	typedef enum _PROTOCOL {
		PROTO_NONE,									// no next protocol
		PROTO_DATA_PAYLOAD,							// data payload
		PROTO_ETHERNET,								// ethernet packet
		PROTO_ARP,									// arp packet
		PROTO_IP,									// ip packet
		PROTO_IPV6,									// ipv6 packet
		PROTO_TCP,									// tcp packet
		PROTO_UDP,									// udp packet
		PROTO_ICMP,									// icmp packet
		PROTO_MPLS,									// mpls packet

		PROTO_MAXIMUM,								// end identifier
	} PROTOCOL;

	typedef struct _PAYLOAD_BUFFER {
		unsigned char*	buf;			// pointer to the data buffer
		unsigned int	size;			// the size of the buffer
		unsigned int	pseudosize;		// tell any lower protocol that uses this buffer to set its length in a length field to this pseudo size

		_PAYLOAD_BUFFER () {
			buf			= NULL;
			size		= 0;
			pseudosize	= 0;
		}

		_PAYLOAD_BUFFER (unsigned char* _buf, int _size) {
			buf			= _buf;
			size		= _size;
			pseudosize	= _size;
		}

		void destroy () {
			if (buf != NULL)
				free (buf);
		}

		string toString (bool decodestring = false) {
			if (buf == NULL || size == 0) return "";

			ostringstream out;
			unsigned char* pos = buf;
			
			if (! decodestring) {
				for (unsigned int i=0; i<size; i++, pos++) {
					out << std::hex << std::setw (2) << std::setfill ('0') << (int)*pos;
					if (i+1 != size) out << " ";
				}
			} else {
				for (unsigned int i=0; i<size; i++, pos++) 
					out << (char) *pos;
			}

			return out.str ();
		}
	} PAYLOAD_BUFFER, *PPAYLOAD_BUFFER; 

	PROTOCOL				getProtocol				();
	
	static string			getProtocolNameFromId	(PROTOCOL proto);
	static PROTOCOL			getProtocolIdFromName	(string name);

	Packet*					getNextPacket			();
	void					setNextPacket			(Packet* nextpacket);
	void					setNextProtocol			(PROTOCOL proto);
	PROTOCOL				getNextProtocol			();

	void					setChecksumValidation	(bool validate);
	bool					getChecksumValidation	();

	bool					getChecksumgood			();
	void					setChecksumgood			(bool good);

protected:

	unsigned char*			buffer;					// buffer of the raw data of this protocol including all payload protocols
	unsigned int			size;					// size of the raw data of this protocol including all payload protocols
	unsigned int			layersize;				// size of this protocol
	PROTOCOL				protocol;				// this protocol
	PROTOCOL				nextProtocol;			// the payload protocol
	Packet*					nextPacket;				// the next payload packet

	bool					checksumcheck;			// check the checksum for correctness
	bool					checksumgood;			// is the checksum good?
	static unsigned short	checksum				(unsigned char* databuf, int len);

};

inline void Packet::setSize(unsigned int len, bool pseudo)
{
#ifdef OMNET_SIMULATION
	assert (pseudo == true);
#endif // OMNET_SIMULATION

	//
	// if only the pseudo size is to be set we allocate no memory
	// this is useful if we do only link packets which are ready to use
	//

	if (! pseudo) {

		if (len <= 0) {
			buffer = NULL;
		} else {
			if (size == 0)
				buffer = (unsigned char*) malloc (len);
			else
				buffer = (unsigned char*) realloc (buffer, len);
		}
	} // if (! pseudo) 

	size = len;
}

#endif // __PACKET_H
