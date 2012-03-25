#ifndef __NETWORK_MANAGER_H
#define __NETWORK_MANAGER_H

#include "base/network/FrameBuffer.h"
#include "base/network/NetworkInterface.h"
#include "base/configuration/Configuration.h"

#ifdef OMNET_SIMULATION
	#include "base/network/omnetpp/NetworkInterfaceOmnetpp.h"
#else
	#include "base/network/libpcap/NetworkInterfacePcap.h"
#endif // OMNET_SIMULATION

class NetworkManager {
public:
						NetworkManager			(DistackInfo* info);
						~NetworkManager			();
	
	bool				startup					();
	bool				shutdown				();
	FrameBuffer*		getFrameSource			();
	NetworkInterface*	getNetworkInterface		();

private:

	DistackInfo*		distackInfo;
	NetworkInterface*	m_interface;
	FrameBuffer*		m_frameBuffer;

};

#endif // __NETWORK_MANAGER_H
