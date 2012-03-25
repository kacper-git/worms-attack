#ifndef __UDP_PACKET_H
#define __UDP_PACKET_H

#include "Packet.h"
#include "IpPacket.h"
#include "Ipv6Packet.h"
#include "PayloadPacket.h"

//
// a UDP header
//

#pragma pack (1)
typedef struct _UDP_HEADER {
	unsigned short	sourceport;		// source port. configuration item UdpSourceport
	unsigned short	destport;		// destination port. configuration item UdpDestport
	unsigned short	len;			// udp length 
	unsigned short	checksum;		// udp checksum 
} UDP_HEADER, *PUDP_HEADER  ;
#pragma pack ()

//
// UDP pseudo header, needed for checksumming
//

#pragma pack (1)
typedef struct _UDP_PSEUDO_HEADER {
	unsigned char	reserved;
	unsigned char	protocol;
	unsigned short	udplength;
} UDP_PSEUDO_HEADER, *PUDP_PSEUDO_HEADER;

typedef struct _UDP_IP4_PSEUDO_HEADER : public UDP_PSEUDO_HEADER {
	IP_ADDR			sourceip;
	IP_ADDR			destip;
} UDP_IP4_PSEUDO_HEADER, *PUDP_IP4_PSEUDO_HEADER;

typedef struct _UDP_IP6_PSEUDO_HEADER : public UDP_PSEUDO_HEADER {
	IPV6_ADDR		sourceip;
	IPV6_ADDR		destip;
} UDP_IP6_PSEUDO_HEADER, *PUDP_IP6_PSEUDO_HEADER;
#pragma pack ()

//
// UdpPacket class representing a udp packet
//

class UdpPacket : public Packet
{
public:
	UdpPacket										(void);
	~UdpPacket										(void);

	bool					parsePacket				();
	string					toString				();
	unsigned int			getMinProtocolSize		();	

	unsigned short			getSourceport			();		
	unsigned short			getDestport				();		
	unsigned short			getLen					();						
	unsigned short			getChecksum				();		

	void					setSourceport			(unsigned short sp);		
	void					setDestport				(unsigned short dp);		
	void					setLen					(unsigned short len);						
	void					setChecksum				(unsigned short chksum);	

	void					setIpAddresses			(IP_ADDR source, IP_ADDR dest);
	void					setIpAddresses			(IPV6_ADDR source, IPV6_ADDR dest);

private:
	UDP_HEADER				header;	

	// the source and dest IP, we need this to calculate the checksum
	IP_ADDR					sourceip, destip;
	IPV6_ADDR				sourceip6, destip6;
	Packet::PROTOCOL		ipProtocol;

	// calculate the UDP checksum
	static unsigned short	checksum				(PUDP_HEADER header, void* sourceip, void* destip, Packet::PROTOCOL ipproto, unsigned char* data, int datalen);
};

#endif // __UDP_PACKET_H
