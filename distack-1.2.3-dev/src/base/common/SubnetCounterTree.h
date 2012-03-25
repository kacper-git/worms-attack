#ifndef __SUBNET_COUNTER_TREE_H
#define __SUBNET_COUNTER_TREE_H

#include "base/common/PatriciaTrie.h"
#include "base/protocol/IpPacket.h"

class SubnetCounterTree {
public:
	typedef struct _ADDR_COUNTER {
		unsigned long srcCount;	
		unsigned long dstCount;

		bool operator== (const struct _ADDR_COUNTER& right) const {
			return (srcCount == right.srcCount && dstCount == right.dstCount);	
		}	

		_ADDR_COUNTER () {
			srcCount = dstCount = 0;
		}
		
		_ADDR_COUNTER (unsigned long src, unsigned long dst) {
			srcCount = src;
			dstCount = dst;
		}
	} ADDR_COUNTER, *PADDR_COUNTER;	

private:
	typedef PatriciaTrie<IP_ADDR, ADDR_COUNTER> SUBNET_DISTRIBUTION;
	typedef PatriciaTrieNode<IP_ADDR, ADDR_COUNTER> SUBNET_DISTRIBUTION_NODE;
	
	SUBNET_DISTRIBUTION* m_patriciaTrie;
	
public:
	SubnetCounterTree( SUBNET_DISTRIBUTION* distrib = NULL );
	~SubnetCounterTree();

	typedef enum _COUNT_TYPE {
		COUNT_TYPE_SOURCE,
		COUNT_TYPE_DEST,
	} COUNT_TYPE;

	void clear();
	void clearCounters();
	void addSubnet( IP_ADDR addr, IP_ADDR mask );
	void addCount( IP_ADDR addr, COUNT_TYPE type, unsigned long count = 1 );
	SubnetCounterTree* copy();

	typedef SUBNET_DISTRIBUTION::NODE_LIST SUBNET_DISTRIBUTION_NODE_LIST;
	typedef SUBNET_DISTRIBUTION_NODE_LIST::iterator SUBNET_DISTRIBUTION_NODE_LIST_ITERATOR;

	SUBNET_DISTRIBUTION_NODE_LIST	getSubnets ();
};

#endif // __SUBNET_COUNTER_TREE_H
