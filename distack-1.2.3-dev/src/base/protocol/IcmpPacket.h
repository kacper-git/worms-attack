#ifndef __ICMP_PACKET_H
#define __ICMP_PACKET_H

#include "Packet.h"
#include "PayloadPacket.h"

//
// ICMP header
//

#pragma pack (1)
typedef struct _ICMP_HEADER {
	unsigned char	type;			// type of message. configuration item IcmpType
	unsigned char	code;			// type sub code. configuration item IcmpCode 
	unsigned short	checksum;		// checksum
	unsigned long	misc;			// depending on type and code. configuration item IcmpMisc
} ICMP_HEADER, *PICMP_HEADER;
#pragma pack ()

//
// ICMP packet class
//

class IcmpPacket : public Packet
{
public:
	IcmpPacket										(void);
	~IcmpPacket										(void);

	bool						parsePacket					();
	string						toString					();
	unsigned int				getMinProtocolSize		();

	unsigned char				getType						();
	unsigned char				getCode						();
	unsigned short				getChecksum					();
	//Packet::PAYLOAD_BUFFER		getData						();
	unsigned long				getMisc						();

	void						setType						(unsigned char tp);
	void						setCode						(unsigned char cd);
	void						setChecksum					(unsigned short chk);
	//void						setData						(Packet::PAYLOAD_BUFFER buf);
	void						setMisc						(unsigned long msc);

	typedef enum _ICMP_TYPE { // taken from http://www.networksorcery.com/enp/protocol/icmp.htm
		ICMP_TYPE_ECHO_REPLY					=  0,
		ICMP_TYPE_DEST_UNREACHABLE				=  3,
		ICMP_TYPE_SOURCE_QUENCH					=  4,
		ICMP_TYPE_REDIRECT						=  5,
		ICMP_TYPE_ALTERNATE_HOST_ADDR			=  6,
		ICMP_TYPE_ECHO_REQUEST					=  8,
		ICMP_TYPE_ROUTER_ADVERISEMENT			=  9,
		ICMP_TYPE_ROUTER_SOLICITATION			= 10,
		ICMP_TYPE_TIME_EXCEEDED					= 11,
		ICMP_TYPE_PARAM_PROBLEM					= 12,
		ICMP_TYPE_TIMESTAMP_REQUEST				= 13,
		ICMP_TYPE_TIMESTAMP_REPLY				= 14,
		ICMP_TYPE_INFORMATION_REQUEST			= 15,
		ICMP_TYPE_INFORMATION_REPLY				= 16,
		ICMP_TYPE_ADDRESS_MASK_REQUEST			= 17,
		ICMP_TYPE_ADDRESS_MASK_REPLY			= 18,
		ICMP_TYPE_TRACEROUTE					= 30,
		ICMP_TYPE_CONVERSION_ERROR				= 31,
		ICMP_TYPE_MOBILE_HOST_REDIRECT			= 32,
		ICMP_TYPE_IPV6_WHERE_ARE_YOU			= 33,
		ICMP_TYPE_IPV6_HERE_I_AM				= 34,
		ICMP_TYPE_MOBILE_REGISTRATION_REQUEST	= 35,
		ICMP_TYPE_MOBILE_REGISTRATION_REPLY		= 36,
		ICMP_TYPE_DOMAIN_NAME_REQUEST			= 37,
		ICMP_TYPE_DOMAIN_NAME_REPLY				= 38,
		ICMP_TYPE_SKIP_ALGO_DISCOVERY_PROTO		= 39,
		ICMP_TYPE_PHOTURIS						= 40,
	} ICMP_TYPE;

	typedef enum _ICMP_DEST_UNREACHABLE_CODE {
		ICMP_DEST_UNREACHABLE_CODE_HOST_UNREACHABLE = 1,
		ICMP_DEST_UNREACHABLE_CODE_PORT_UNREACHABLE = 3,
	} ICMP_DEST_UNREACHABLE_CODE;

private:

	ICMP_HEADER			header;

	static unsigned short checksum (PICMP_HEADER header, unsigned char* data, int datalen);

};

#endif // __ICMP_PACKET_H
