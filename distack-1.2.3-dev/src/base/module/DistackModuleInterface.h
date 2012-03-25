#ifndef __MODULE_INTERFACE_H
#define __MODULE_INTERFACE_H

#include <string>
#include <map>
#include <ctime>
#include <algorithm>
#include "base/common/Timer.h"
#include "base/common/Helper.h"
#include "base/protocol/Frame.h"
#include "base/message/MessagingNode.h"
#include <boost/lexical_cast.hpp>

using std::string;
using std::pair;
using std::map;

#ifdef WIN32
	#define DLLEXPORT __declspec(dllexport)
#else
	#define DLLEXPORT
#endif

#include "base/common/Log.h"
#include "base/protocol/PacketFactory.h"

#define MODULE_INTERFACE(x) \
	extern "C" DLLEXPORT DistackModuleInterface* createModule( unsigned int id ) \
	{ \
		return new x(); \
	} \
	extern "C" DLLEXPORT int initPacketFactory( PacketFactory* factory ) \
	{ \
		PacketFactory::reference( factory ); \
		return 0; \
	} \
	extern "C" DLLEXPORT int initLogging( Log* logger ) \
	{ \
		Log::reference( logger ); \
		return 0; \
	}

class ModuleConfiguration {
private:

	typedef pair<string,string>		CONFIG_PAIR;
	typedef map<string, string>		CONFIG_MAP;
	CONFIG_MAP						configmap;

public:

	string							name;
	string							library;
	unsigned short					stage;

	void				set			(string name, string value)
	{
		configmap.insert (CONFIG_PAIR (name, value));
	}

	bool				has			(string name)
	{
		return (configmap.find (name) != configmap.end ());
	}

	string				get			(string name)
	{
		CONFIG_MAP::iterator it = configmap.find (name);
		return (it != configmap.end() ? it->second : "");
	}

	long				getLong		(string name) 
	{	
		string val = get (name);
		return strtol (val.c_str (), NULL, 10);
	}

	double				getDouble	(string name)
	{
		//
		// do not use strtod for string to double conversion as
		// it relies on the system locale settings (use . or , as separator)
		//

		string val = get (name);
		return boost::lexical_cast<double> (val);
	}

	string				toString	()
	{
		string ret = "";
		CONFIG_MAP::iterator begin	= configmap.begin	();
		CONFIG_MAP::iterator end	= configmap.end		();

		for ( ; begin != end; begin++) {
			if (ret.length () > 0) ret += "";
			ret += "[" + begin->first + "," + begin->second + "]";
		}
		
		return ret;
	}

};

#ifdef OMNET_SIMULATION
	class DistackOmnetModule; // forward decl
#endif

class DistackInfo;

class DistackModuleInterface : public MessagingNode, public Timer {
public:

					DistackModuleInterface	(){};
	virtual				~DistackModuleInterface	(){};

	virtual bool			configure		(ModuleConfiguration& configList) = 0;
	virtual bool			frameCall		(Frame& frame) {return true;};

#ifdef OMNET_SIMULATION
	DistackOmnetModule*		omnetModule;
#endif

#ifdef OMNET_SIMULATION
	#define ENVIR_TIME	(static_cast<unsigned long>(simTime().dbl()))
#else
	//#define ENVIR_TIME	(static_cast<unsigned long>((((double)clock())/((double)CLOCKS_PER_SEC))* 1000.0))
	#define ENVIR_TIME		(static_cast<unsigned long>(time(NULL)*1000))
#endif // OMNET_SIMULATION

	DistackInfo*			distackInfo;
};

#endif // __MODULE_INTERFACE_H
