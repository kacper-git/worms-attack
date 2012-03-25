#include "NetworkInterfacePcap.h"

NetworkInterfacePcap::NetworkInterfacePcap (DistackInfo* info, string iface, bool promisc, unsigned int frameCaptureLen)
	: NetworkInterface( info, iface, NetworkInterface::CAPTURE_TYPE_ONLINE, promisc, frameCaptureLen ),
	m_handle( NULL ), m_lastPacketArrival( 0, 0 ), m_allFrames( 0 ),
	m_delayedFrames( 0 ), m_milliDelay( 0 ){
}

NetworkInterfacePcap::NetworkInterfacePcap (DistackInfo* info, string file, double replayspeedup)
:	NetworkInterface( info, file, NetworkInterface::CAPTURE_TYPE_OFFLINE, true, (unsigned int)pow (2.0, 16) ),
	m_handle( NULL ), m_lastPacketArrival( 0, 0 ), m_replaySpeedup( replayspeedup ),
	m_lastTimestamp( 0 ), m_allFrames( 0 ), m_delayedFrames( 0 ), m_milliDelay( 0 ){
	if (m_replaySpeedup <= 0) {
                std::cout << "invalid replay speedup. setting speedup to 1.0" << std::endl;	
		m_replaySpeedup = 1.0;
	}
}

NetworkInterfacePcap::~NetworkInterfacePcap ()
{
	//
	// close the interface
	//

	if (getState() == NetworkInterface::INTERFACE_STATE_OPEN)
		close ();

	//
	// print out time-speed statistics for offline replay
	//

	if (getCaptureType() == NetworkInterface::CAPTURE_TYPE_OFFLINE) {
		
		unsigned short	percentDelayed	= 0;
		unsigned long	averageDelay	= 0;

		if (m_allFrames > 0)
			percentDelayed = static_cast<unsigned short>(((double)m_delayedFrames / (double)m_allFrames) * 100.0);
		
		if (m_delayedFrames > 0)
			averageDelay = (unsigned long) (m_milliDelay / m_delayedFrames);
		
		logging_info( "offline replay statistics: " + Helper::ultos(percentDelayed) + "% frames delayed, average delay " +  Helper::ultos(averageDelay) + "ms");

	} // if (getCaptureType() == NetworkInterface::CAPTURE_TYPE_OFFLINE)
}

bool NetworkInterfacePcap::openOffline ()
{
	char errbuf	[PCAP_ERRBUF_SIZE];
	m_handle = pcap_open_offline (getName().c_str(), errbuf);

	if (m_handle == NULL)
		logging_error( "opening offline-interface " + getName() + " failed: " + errbuf);

	return (m_handle != NULL);
}

bool NetworkInterfacePcap::openOnline ()
{
	pcap_if_t*	ifaces	= NULL;
	char		errbuf	[PCAP_ERRBUF_SIZE];
	int			ret		= -1;

	ret = pcap_findalldevs (&ifaces, errbuf);

	if (ret != 0) {
		logging_error( "getting devices list from pcap failed: " + string (errbuf));
		return false;
	}

	//
	// find the correct interface 
	//

	pcap_if_t* i = NULL;

	for (i = ifaces; i != NULL; i = i->next) {
		if (i == NULL || i->name == NULL) continue;

		string name = string (i->name);

		if (getName().compare (name) == 0) {
			if (i->description != NULL)	
				setDescription (i->description);		
			break;
		}

	} // for (pcap_if_t* i = ifaces; i != NULL, i = i->next) 

	//
	// did we find the correct interface?
	//

	if (i == NULL) {
		logging_error( "interface " +  getName() + " not found");
		logging_error( "\tavailable interfaces:");
		
		for (i = ifaces; i != NULL; i = i->next) {
			string name  = i->name;
			string descr = (i->description != NULL ? i->description : "");

			logging_error( "\t\t" + name + " (" + descr + ")"); 
		}
	}

	//
	// don't need the device list anymore
	//

	pcap_freealldevs (ifaces);

	if (i == NULL) 
		return false;

	//
	// open the interface
	//
	
	logging_debug( "opening interface " + getName() + " (" + getDescription() + ")");

	m_handle = pcap_open_live (
		getName().c_str (),		// interface name
		getFrameCaptureLength (),	// capture all frame content
		(getPromisc() ? 1 : 0),		// capture in promiscuous mode
		500,				// read timeout. without this we would never return from pcap_next_ex when there are no packets	coming
		errbuf				// error buffer string
		);

	if (m_handle == NULL)
		logging_error( "opening online-interface " + getName() + " failed: " + errbuf);

	return (m_handle != NULL);
}

bool NetworkInterfacePcap::open ()
{
	bool ret = (getCaptureType() == NetworkInterface::CAPTURE_TYPE_ONLINE ? openOnline() : openOffline());
	if (! ret) return false;

	if (m_handle == NULL) {
		logging_error( "failed opening " + getName() + " using libpcap");
		return false;
	}

	//
	// check for correct link layer type
	// we currently support 
	// DLT_EN10MB (Ethernet) and 
	// DLT_RAW (we suppose first protocol is IPv4)
	//

	switch (pcap_datalink(m_handle)) {
		case DLT_EN10MB:	Frame::nettype = Frame::LINK_ETHERNET;	break;
		case DLT_RAW:		Frame::nettype = Frame::LINK_RAWIP;		break;
		default:			Frame::nettype = Frame::LINK_UNKNOWN;	
							logging_error( "invalid pcap link type");	return false;
	}

	//
	// interface opened successfully!
	//

	setState (INTERFACE_STATE_OPEN);
	return true;
}

bool NetworkInterfacePcap::close ()
{
	if( getState() == INTERFACE_STATE_CLOSE )
		return false;

	if( getCaptureType() == NetworkInterface::CAPTURE_TYPE_OFFLINE )
		m_offlineSleeper.interrupt();

	if( m_handle != NULL ){
		pcap_close( m_handle );
		m_handle = NULL;
	}

	setState( INTERFACE_STATE_CLOSE );
	return true;
}

Frame* NetworkInterfacePcap::read ()
{
	if (m_handle == NULL) return NULL;

	//
	// read the next packet from the pcap source
	//

	int						res;
	struct pcap_pkthdr*		header;
	const unsigned char*	data;

	res = pcap_next_ex (m_handle, &header, &data);
	
	if (res != 1) {
		
		switch (res) {
			case -2:	// eof reached. this should only happen on offline dumps
						logging_debug( "pcap end-of-file on " + getName());
						break;
			case 0:		// timeout. don't need to log this
						break;
			case -1:	// an error occured, fall through
			default:	// unknown error
						logging_error( "error reading from pcap on interface " + getName());
						break;
		}
		
		return NULL;
	}

	if (header->caplen == 0 || header->caplen > 65535)
		return NULL;

	//
	// create the frame and set its properties
	//

	Frame* frame = PacketFactory::instance()->createFrame (distackInfo);
	assert (frame->payloadpacket != NULL);

	frame->timestamp.tv_sec		= header->ts.tv_sec;	// different timeval struct. otherwise we either depend on 
	frame->timestamp.tv_usec	= header->ts.tv_usec;	// pcap or winsock because of one struct and have to change this in the Frame.h file
	frame->capturelength		= header->caplen;
	frame->packetlength			= header->len;

	frame->payloadpacket->setSize (frame->capturelength);
	memcpy (frame->payloadpacket->getBuffer(), data, frame->capturelength);
	
	if (getCaptureType() == NetworkInterface::CAPTURE_TYPE_OFFLINE) {
		
		//
		// if we are gettings frames from an offline source
		// wait until the timespan to the frame before has elapsed
		// so that the frame timing is correct. Because we can not
		// wait microseconds we cast the microseconds to milliseconds.
		// Further we have to take note of the process time that elapsed 
		// since last call of the read function. This has to be substracted
		// from the difference between the frame timestamps. If we have 
		// set up a speedup for replaying files, we take this into account, too.
		// 

		if (m_lastPacketArrival.tv_sec != 0 && m_lastPacketArrival.tv_usec != 0) {	

			//
			// do _not_ change to unsigned! usecwait can be negative
			// and will be handled correctly if negative!
			long secwait	= frame->timestamp.tv_sec  - m_lastPacketArrival.tv_sec;
			long usecwait	= frame->timestamp.tv_usec - m_lastPacketArrival.tv_usec;
		
			long			millis;
			unsigned long	currentTimeStamp = Helper::getElapsedMillis ();
			unsigned long	elapsedMillis = currentTimeStamp - m_lastTimestamp;

			// conversion of total time into milliseconds
			millis	= (secwait * 1000 + usecwait / 1000);

			// speedup factor
			millis  = long((double)millis / m_replaySpeedup);
			
			// elapsed process time
			if (elapsedMillis > 0)	millis -= elapsedMillis;

			// sleep the resulting timespan
			if (millis > 0)	{
				m_offlineSleeper.sleep (millis);	
			} else {
				m_delayedFrames++;
				m_milliDelay += (-millis);
			}

			m_lastTimestamp = Helper::getElapsedMillis ();
		
		} // if (m_lastPacketArrival.tv_sec != 0 && m_lastPacketArrival.tv_usec != 0)

		m_lastPacketArrival = frame->timestamp;

	} // if (getCaptureType() == NetworkInterface::CAPTURE_TYPE_OFFLINE)

	m_allFrames++;

	return frame;
}
