#include "MplsPacket.h"

MplsPacket::MplsPacket(void)
{
	memset		(&header, 0, sizeof (MPLS_HEADER));
	protocol	= Packet::PROTO_MPLS;
}

MplsPacket::~MplsPacket(void)
{
}

bool MplsPacket::parsePacket()
{
	memcpy (&header, buffer, sizeof (MPLS_HEADER)); 

	//
	// next protocol is always IP
	//

	nextProtocol	= Packet::PROTO_IP;
	layersize		= sizeof (MPLS_HEADER);

	//
	// adjust endianess
	//

	//header.destport		=	swap16	(header.destport	);
	//header.sourceport	=	swap16	(header.sourceport	);
	//header.checksum		=	swap16	(header.checksum	);
	//header.len			=	swap16	(header.len			);
	
	return true;
}

string MplsPacket::toString ()
{
	ostringstream out;

	out << "MPLS packet"							<< std::endl
		<< "\tlabel: \t"	<< getLabel ()			<< std::endl
		<< "\texp: \t"		<< getExperimental ()	<< std::endl
		<< "\tS: \t"		<< (getStack() ? 1 : 0)	<< std::endl
		<< "\tttl: \t"		<< getTtl ()			;

	return out.str ();
}

unsigned int MplsPacket::getMinProtocolSize ()
{
	return sizeof (MPLS_HEADER);
}

unsigned int MplsPacket::getLabel ()
{
	return MPLS_LABEL (header.packet);
}

unsigned short MplsPacket::getExperimental ()	
{
return MPLS_EXP (header.packet);
}

bool MplsPacket::getStack ()	
{
	return (MPLS_S(header.packet) == 1);
}

unsigned short MplsPacket::getTtl ()		
{
	return MPLS_TTL (header.packet);
}

void MplsPacket::setLabel (unsigned int label)	
{
	// TODO
}

void MplsPacket::setExperimental (unsigned short exp)	
{
	// TODO
}

void MplsPacket::setStack (bool stack)						
{
	// TODO
}

void MplsPacket::setTtl (unsigned short ttl)	
{
	// TODO
}
