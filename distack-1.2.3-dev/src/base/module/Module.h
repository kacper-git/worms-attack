#ifndef __MODULE_H
#define __MODULE_H

#include <string>
#include <boost/array.hpp>
#include "base/module/DynamicLibrary.h"
#include "base/protocol/Frame.h"
#include "base/module/DistackModuleInterface.h"

class Timer;
class DistackInfo;
class PacketFactory;
#ifdef OMNET_SIMULATION
  class DistackOmnetModule; // forward decl
#endif // OMNET_SIMULATION

using std::string;

#define MODULE_INTERFACE_ENTRYFUNCTION			"createModule"
#define MODULE_INTERFACE_INIT_PACKETFACTORY		"initPacketFactory"
#define MODULE_INTERFACE_INIT_LOGGING			"initLogging"

class Module {
public:

#ifdef OMNET_SIMULATION
	Module( ModuleConfiguration config, DistackOmnetModule* omnetModule, DistackInfo* info );
#else
	Module( ModuleConfiguration config, DistackInfo* info );
#endif // OMNET_SIMULATION
						
	virtual 				~Module					();

	string					getName					();
	bool					good					();
	bool					frameCall				(Frame& frame);
	DistackModuleInterface*			getInternal				();
	static void				setLibrarySearchPaths			(DynamicLibrary::SEARCH_PATHES pathes);

protected:

	void					setName					(string name);
	bool					goodstate;

private:
	DistackInfo* distackInfo;

#ifdef OMNET_SIMULATION
	DistackOmnetModule*			m_distackModule;	
#endif // OMNET_SIMULATION

	string					m_name;
	DynamicLibrary				m_library;
	DistackModuleInterface*			m_internal;

	static unsigned long			ID_COUNTER;
	static DynamicLibrary::SEARCH_PATHES 	m_libraryPaths;

};

#endif // __MODULE_H
