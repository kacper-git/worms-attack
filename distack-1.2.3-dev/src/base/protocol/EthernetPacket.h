#ifndef	__ETHERNET_HEADER_H
#define __ETHERNET_HEADER_H

#include "Packet.h"

//
// some ethernet constants
//

#define	ETHER_ADDR_LEN		6		// length of an Ethernet address

//
// Structure of a 10Mb/s Ethernet header.
//

#pragma pack (1)
typedef struct	_ETHERNET_HEADER {
	unsigned char	desthost	[ETHER_ADDR_LEN];	// configuration item MacDest
	unsigned char	sourcehost	[ETHER_ADDR_LEN];	// configuration item MacSource
	unsigned short	type;							// configuration item MacType
} ETHERNET_HEADER, *PETHERNET_HEADER ;
#pragma pack ()

//
// some ethertypes for the encapsulated network protocol
//

#define ETHERTYPE_UNKNOWN			0x0000	// unknown protocol type
#define	ETHERTYPE_IP				0x0800	// IP protocol version 4
#define	ETHERTYPE_ARP				0x0806	// Address resolution protocol 
#define	ETHERTYPE_IPV6				0x86DD	// IP protocol version 6 
#define ETHERTYPE_MPLS				0x8847  // MPLS unicast
#define ETHERTYPE_MPLS_MULTICAST	0x8848  // MPLS multicast

//
// a MAC address
//

typedef struct _MAC_ADDR {
	unsigned char x[ETHER_ADDR_LEN];

	string toString () {
		ostringstream out;

		for (int i=0; i<ETHER_ADDR_LEN; i++) {
			out << std::hex << std::setw (2) << std::setfill ('0') << (int)x[i];
			
			if (i < ETHER_ADDR_LEN-1) out << "-";
		}

		return out.str ();
	}
} MAC_ADDR, *PMAC_ADDR;

//
// EthernetPacket class, representing an ethernet packet
//

class EthernetPacket : public Packet
{
public:

	EthernetPacket												(void);
	~EthernetPacket												(void);

	bool								parsePacket				();
	string								toString				();
	unsigned int						getMinProtocolSize		();

	MAC_ADDR							getSourceMac			();
	MAC_ADDR							getDestMac				();
	unsigned short						getType					();

	void								setSourceMac			(MAC_ADDR mac);
	void								setDestMac				(MAC_ADDR mac);
	void								setType					(unsigned short tp);	
	
private:

	ETHERNET_HEADER						header;

};

#endif // __ETHERNET_HEADER_H

