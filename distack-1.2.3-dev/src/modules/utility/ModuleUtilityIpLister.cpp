#include "ModuleUtilityIpLister.h"

MODULE_INTERFACE(ModuleUtilityIpLister);

const string ModuleUtilityIpLister::PARAM_OutFilename	= "OutFilename";
const string ModuleUtilityIpLister::PARAM_SubnetMasking = "SubnetMasking";

ModuleUtilityIpLister::ModuleUtilityIpLister ()
{
}

ModuleUtilityIpLister::~ModuleUtilityIpLister	()
{
	IP_COUNTER_MAP_ITERATOR i	 = m_counterMap.begin ();
	IP_COUNTER_MAP_ITERATOR iend = m_counterMap.end   ();

	for ( ; i != iend; i++) {
		
		IP_ADDR		 addr  = i->first;
		unsigned int count = i->second;

		m_outFile << addr.toString() << "\t" << count << std::endl;
	}

	m_outFile.close ();
}

bool ModuleUtilityIpLister::configure (ModuleConfiguration& configList)
{
	bool good = true;
	good &= configList.has (PARAM_OutFilename);
	good &= configList.has (PARAM_SubnetMasking);
	
	if (good) {
#ifdef OMNET_SIMULATION
		string outFileName(configList.get(PARAM_OutFilename) + "_" + distackInfo->modulePath);
#else
		string outFileName(configList.get(PARAM_OutFilename));
#endif

		m_outFile.open (outFileName.c_str());
		good &= m_outFile.is_open ();
		good &= m_param_SubnetMasking.fromString (configList.get(PARAM_SubnetMasking));
	}

	return good;
}

bool ModuleUtilityIpLister::frameCall (Frame& frame)
{
	frame.parsePackets ();

	for (Packet* packet = frame.payloadpacket; packet != NULL; packet = packet->getNextPacket()) {
		Packet::PROTOCOL protocol = packet->getProtocol ();
		
		if (protocol == Packet::PROTO_IP) {
			IpPacket* ipPacket = (IpPacket*)packet;
			
			IP_ADDR source	= ipPacket->getSourceip () & m_param_SubnetMasking;
			IP_ADDR dest	= ipPacket->getDestip   () & m_param_SubnetMasking;

			{
				IP_COUNTER_MAP_ITERATOR item = m_counterMap.find (source);
				if (item == m_counterMap.end ()) m_counterMap.insert (IP_COUNTER_PAIR (source, 1));
				else							 item->second++;
			}

			{
				IP_COUNTER_MAP_ITERATOR item = m_counterMap.find (dest);
				if (item == m_counterMap.end ()) m_counterMap.insert (IP_COUNTER_PAIR (dest, 1));
				else							 item->second++;
			}

			break;
		}

	} // for (Packet* packet = frame.payloadpacket; packet != NULL; packet = packet->getNextPacket())

	return true;
}
