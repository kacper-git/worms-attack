#include "RemoteMessagingSystem.h"
#include "base/message/MessagingSystem.h"

//<begin register remote messages-------------->

/* messages from attack detection */
REMOTE_MESSAGING_REGISTER 	(MessageAggregateIntervalValues)
REMOTE_MESSAGING_REGISTER 	(MessageLastAnomalyType)
REMOTE_MESSAGING_REGISTER 	(MessageLastSuspiciousAggregate)
REMOTE_MESSAGING_REGISTER 	(MessageAggregateWatchValues)
REMOTE_MESSAGING_REGISTER 	(MessageAddressDistribution)

/* messages from sampling */
// no messages in sampling

/* messages from utility */
REMOTE_MESSAGING_REGISTER 	(MessageAlert)
REMOTE_MESSAGING_REGISTER 	(MessageTimer)

//<end register remote messages------------------>


RemoteMessagingSystem::RemoteMessagingSystem (MessagingSystem* system, DistackInfo* info)
	: m_messagingSystem( system ), m_commSystem( NULL ), distackInfo( info) {

	//
	// create the communication system of choice
	//

	string remoteMessaging = Configuration::instance(distackInfo)->getRemoteMessaging ();

#ifdef OMNET_SIMULATION
	if (remoteMessaging == "OMNET_TCP")
		m_commSystem = new RemoteCommSystemOmnetTcp( distackInfo );
	else if (remoteMessaging == "OMNET_PATH")
		m_commSystem = new RemoteCommSystemOmnetPathbased( distackInfo );
	else if (remoteMessaging == "OMNET_RING")
		m_commSystem = new RemoteCommSystemOmnetRing( distackInfo );
	else
		m_commSystem = new RemoteCommSystemNone( distackInfo ); // default case: no comm
#else
	if (remoteMessaging == "TCP_SOCKET")
		m_commSystem = new RemoteCommSystemTcpSocket( distackInfo );
	else if (remoteMessaging == "GIST")
		m_commSystem = new RemoteCommSystemGist( distackInfo );
	else
		m_commSystem = new RemoteCommSystemNone( distackInfo ); // default case: no comm
#endif // OMNET_SIMULATION

	if (m_commSystem != NULL) {
		m_commSystem->setMessagingSystem (this);
		logging_debug( "running remote messaging system: " + m_commSystem->getName());
	} else {
		logging_warn( "no remote messaging system created. Remote messaging will fail!");
	}
}

RemoteMessagingSystem::~RemoteMessagingSystem ()
{
	if (m_commSystem != NULL)
		delete m_commSystem;
}

void RemoteMessagingSystem::sendMessage (Message* msg, MessagingNode::SEND_OPTIONS options)
{
	if (msg == NULL) return;
	if (m_commSystem == NULL) return;

	assert ((options.remoteMode & MessagingNode::SEND_REMOTE_MODE_REMOTE) == MessagingNode::SEND_REMOTE_MODE_REMOTE);

	//
	// serialize the object into a string
	//

	string data = serialize (msg);

#ifdef _DEBUG
	Message* testMsg = deserialize (data);

	assert (testMsg->getKind() == msg->getKind());
	assert (testMsg->getType() == msg->getType());

	delete testMsg;
#endif

	//
	// prepend the header and send out 
	// the string buffer over the network
	//

	DISTACK_REMOTE_DATA	sendData ((unsigned long)data.length());
	memcpy (sendData.data, (unsigned char*)data.c_str(), sendData.len);

	m_commSystem->write (sendData, options);
	sendData.destroy	();
}

void RemoteMessagingSystem::reveiveMessage (Message* msg)
{
	if (msg == NULL) return;
	assert (m_messagingSystem != NULL);

	//
	// put the message into the MessagingSystem queue 
	// it will then be processed asyncronously from the consumer thread
	//

	msg->m_fromRemote = true;

	boost::mutex::scoped_lock scopedLock (m_messagingSystem->m_queueMutex);
	MessagingNode::SEND_OPTIONS options = MessagingNode::SEND_OPTIONS::createLocalAsync();
	m_messagingSystem->m_queue.push (MessagingSystem::MESSAGE_OPTIONS_PAIR(msg, options));
}

void RemoteMessagingSystem::receiveBytes (DISTACK_REMOTE_DATA data)
{
	string stringdata = "";

	unsigned char* pnt = data.data;
	for (unsigned long i=0; i<data.len; i++, pnt++)
		stringdata += *pnt;
		
	data.destroy ();
	
	Message* msg = deserialize (stringdata);

	if (msg != NULL)
		reveiveMessage (msg);
}

string RemoteMessagingSystem::serialize (Message* msg)
{

	stringstream archiveStream (ios_base::binary | ios_base::out);
	{ // the brackets are important, otherwise the closing xml-tag is not written

#ifdef REMOTE_XML
// 		Output serialized message into xml file instead of remote message (for debugging purposes):
// 		ofstream archiveStream ("./distack_xml_output", ios_base::binary | ios_base::out);
// 		boost::archive::xml_oarchive	outputArchive (archiveStream);
	
		boost::archive::xml_oarchive outputArchive( archiveStream );
#else
		boost::archive::binary_oarchive outputArchive( archiveStream );
#endif //REMOTE_XML

	    outputArchive & msg;
	}
	
	string data = archiveStream.str();
	return data;
}

Message* RemoteMessagingSystem::deserialize (string data)
{
	stringstream archivStream (data, ios_base::binary | ios_base::in);
#ifdef REMOTE_XML
	boost::archive::xml_iarchive inputArchive( archivStream );
#else
	boost::archive::binary_iarchive inputArchive( archivStream );
#endif

	Message* msg = NULL;
	inputArchive >> msg;

	return msg;
}

RemoteCommSystem* RemoteMessagingSystem::getCommSystem ()
{
	return m_commSystem;
}

//#pragma warning (disable : 4996)
//string RemoteMessagingSystem::serialize (Message* msg)
//{
//	stringbuf outputStream;
//	
//	{
//		ostream								archiveStream (&outputStream); 
//		boost::iostreams::filtering_ostream filteredOutputStream;
//    
//		filteredOutputStream.push	(boost::iostreams::zlib_compressor (boost::iostreams::zlib_params()));
//		filteredOutputStream.push	(archiveStream);
//
//		boost::archive::binary_oarchive archive (filteredOutputStream);
//
//		archive << (const Message)(*msg);
//	}
//	
//	string data	= outputStream.str	();
//	return data;
//}
//#pragma warning (default : 4996)

//string RemoteMessagingSystem::compressString (string data)
//{
//	unsigned long inlen  = (unsigned long)data.length ();
//	unsigned long outlen = inlen * 2 + 12; // Upon entry, destLen is the total size of the destination buffer, which must be at least 0.1% larger than sourceLen plus 12 bytes. 
//
//	unsigned char* src = (unsigned char*) malloc (inlen);
//	unsigned char* dst = (unsigned char*) malloc (outlen);
//
//	memcpy (src, data.c_str(),inlen);
//#ifdef _DEBUG
//	memset (dst, 0, outlen);
//#endif
//
//	int ret = compress (dst, &outlen, src, inlen);
//	assert (ret == Z_OK);
//
//	string			retData = "";
//	unsigned char*	pnt		= dst;
//
//	for (unsigned long i=0; i<outlen; i++, pnt++)
//		retData += *pnt;
//
//	free (src);
//	free (dst);
//
//	return retData;
//}
//
//string RemoteMessagingSystem::decompressString (string data)
//{
//	unsigned long inlen  = (unsigned long)data.length ();
//	unsigned long outlen = inlen * 2 + 12; // Upon entry, destLen is the total size of the destination buffer, which must be at least 0.1% larger than sourceLen plus 12 bytes. 
//
//	unsigned char* src = (unsigned char*) malloc (inlen);
//	unsigned char* dst = (unsigned char*) malloc (outlen);
//
//	memcpy (src, data.c_str(),inlen);
//#ifdef _DEBUG
//	memset (dst, 0, outlen);
//#endif
//
//	int ret = compress (dst, &outlen, src, inlen);
//	assert (ret == Z_OK);
//
//	string			retData = "";
//	unsigned char*	pnt		= dst;
//
//	for (unsigned long i=0; i<outlen; i++, pnt++)
//		retData += *pnt;
//
//	free (src);
//	free (dst);
//
//	return retData;
//}
