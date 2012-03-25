#ifndef __FRAME_H
#define __FRAME_H

#include "EthernetPacket.h"
#include "IpPacket.h"
#include <sstream>

class DistackInfo;

using std::ostringstream;

class Frame{
public:
	Frame(void);
	~Frame(void);

	void buildFrame(DistackInfo* info);
	unsigned int getSize();

	typedef enum _LINK_TYPE {
		LINK_UNKNOWN	= 0,	
		LINK_ETHERNET	= 1,
		LINK_RAWIP	= 2,
	} LINK_TYPE;

	#pragma pack (1)
	typedef struct _TIME_VAL {
		long tv_sec;  
		long tv_usec;

		_TIME_VAL (long sec = 0, long usec = 0) {
			tv_sec  = sec;
			tv_usec = usec;
		}

		string toString () {
			ostringstream out;
			out << tv_sec << "sec " << tv_usec << "microsec";
			return out.str ();
		}
	} TIME_VAL, *PTIME_VAL;
	#pragma pack ()

	static LINK_TYPE nettype;

	TIME_VAL timestamp;
	unsigned long capturelength;
	unsigned long packetlength;

	Packet* payloadpacket;
	string toString();

	void parsePackets();

private:
	DistackInfo* distackInfo;

};

#endif // __FRAME_H
