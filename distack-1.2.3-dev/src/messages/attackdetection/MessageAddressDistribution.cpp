#include "MessageAddressDistribution.h"

MessageAddressDistribution::MessageAddressDistribution () 
{
}

MessageAddressDistribution::~MessageAddressDistribution ()
{
	SUBNET_COUNTER_ITEMS_ITERATOR i = m_counterItems.begin();
	SUBNET_COUNTER_ITEMS_ITERATOR iend = m_counterItems.end();

	for ( ; i != iend; i++)
		delete *i;
}

Message::MESSAGE_TYPE MessageAddressDistribution::getType ()
{
	return Message::MESSAGE_TYPE_ADDRESS_DISTRIBUTION;
}

void MessageAddressDistribution::addSubnetDistrib (SubnetCounterTree* tree)
{
	m_counterItems.push_back (tree);
}

unsigned int MessageAddressDistribution::getSubnetDistribCount ()
{
	return (unsigned int) m_counterItems.size ();
}

SubnetCounterTree* MessageAddressDistribution::getSubnetDistrib (unsigned int index)
{
	if (index < m_counterItems.size())	return m_counterItems[index];
	else								return NULL;
}
