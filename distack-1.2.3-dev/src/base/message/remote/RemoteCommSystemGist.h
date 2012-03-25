#ifndef __REMOTE_COMM_SYSTEM_GIST_H
#define __REMOTE_COMM_SYSTEM_GIST_H

#include "base/message/remote/RemoteCommSystem.h"
//#include "ntlp_starter.h"

class RemoteCommSystemGist : public RemoteCommSystem {
public:
					RemoteCommSystemGist			(DistackInfo* info);
	virtual			~RemoteCommSystemGist			();

	bool			write							(DISTACK_REMOTE_DATA data, MessagingNode::SEND_OPTIONS options);

private:

};

#endif // __REMOTE_COMM_SYSTEM_GIST_H
