#ifndef __MESSAGE_ADDRESS_DISTRIBUTION_H
#define __MESSAGE_ADDRESS_DISTRIBUTION_H

#include <vector>
#include <algorithm>
#include "base/message/Message.h"
#include "base/common/SubnetCounterTree.h"

using std::vector;

class MessageAddressDistribution : public Message {
public:
	MessageAddressDistribution();
	~MessageAddressDistribution();

	MESSAGE_TYPE getType ();

	void addSubnetDistrib( SubnetCounterTree* tree );
	unsigned int getSubnetDistribCount();
	SubnetCounterTree* getSubnetDistrib( unsigned int index );

private:
	typedef vector<SubnetCounterTree*> SUBNET_COUNTER_ITEMS;
	typedef SUBNET_COUNTER_ITEMS::iterator SUBNET_COUNTER_ITEMS_ITERATOR;
	SUBNET_COUNTER_ITEMS m_counterItems;
	
	REMOTE_MESSAGING_BEGIN(MessageAddressDistribution, remote)
#ifdef REMOTE_XML
// TODO
// 		remote & boost::serialization::make_nvp("", );
#else
// TODO
// 		remote & ;
#endif //REMOTE_XML	
	REMOTE_MESSAGING_END
};

#endif // __MESSAGE_ADDRESS_DISTRIBUTION_H
