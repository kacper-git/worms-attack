#include "NetworkInterface.h"
#include "base/network/FrameBuffer.h"

NetworkInterface::NetworkInterface (DistackInfo* info, string name, CAPTURE_TYPE type, bool promisc, unsigned int frameCaptureLen)
	: m_state( INTERFACE_STATE_UNKNOWN ), m_name( name ), m_promisc( promisc ),
	m_frameCaptureLen( frameCaptureLen ), m_captureType( type ), distackInfo( info )
{
	const unsigned int MAX_CAPTURE_LENGTH = (unsigned int) pow( 2.0, 16 ) - 1;

	if( m_frameCaptureLen == 0 || m_frameCaptureLen > MAX_CAPTURE_LENGTH )
		m_frameCaptureLen = MAX_CAPTURE_LENGTH;
}

NetworkInterface::~NetworkInterface()
{
}

bool NetworkInterface::getPromisc()
{
	return m_promisc;
}

unsigned int NetworkInterface::getFrameCaptureLength()
{
	return m_frameCaptureLen;
}

void NetworkInterface::setDescription( string description )
{
	m_description = description;
}

NetworkInterface::INTERFACE_STATE NetworkInterface::getState()
{
	return m_state;
}

void NetworkInterface::setState( NetworkInterface::INTERFACE_STATE state )
{
	logging_debug( "interface state for " + getName() + 
		" set to " + getStateName (state) );
	m_state = state;
}

string NetworkInterface::getName()
{
	return m_name;
}

string NetworkInterface::getDescription()
{
	return m_description;
}

string NetworkInterface::getStateName( INTERFACE_STATE state )
{
	switch (state) {
		case INTERFACE_STATE_UNKNOWN: return "unknown";
		case INTERFACE_STATE_OPEN: return "open";
		case INTERFACE_STATE_CLOSE: return "close";
		default: return "invalid";
	}

	return "invalid";
}

NetworkInterface::CAPTURE_TYPE NetworkInterface::getCaptureType()
{
	return m_captureType;
}

void NetworkInterface::setCaptureType( CAPTURE_TYPE type )
{
	m_captureType = type;
}
