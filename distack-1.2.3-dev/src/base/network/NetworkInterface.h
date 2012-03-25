#ifndef __NETWORK_INTERFACE_H
#define __NETWORK_INTERFACE_H

#include <cmath>
#include "base/protocol/Frame.h"
#include "base/protocol/PacketFactory.h"
#include "base/common/Log.h"
#include "base/common/DistackInfo.h"

class FrameBuffer;

class NetworkInterface{
public:
	typedef enum _CAPTURE_TYPE {
		CAPTURE_TYPE_ONLINE,
		CAPTURE_TYPE_OFFLINE,
	} CAPTURE_TYPE;

	NetworkInterface(
		DistackInfo* info,
		string name, 
		CAPTURE_TYPE type, 
		bool promisc, 
		unsigned int frameCaptureLen
		);
	
	virtual ~NetworkInterface();

	virtual bool open() = 0;
	virtual bool close() = 0;
	virtual Frame* read() = 0;

	string getName();
	string getDescription();

	typedef enum _INTERFACE_STATE {
		INTERFACE_STATE_UNKNOWN,
		INTERFACE_STATE_OPEN,
		INTERFACE_STATE_CLOSE,
	} INTERFACE_STATE; 

	INTERFACE_STATE getState();
	string getStateName( INTERFACE_STATE state );
	CAPTURE_TYPE getCaptureType ();

protected:
	void setCaptureType( CAPTURE_TYPE type );
	void setState( INTERFACE_STATE state );
	void setDescription( string description );
	bool getPromisc();
	unsigned int getFrameCaptureLength();
	
	DistackInfo* distackInfo;

private:
	CAPTURE_TYPE m_captureType;
	INTERFACE_STATE m_state;
	bool m_promisc;
	unsigned int m_frameCaptureLen;
	string m_name;
	string m_description;
};

#endif // __NETWORK_INTERFACE_H
