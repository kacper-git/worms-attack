cplusplus {{
#include "IPvXAddress.h"
#include "ReaSEDefs.h"
const int DISTACK_RAO_PACKET_SIZE = 48;
}}
struct IPvXAddress;

packet DistackRAOData
{
	IPvXAddress requester;
	IPvXAddress target;
	int requesterPort;
	int id;
}