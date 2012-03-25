#include "RemoteCommSystemGist.h"

RemoteCommSystemGist::RemoteCommSystemGist (DistackInfo* info)
:	RemoteCommSystem ("GIST", "remote communication system using the GIST-ka library", info)
{
	//
	// dynamically load the GIST library. this enables us not to link
	// against it. and this way the communication system can be selected
	// using the configuration and is not compile-time dependend
	//

	//
	// configure the ntlp stuff. use all the std parameters
	//

	//NTLPStarterParam ntlppar;
	//
	//ThreadStarter<ntlp::NTLPStarter,NTLPStarterParam> ntlpthread (1, ntlppar);
 //   ntlpthread.start_processing();
 //   sleep(4);
}

RemoteCommSystemGist::~RemoteCommSystemGist ()
{
}

bool RemoteCommSystemGist::write (DISTACK_REMOTE_DATA data, MessagingNode::SEND_OPTIONS options)
{
	return false;
}
