#ifndef __ARP_PACKET_H
#define __ARP_PACKET_H

#include "Packet.h"
#include "IpPacket.h"
#include "EthernetPacket.h"

//
// ARP header
//

#pragma pack (1)
typedef struct _ARP_HEADER {
	unsigned short	hardwaretype;	// 0x1 for ethernet. configuration item ArpHardwaretp
	unsigned short	protocoltype;	// 0x800 for ip. configuration item ArpPrototp
	unsigned char	hwaddrlen;		// 0x6 for ethernet mac addressess. configuration item ArpHardwareaddrlen
	unsigned char 	protoaddrlen;	// 0x4 for ip addresses. configuration item ArpProtoaddrlen
	unsigned short	opcode;			// see defines below. configuration item ArpOpcode
	MAC_ADDR		sourcemac;		// configuration item ArpSourcemac
	IP_ADDR			sourceip;		// configuration item ArpSourceip
	MAC_ADDR		destmac;		// configuration item ArpDestmac
	IP_ADDR			destip;			// configuration item ArpDestip
} ARP_HEADER, *PARP_HEADER;
#pragma pack ()

//
// ARP opcodes
//

#define ARP_OPCODE_REQUEST		0x1
#define ARP_OPCODE_REPLY		0x2
#define ARP_OPCODE_REVREQUEST	0x3
#define ARP_OPCODE_REVREPLY		0x4

//
// ArpPacket class representing an arp packet
//

class ArpPacket : public Packet {
public:
							ArpPacket				();
							~ArpPacket				();	
		
	bool					parsePacket				();
	string					toString				();
	unsigned int			getMinProtocolSize		();
		
	unsigned short			getHardwaretype 		();	
	unsigned short			getProtocoltype			();
	unsigned char			getHardwareaddrlen		();
	unsigned char			getProtocoladdrlen		();
	unsigned short			getOpcode				();
	MAC_ADDR				getSourcemac			();
	IP_ADDR					getSourceip				();
	MAC_ADDR				getDestmac				();
	IP_ADDR					getDestip				();
	
	void					setHardwaretype 		(unsigned short hwtype		);	
	void					setProtocoltype			(unsigned short	prototype	);
	void					setHardwareaddrlen		(unsigned char 	hwlen		);
	void					setProtocoladdrlen		(unsigned char 	protolen	);
	void					setOpcode				(unsigned short	opcode		);
	void					setSourcemac			(MAC_ADDR 		sourcemac	);
	void					setSourceip				(IP_ADDR 		sourceip	);
	void					setDestmac				(MAC_ADDR 		destmac		);
	void					setDestip				(IP_ADDR 		destip		);
	
private:
		
	ARP_HEADER				header;

};

#endif // __ARP_PACKET_H
