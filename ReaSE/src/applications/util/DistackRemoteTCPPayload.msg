cplusplus {{
#include "ReaSEDefs.h"
}}

packet DistackRemoteTCPPayload
{
	char header[];
	char data[];
	bool xml;
}
