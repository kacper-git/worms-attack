#include "ModuleCollectorAddressSpace.h"

MODULE_INTERFACE(ModuleCollectorAddressSpace);

const string ModuleCollectorAddressSpace::PARAM_RoutingTableFilename = "RoutingTableFilename";
const string ModuleCollectorAddressSpace::PARAM_TimerModule			 = "TimerModule";	
const string ModuleCollectorAddressSpace::PARAM_HistoryLength		 = "HistoryLength";

ModuleCollectorAddressSpace::ModuleCollectorAddressSpace ()
: m_currentCounterTree (NULL)
{
}

ModuleCollectorAddressSpace::~ModuleCollectorAddressSpace ()
{
}

void ModuleCollectorAddressSpace::receiveMessage (Message* msg)
{
	//
	// handle the address space distribution request message
	//

	if (msg->getType() == Message::MESSAGE_TYPE_ADDRESS_DISTRIBUTION && msg->isRequest())
			handleCollectionRequestMsg ();

	//
	// handle sync timer event message
	//

	if (msg->getType() == Message::MESSAGE_TYPE_TIMER) {
		handleTimerMsg ();
	}

}

void ModuleCollectorAddressSpace::handleCollectionRequestMsg ()
{
	boost::mutex::scoped_lock scopedLock (m_addressDistributionsMutex);
	
	//
	// create a new message and copy all the distributions
	// to the newly created message. As this is a queue
	// we have to circulate the messages, pop it out and push 
	// it in back again
	//

	MessageAddressDistribution* distMsg = new MessageAddressDistribution ();
	unsigned int items = (unsigned int) m_addressDistributions.size ();
	assert (items <= m_param_HistoryLength);

	for (unsigned int i=0; i<items; i++) {
		
		SubnetCounterTree* tree = m_addressDistributions.front ();
		m_addressDistributions.pop ();

		distMsg->addSubnetDistrib (tree->copy());
		
		m_addressDistributions.push (tree);

	} // for (int i=0; i<items; i++) 

	sendMessage (distMsg);
}

void ModuleCollectorAddressSpace::registerMessages ()
{
	//
	// register for the address distribution message
	// we will only look at request-kind message
	// and then send out the reply with the patricia stuff
	//

	subscribeMessage (Message::MESSAGE_TYPE_ADDRESS_DISTRIBUTION);

	//
	// register for the timer message which is our syncronization
	// object to run in sync with AggregateWatch module
	//

	subscribeMessage (Message::MESSAGE_TYPE_TIMER);
}

bool ModuleCollectorAddressSpace::configure (ModuleConfiguration& configList)
{
	bool good = true;

	good &= configList.has (PARAM_RoutingTableFilename);
	good &= configList.has (PARAM_TimerModule);
	good &= configList.has (PARAM_HistoryLength);

	if (good) {
		m_param_RoutingTableFilename = configList.get	  (PARAM_RoutingTableFilename);
		m_param_TimerModule			 = configList.get	  (PARAM_TimerModule);
		m_param_HistoryLength		 = configList.getLong (PARAM_HistoryLength);
	}

	//
	// get the routing table and init the address space counters
	//

	GenericRoutingTable::ROUTING_SOURCE source = (m_param_RoutingTableFilename.length() == 0			? 
														GenericRoutingTable::ROUTING_SOURCE_SYSTEM		: 
														GenericRoutingTable::ROUTING_SOURCE_FILE		);
	
#ifdef OMNET_SIMULATION
	GenericRoutingTable::ROUTING_TABLE table = GenericRoutingTable::getRoutingTable (omnetModule, source, m_param_RoutingTableFilename);
#else
	GenericRoutingTable::ROUTING_TABLE table = GenericRoutingTable::getRoutingTable (source, m_param_RoutingTableFilename);
#endif
	{
		boost::mutex::scoped_lock scopedLock (m_addressDistributionsMutex);
		m_subnetTemplate.clear ();

		GenericRoutingTable::ROUTING_TABLE_ITERATOR i	 = table.begin ();
		GenericRoutingTable::ROUTING_TABLE_ITERATOR iend = table.end   ();

		for ( ; i != iend; i++)
			m_subnetTemplate.addSubnet (i->addr, i->mask);
	}

	//
	// create the first and current subnet counter tree
	//

	{
		boost::mutex::scoped_lock lock (m_addressDistributionsMutex);
		m_currentCounterTree = m_subnetTemplate.copy ();
	}

	return good;
}

bool ModuleCollectorAddressSpace::frameCall	(Frame& frame)
{
	frame.parsePackets ();

	//
	// update the youngest address space distribution
	//

	for (Packet* packet = frame.payloadpacket; packet != NULL; packet = packet->getNextPacket()) {

		Packet::PROTOCOL protocol = packet->getProtocol ();
		
		if (protocol == Packet::PROTO_IP) {

			IpPacket* ipPacket = (IpPacket*)packet;
			
			boost::mutex::scoped_lock scopedLock (m_addressDistributionsMutex);
			assert (m_currentCounterTree != NULL);

			m_currentCounterTree->addCount (ipPacket->getSourceip (), SubnetCounterTree::COUNT_TYPE_SOURCE);
			m_currentCounterTree->addCount (ipPacket->getDestip   (), SubnetCounterTree::COUNT_TYPE_DEST  );
		
			break;
		}

	} // for (Packet* packet = frame.payloadpacket; packet != NULL; packet = packet->getNextPacket())

	//
	// don't drop any frames from channel processing
	//

	return true;
}

void ModuleCollectorAddressSpace::handleTimerMsg ()
{
	boost::mutex::scoped_lock lock (m_addressDistributionsMutex);

	//
	// when the interval expired and we reach here, the oldest distribution is
	// deleted from the queue and a new one in inserted
	//
	// remove the oldest element if the queue is full
	//

	unsigned int count = (unsigned int) m_addressDistributions.size();
	assert (count <= m_param_HistoryLength);

	if (count == m_param_HistoryLength) {
		SubnetCounterTree* tree = m_addressDistributions.front ();
		m_addressDistributions.pop ();
		delete tree;
	}

	//
	// create a new current tree 
	//

	m_currentCounterTree = m_subnetTemplate.copy ();
	m_addressDistributions.push (m_currentCounterTree);
}
