#ifndef __IPV6_PACKET_H
#define __IPV6_PACKET_H

#include "Packet.h"
#include "IpPacket.h" // needed for the transport protocol constants

#define IPV6_ADDR_LEN	16 

///
/// IPv6 IP address
///

typedef struct _IPV6_ADDR {
	unsigned short x [IPV6_ADDR_LEN/2];

	//
	// print an IPv6 address according to RFC 2373, 2.2
	// http://www.ietf.org/rfc/rfc2373.txt
	//

	string toString () {
		ostringstream out;

		for (int i=0; i<IPV6_ADDR_LEN/2; i++) {

			out << std::hex << swap16 (x[i]);
			if ((i < IPV6_ADDR_LEN/2 - 1)) out << ":";

		} // for (int i=0; i<IPV6_ADDR_LEN/2; i++) 

		return out.str ();
	}
} IPV6_ADDR, *PIPV6_ADDR;

//
// IPv6 header
//

typedef struct _IPV6_HEADER {
	unsigned int	version_trafficclass_flowlabel;		// configuration item Ipv6Trafficclass and Ipv6Flowlabel
	unsigned short	payloadlen;							
	unsigned char	nextheader;	
	unsigned char	hoplimit;							// configuration item Ipv6Hoplimit
	IPV6_ADDR		sourceaddr;							// configuration item Ipv6Sourceaddr
	IPV6_ADDR		destaddr;							// configuration item Ipv6Destaddr
} IPV6_HEADER, *PIPV6_HEADER;

//
// macros to fetch values from bytes
//

#define IPV6_VERSION(x) 		((x & 0xF0000000) >> 28)
#define IPV6_TRAFFICCLASS(x)	((x & 0x0FF00000) >> 20)	
#define IPV6_FLOWLABEL(x)		((x & 0x000FFFFF)      )	

//
// IPv6Packet class representing an IPv6 packet
//

class Ipv6Packet : public Packet {
	
public:

							Ipv6Packet			();
							~Ipv6Packet			();	
		
	bool					parsePacket			();
	string					toString			();
	unsigned int			getMinProtocolSize	();

	unsigned char			getVersion			();
	unsigned char			getTrafficclass		();
	unsigned int			getFlowlabel		();
	unsigned short			getPayloadlen		();
	unsigned char			getNextheader		();
	unsigned char			getHoplimit			();
	IPV6_ADDR				getSourceaddr		();
	IPV6_ADDR				getDestaddr			();
	
	void					setVersion			(unsigned char 	version			);
	void					setTrafficclass		(unsigned char 	trafficclass	);
	void					setFlowlabel		(unsigned int 	flowlabel		);
	void					setPayloadlen		(unsigned short payloadlen		);
	void					setNextheader		(unsigned char 	nextheader		);
	void					setHoplimit			(unsigned char 	hoplimit		);
	void					setSourceaddr		(IPV6_ADDR 		sourceaddr		);
	void					setDestaddr			(IPV6_ADDR 		destaddr		);
			
private:
		
	IPV6_HEADER				header;

};

#endif // __IPV6_PACKET_H

