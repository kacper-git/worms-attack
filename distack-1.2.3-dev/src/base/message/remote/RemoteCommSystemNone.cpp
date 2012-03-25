#include "RemoteCommSystemNone.h"

/**
  * Constructs a new RemoteCommSystemNone
  * This specific CommSystem discards all messages it recieves
  * Only used with Omnet
  * @param info the DistackInfo reference for this Distack instance
  */
RemoteCommSystemNone::RemoteCommSystemNone (DistackInfo* info)
:	RemoteCommSystem	("none", "remote communication system that discards any message passed to it", info){
}

#ifdef OMNET_SIMULATION
/**
  * called upon complete initialization of the distack module
  * In this case does nothing
  */
void RemoteCommSystemNone::init (int stage)
{
}

/**
  * handles all Omnet messages arriving at the distack module.
  * In this case all messages are instantly discarded, as no communication is required
  * @param msg the Omnet message
  */
void RemoteCommSystemNone::handleMessage (cPacket* msg)
{
	delete msg;
}
#endif

/**
  * Called by the RemoteMessagingSystem if the is data to send remotely
  * In this case true is always returned, to prevent the RemoteMessagingSystem reporting RemoteComm errors
  * @param data the DISTACK_REMOTE_DATA construct representing the data to send
  * @param options the sendoptions
  * @return always true
  */
bool RemoteCommSystemNone::write (DISTACK_REMOTE_DATA data, MessagingNode::SEND_OPTIONS options)
{
	return true;
}

/**
  * Destructor
  */
RemoteCommSystemNone::~RemoteCommSystemNone ()
{
}
