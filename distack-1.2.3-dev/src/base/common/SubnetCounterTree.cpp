#include "SubnetCounterTree.h"

SubnetCounterTree::SubnetCounterTree (SUBNET_DISTRIBUTION* distrib)
{
	m_patriciaTrie = (distrib == NULL ? new SUBNET_DISTRIBUTION() : distrib);
}

SubnetCounterTree::~SubnetCounterTree ()
{
	delete m_patriciaTrie;
	m_patriciaTrie = NULL;
}

SubnetCounterTree* SubnetCounterTree::copy ()
{
	SubnetCounterTree* ret = new SubnetCounterTree (m_patriciaTrie->Copy ());
	return ret;
}

void SubnetCounterTree::clear ()
{
	SUBNET_DISTRIBUTION_NODE_LIST			nodes	= m_patriciaTrie->GetNodeList ();
	SUBNET_DISTRIBUTION_NODE_LIST_ITERATOR	i		= nodes.begin ();
	SUBNET_DISTRIBUTION_NODE_LIST_ITERATOR	iend	= nodes.end	  ();

	for ( ; i != iend; i++) {
		SUBNET_DISTRIBUTION_NODE* node = *i;
		m_patriciaTrie->Delete (node->GetKey ());
	}

}

SubnetCounterTree::SUBNET_DISTRIBUTION_NODE_LIST SubnetCounterTree::getSubnets ()
{
	return m_patriciaTrie->GetNodeList ();
}

void SubnetCounterTree::clearCounters ()
{
	SUBNET_DISTRIBUTION_NODE_LIST		  nodes = m_patriciaTrie->GetNodeList ();
	SUBNET_DISTRIBUTION_NODE_LIST_ITERATOR i		= nodes.begin ();
	SUBNET_DISTRIBUTION_NODE_LIST_ITERATOR iend	= nodes.end	  ();

	for ( ; i != iend; i++) {
		SUBNET_DISTRIBUTION_NODE* node = *i;
		node->SetData (ADDR_COUNTER (0, 0));
	}
}	

void SubnetCounterTree::addSubnet (IP_ADDR addr, IP_ADDR mask)
{
	IP_ADDR subnet = addr & mask;
	
	if (! m_patriciaTrie->Exists (subnet))
		m_patriciaTrie->Insert (subnet, ADDR_COUNTER (0, 0));
}

void SubnetCounterTree::addCount (IP_ADDR addr, COUNT_TYPE type, unsigned long count)
{
	//
	// find out which subnet belongs to the addr
	//

	SUBNET_DISTRIBUTION_NODE* node = m_patriciaTrie->LookupGroup (addr);
	if (node == NULL) return;
	
	//
	// update the counter for the subnet
	//

	ADDR_COUNTER counter = node->GetData ();
	
	if (type == COUNT_TYPE_SOURCE)	counter.srcCount += count;
	if (type == COUNT_TYPE_DEST)	counter.dstCount += count;

	node->SetData (counter);
}
