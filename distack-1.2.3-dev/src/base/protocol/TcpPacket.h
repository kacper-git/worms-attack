#ifndef __TCP_PACKET_H
#define __TCP_PACKET_H

#include "Packet.h"
#include "IpPacket.h"
#include "Ipv6Packet.h"
#include "PayloadPacket.h"

//
// masks to fetch combined values
// 

#define TCP_HEADER_LEN(x)		(((x &	0xF000) >> 12	) *   4	)
#define TCP_HEADER_FLAGS(x)		((x &	0x3F			)		)

//
// TCP header len without options
//

#define TCP_HEADER_NO_OPTIONS_LEN	20

//
// TCP header 
//

#pragma pack (1)
typedef struct _TCP_HEADER {
	unsigned short	sourceport;		// source port. configuration item TcpSourceport
	unsigned short	destport;		// destination port. configuration item TcpDestport 
	unsigned long	sequencenum;	// sequence number. configuration item TcpSeqnum 
	unsigned long	acknum;			// acknowledgement number. configuration item TcpAcknum 
	unsigned short	headerlen_flags;//header length 4 bit, 6 bit reserved, 6 bit flags. configuration item TcpFlags. none for header length
	unsigned short	windowsize;		// window size. configuration item TcpWindowsize
	unsigned short	checksum;		// checksum 
	unsigned short	urgentpointer;	// urgent pointer. configuration item TcpUrgentpnt 
} TCP_HEADER, *PTCP_HEADER;
#pragma pack ()

//
// TCP pseudo header, needed for checksumming
//

#pragma pack (1)
typedef struct _TCP_PSEUDO_HEADER {
	unsigned char	reserved;
	unsigned char	protocol;
	unsigned short	tcplength;
} TCP_PSEUDO_HEADER, *PTCP_PSEUDO_HEADER;

typedef struct _TCP_IP4_PSEUDO_HEADER : public TCP_PSEUDO_HEADER{
	IP_ADDR			sourceip;
	IP_ADDR			destip;
} TCP_IP4_PSEUDO_HEADER, *PTCP_IP4_PSEUDO_HEADER;

typedef struct _TCP_IP6_PSEUDO_HEADER : public TCP_PSEUDO_HEADER{
	IPV6_ADDR		sourceip;
	IPV6_ADDR		destip;
} TCP_IP6_PSEUDO_HEADER, *PTCP_IP6_PSEUDO_HEADER;
#pragma pack ()

//
// TCP packet class
//

class TcpPacket : public Packet
{
public:
	TcpPacket(void);
	~TcpPacket(void);

	bool					parsePacket				();
	string					toString				();		
	unsigned int			getMinProtocolSize		();

	unsigned short			getSourceport			();		
	unsigned short			getDestport				();		
	unsigned long			getSequencenum			();		
	unsigned long			getAcknum				();		
	unsigned short			getHeaderlength			();		
	unsigned short			getFlags				();		
	unsigned short			getWindowsize			();			
	unsigned short			getChecksum				();		
	unsigned short			getUrgentpointer		();		
	Packet::PAYLOAD_BUFFER	getOptions				();

	void					setSourceport			(unsigned short		sourcep	);		
	void					setDestport				(unsigned short		destp	);		
	void					setSequencenum			(unsigned long		seqnum	);		
	void					setAcknum				(unsigned long		aknum	);		
	void					setHeaderlength			(unsigned short		hdlen	);		
	void					setFlags				(unsigned short		flgs	);		
	void					setWindowsize			(unsigned short		wsize	);			
	void					setChecksum				(unsigned short		cksum	);		
	void					setUrgentpointer		(unsigned short		urgpnt	);	
	void					setOptions				(unsigned char* buf, int len);

	void					setIpAddresses			(IP_ADDR source, IP_ADDR dest);
	void					setIpAddresses			(IPV6_ADDR source, IPV6_ADDR dest);

	typedef enum _TCP_FLAG {
		TCP_FLAG_FIN =   1,
		TCP_FLAG_SYN =   2,
		TCP_FLAG_RST =   4,
		TCP_FLAG_PSH =   8,
		TCP_FLAG_ACK =  16,
		TCP_FLAG_URG =  32,
		TCP_FLAG_ECN =  64,
		TCP_FLAG_CWR = 128,
	} TCP_FLAG;

	bool					isFlagSet				(TCP_FLAG flag);
	void					setFlag					(TCP_FLAG flag, bool set = true);

private:
	TCP_HEADER				header;

	// the tcp options
	Packet::PAYLOAD_BUFFER	options;	// configuration item TcpOptions

	// the source and dest IP, we need this to calculate the checksum
	IP_ADDR					sourceip, destip;
	IPV6_ADDR				sourceip6, destip6;
	Packet::PROTOCOL		ipProtocol;

	// calculate the TCP checksum
	static unsigned short	checksum				(PTCP_HEADER header, void* sourceip, void* destip, Packet::PROTOCOL ipproto, unsigned char* options, int optionslen, unsigned char* data, int datalen);
};

#endif // __TCP_PACKET_H
