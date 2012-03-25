#ifndef __NETWORK_INTERFACE_PCAP_H
#define __NETWORK_INTERFACE_PCAP_H

#include "base/network/NetworkInterface.h"
#include "base/common/InterruptableSleeper.h"
#include "base/common/Log.h"
#include <pcap.h>

class NetworkInterfacePcap : public NetworkInterface {
public:
	NetworkInterfacePcap(
		DistackInfo* info,
		string iface, 
		bool promisc, 
		unsigned int frameCaptureLen
		);
		
	NetworkInterfacePcap( DistackInfo* info, string file, double replayspeedup );
	~NetworkInterfacePcap();

	bool open();
	bool close();
	Frame* read();

private:
	pcap_t* m_handle;

	bool openOnline();
	bool openOffline();

	//
	// these items are needed for offline trace processing
	//

	Frame::TIME_VAL m_lastPacketArrival;
	double m_replaySpeedup;
	unsigned long m_lastTimestamp;
	InterruptableSleeper m_offlineSleeper;

	//
	// statistics for offline replay speed
	// 

	unsigned long m_allFrames;
	unsigned long m_delayedFrames;
	unsigned long long m_milliDelay;
};

#endif // __NETWORK_INTERFACE_PCAP_H
