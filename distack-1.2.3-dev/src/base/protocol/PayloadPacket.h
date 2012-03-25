#ifndef __PAYLOAD_PACKET_H
#define __PAYLOAD_PACKET_H

#include "Packet.h"
#include <cassert>

class PayloadPacket : public Packet
{
public:
									PayloadPacket			();
									~PayloadPacket			(void);

	bool							parsePacket				();
	string							toString				();
	unsigned int					getMinProtocolSize		();

	Packet::PAYLOAD_BUFFER			getData					();
	void							setData					(unsigned char* buf, int len);

	unsigned int					getPseudoLength			();

private:

	Packet::PAYLOAD_BUFFER			data;	// configuration item PayloadPacketData

};

#endif // __PAYLOAD_PACKET_H
