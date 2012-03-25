#ifndef __IP_PACKET_H
#define __IP_PACKET_H

#ifdef OMNET_SIMULATION
	#pragma warning (disable : 4244 4800 4267)
		#include <omnetpp.h>
		#include <IPDatagram.h>
	#pragma warning (default : 4244 4800 4267)
#endif // OMNET_SIMULATION

#include "Packet.h"
#include "base/common/Helper.h"
#include <cassert>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>

using std::vector;

//
// constants for the encapsulated transport protocols
//

#define IPTYPE_IP		0x04
#define IPTYPE_TCP		0x06
#define IPTYPE_UDP		0x11
#define IPTYPE_ICMP		0x01
#define IPTYPE_IPV6		0x29
#define IPTYPE_MPLS		0x89

//
// some ip constants
//

#define	IP_ADDR_LEN					4		
#define IP_HEADER_NO_OPTIONS_LEN	20

//
// masks to fetch combined values
// 

#define IP_HEADER_VERSION(x)		((x &	0xF0	) >>  4	)
#define IP_HEADER_LEN(x)			((x &	0x0F	) *   4	)
#define IP_HEADER_FLAGS(x)			((x &	0xE000	) >> 13	)
#define IP_HEADER_FRAGOFFSET(x)		((x &	0x1FFF	)		)

//
// the IP header
// 

#pragma pack (1)
typedef struct _IP_HEADER {
	unsigned char		version_len;			// 4 bit version and 4 bit length 
	unsigned char		typeofservice;			// type of service . configuration item IpTos
	unsigned short		totallen;				// total length
	unsigned short		identification;			// identification. configuration item IpIdent
	unsigned short		flags_fragoffset;		// 3  bit flags and 13 bit fragment offset field. configuration item IpFragoffset and IpFlags
	unsigned char		ttl;					// time to live. configuration item IpTtl				
	unsigned char		protocol;				// protocol. configuration item IpSourceip
	unsigned short		checksum;				// checksum
	unsigned long		sourceip;				// source ip address. configuration item IpSource
	unsigned long		destip;					// dest ip address. configuration item IpDestip
} IP_HEADER, *PIP_HEADER;
#pragma pack ()

//
// a IP address
//

typedef struct _IP_ADDR {
	unsigned char	x [IP_ADDR_LEN];

	_IP_ADDR () {
		for (int i=0; i<IP_ADDR_LEN; i++)
			x[i] = 0;
	}

	_IP_ADDR (unsigned long addr) {
		for (int i=0; i<IP_ADDR_LEN; i++)
			x[i] = (unsigned char) (addr >> (i*8)) & 0xFF;
	}

#ifdef OMNET_SIMULATION
	_IP_ADDR (IPAddress addr) {
		unsigned long laddr = addr.getInt ();

		for (int i=0; i<IP_ADDR_LEN; i++)
			x[IP_ADDR_LEN-i-1] = (unsigned char) (laddr >> (i*8)) & 0xFF;
	}
#endif // OMNET_SIMULATION

	string toString () {
		ostringstream out;

		for (int i=0; i<IP_ADDR_LEN; i++) {
			out << (int)x[i];
			
			if (i < IP_ADDR_LEN-1) out << ".";
		}

		return out.str ();
	}

	const unsigned char operator[] (int i) {
		if (i < IP_ADDR_LEN ) 
			return x[i];
		else
			return 0;
	}

	bool operator== (const struct _IP_ADDR& right) const {
		return memcmp (right.x, x, IP_ADDR_LEN) == 0;	
	}

	bool operator!= (const struct _IP_ADDR& right) const {
		return !operator== (right);
	}

	bool operator< (const struct _IP_ADDR& right) const {

		for (int i=0; i<IP_ADDR_LEN; i++) {
			if (x[i] < right.x[i])
				return true;
			else if (x[i] > right.x[i])
				return false;
		}

		assert (*this == right);
		return false;
	}

	bool operator> (const struct _IP_ADDR&right) const {
		return (operator==(right) == false) && (operator<(right) == false);
	}

	bool operator<= (const struct _IP_ADDR&right) const {
		return !operator>(right);
	}

	bool operator>= (const struct _IP_ADDR&right) const {
		return !operator<(right);
	}

	struct _IP_ADDR operator& (const struct _IP_ADDR& right) const {
		struct _IP_ADDR ret;

		for (int i=0; i<IP_ADDR_LEN; i++)
			ret.x[i] = x[i] & right.x[i];
			
		return ret;
	}

	struct _IP_ADDR operator~ () const {
		struct _IP_ADDR ret;

		for (int i=0; i<IP_ADDR_LEN; i++)
			ret.x[i] = ~x[i];	
		
		return ret;
	}

	struct _IP_ADDR operator| (const struct _IP_ADDR& right) const {
		struct _IP_ADDR ret;

		for (int i=0; i<IP_ADDR_LEN; i++)
			ret.x[i] = x[i] | right.x[i];	
		
		return ret;
	}

	struct _IP_ADDR& operator++ () {

		// prefix version ++ip;

		bool overflow = true;

		for (int len = IP_ADDR_LEN - 1; len >= 0; len--) {
			
			if (x[len] < 255) {
				x[len]++;
				overflow = false;
				break;
			}

		} // for (int len = PROTOADDR_LEN - 1; len >= 0; len--) 
		
		if (overflow) 
			memset (&x, 0, IP_ADDR_LEN);

		return *this;
	}

	struct _IP_ADDR operator++ (int) {
	
		// postfix version ip++;

		struct _IP_ADDR copy = *this;
		++(*this);

		return copy;
	}

	struct _IP_ADDR swap () const {
		struct _IP_ADDR ret;

		ret.x[0] = x[3];
		ret.x[1] = x[2];
		ret.x[2] = x[1];
		ret.x[3] = x[0];

		return ret;
	}

	string toString () const {

		static const int buffersize = IP_ADDR_LEN*3 + IP_ADDR_LEN - 1 + 1;
		char buf [buffersize] = {0};
		
#ifdef WIN32
		sprintf_s (	buf, 
					buffersize,
					"%d.%d.%d.%d", 
					x[0], x[1], x[2], x[3]	); 
#else
		sprintf (	buf, 
					"%d.%d.%d.%d", 
					x[0], x[1], x[2], x[3]	); 
#endif

		return buf;
	}

	bool fromString (string ip) {

		typedef vector<string>			STRING_LIST;
		typedef STRING_LIST::iterator	STRING_LIST_ITERATOR;

		STRING_LIST list;
		boost::split (list, ip, boost::is_any_of ("."));
		
		if (list.size () != IP_ADDR_LEN) 
			return false;

		STRING_LIST_ITERATOR begin	= list.begin	();
		STRING_LIST_ITERATOR end	= list.end		();

		for (unsigned char i=0; begin != end && i < IP_ADDR_LEN; begin++, i++) {
			
			int val = Helper::stoi (*begin);

			if (val >= 0 && val <= 255)	x [i] = val;
			else						return false;

		} // for (unsigned char i=0; begin != end && i < 4; begin++, i++) 
	
		assert (toString().compare (ip) == 0);
		return true;
	}

} IP_ADDR, *PIP_ADDR;

//
// IP packet class
//

class IpPacket : public Packet
{
public:
							IpPacket(void);
							~IpPacket(void);

	bool					parsePacket					();
	string					toString					();
	unsigned int			getMinProtocolSize			();

	static Packet::PROTOCOL	getTransportProtocol		(unsigned char proto);

	unsigned char			getVersion					();
	unsigned char			getHeaderlength				();
	unsigned char			getTos						();
	unsigned short			getTotallen					();
	unsigned short			getIdentification			();
	unsigned short			getFlags					();
	unsigned short			getFragoffset				();
	unsigned char			getTtl						();
	unsigned char			getProtocol					();
	unsigned short			getChecksum					();
	IP_ADDR					getSourceip					();
	IP_ADDR					getDestip					();
	Packet::PAYLOAD_BUFFER	getOptions				();

	void					setVersion					(unsigned char	ver		);
	void					setHeaderlength				(unsigned char	len		);
	void					setTos						(unsigned char	tos		);
	void					setTotallen					(unsigned short	totlen	);
	void					setIdentification			(unsigned short	ident	);
	void					setFlags					(unsigned short	flgs	);
	void					setFragoffset				(unsigned short	fragoff	);
	void					setTtl						(unsigned char	tl		);
	void					setProtocol					(unsigned char	proto	);
	void					setChecksum					(unsigned short checks	);
	void					setSourceip					(IP_ADDR		sip		);
	void					setDestip					(IP_ADDR		dip		);
	void					setOptions					(unsigned char* buf, int len);
	
	typedef enum _IP_FLAG {
		IP_FLAG_MF = 1,
		IP_FLAG_DF = 2,
		IP_FLAG_R  = 4,
	} IP_FLAG;

	bool					isFlagSet					(IP_FLAG flag);
	void					setFlag						(IP_FLAG flag, bool set = true);

private:

	IP_HEADER				header;
	Packet::PAYLOAD_BUFFER	options; // configuration item IpOptions		
	
protected:

	static unsigned short	checksum				(PIP_HEADER ipheader);

};

#endif // __IP_PACKET_H
