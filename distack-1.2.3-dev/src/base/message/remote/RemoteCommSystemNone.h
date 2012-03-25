#ifndef __REMOTE_COMM_SYSTEM_NONE_H
#define __REMOTE_COMM_SYSTEM_NONE_H

#include "base/message/remote/RemoteCommSystem.h"

class RemoteCommSystemNone : public RemoteCommSystem {
public:
	RemoteCommSystemNone(DistackInfo* info);
	~RemoteCommSystemNone();

	bool write( DISTACK_REMOTE_DATA data, MessagingNode::SEND_OPTIONS options );

#ifdef OMNET_SIMULATION
	void handleMessage(cPacket* msg);
	void init(int stage);
#endif
};

#endif // __REMOTE_COMM_SYSTEM_NONE_H
