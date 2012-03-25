#ifndef __MPLS_PACKET_H
#define __MPLS_PACKET_H

#include "Packet.h"

//
// a MPLS header
//

#pragma pack (1)
typedef struct _MPLS_HEADER {
	unsigned int packet; // 20bit label, 3bit exp, 1bit S, 8bit TTL
} MPLS_HEADER, *PMPLS_HEADER  ;
#pragma pack ()

#define MPLS_LABEL(x) 		((x & 0xFFFFF800) >> 10)
#define MPLS_EXP(x) 		((x & 0x00000E00) >>  9)
#define MPLS_S(x) 			((x & 0x00000100) >>  8)
#define MPLS_TTL(x) 		((x & 0x000000FF)      )

//
// MplsPacket class representing a MPLS packet
//

class MplsPacket : public Packet
{
public:
							MplsPacket				(void);
							~MplsPacket				(void);

	bool					parsePacket				();
	string					toString				();
	unsigned int			getMinProtocolSize		();	

	unsigned int			getLabel				();		
	unsigned short			getExperimental			();		
	bool					getStack				();						
	unsigned short			getTtl					();		

	void					setLabel				(unsigned int label);	
	void					setExperimental			(unsigned short exp);	
	void					setStack				(bool stack);						
	void					setTtl					(unsigned short ttl);	
	
private:

	MPLS_HEADER				header;	

};

#endif // __MPLS_PACKET_H
