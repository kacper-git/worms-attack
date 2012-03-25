#ifndef __DISTACK_H
#define __DISTACK_H

//
// Distack has two interfaces: 
// - one for normal compilation that has a main function
// - one Omnet++ interface for simulation
//
// both interfaces do about the same, just in a different way ... :)
//

#include <locale.h>
#include <list>
#include <sstream>
#include <algorithm>
#include <boost/thread/mutex.hpp>
#include "base/common/DistackInfo.h"
#include "base/common/StdOutLogOutputter.h"
#include "base/common/FileLogOutputter.h"
#include "base/common/Log.h"
#include "base/common/Helper.h"
#include "base/network/NetworkManager.h"
#include "base/module/ModuleManager.h"
#include "base/configuration/Configuration.h"

#ifdef OMNET_SIMULATION
	#include <omnetpp.h>
	#include "base/network/NetworkInterface.h"
	#include "base/network/omnetpp/NetworkInterfaceOmnetpp.h"
	#include "base/common/Timer.h"
	class DistackOmnetModule; // forward decl;
#endif

#ifdef _MSC_VER
	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>
	#ifdef _DEBUG
		#define _CRTDBG_MAP_ALLOC
		#include <crtdbg.h>
	#endif
#endif

using std::ostringstream;
using std::find;
using std::list;

/** @class Distack
  * Contains the attack detection functionality and offers two interfaces: 
  * one for normal operation using pcap and one for simulation using Omnet++.
  */
class Distack {
public:
	Distack( DistackInfo* info );
	~Distack();

	bool startup();
	bool shutdown();

#ifdef OMNET_SIMULATION
	void setDistackModule( DistackOmnetModule* module );
#endif

	NetworkManager* getNetworkManager();
	ModuleManager* getModuleManager();

private:
	DistackInfo* distackInfo;
	NetworkManager* m_networkmanager;
	ModuleManager* m_modulemanager;

	LogOutputter* m_logoutputter;

#ifdef OMNET_SIMULATION
	DistackOmnetModule* distackModule;
#endif
};

#ifndef OMNET_SIMULATION

	int main( int argc, char* argv[] );

#else
	/** @class DistackOmnetModule
	* The Omnet Interface Class.
	* Encapsulates the Distack functionality in a cSimpleModule, usable in Omnet++.
	*/
	class INET_API DistackOmnetModule : public cSimpleModule {
	public:	
		DistackOmnetModule();
		~DistackOmnetModule();

		void registerTimer( Timer* timer );
		void unregisterTimer( Timer* timer );
		void scheduleTimerMsg( simtime_t tm, cMessage* msg );
		cMessage* createTimerMsg( int timerid, string name="" );
		Distack* getDistack();

	protected:
		/// called from Omnet++ on initialization of the simulation
		virtual int numInitStages() const;
		virtual void initialize( int stages );
		/// called from Omnet++ during simulation: called when the module receives a message
		virtual void handleMessage( cMessage *msg );
		/// called from Omnet++ during simulation: called when the 
		/// simulation terminates. Can be used for writing statistics and the likes.
		virtual void  finish();

	private:
		DistackInfo* distackInfo;
		bool doShutdown;
		static int GLOBAL_ID;
		Distack* distack;
		NetworkInterfaceOmnetpp* omnetInterface;

		typedef list<Timer*> OMNET_TIMER_LIST;
		typedef OMNET_TIMER_LIST::iterator OMNET_TIMER_LIST_ITERATOR;
		OMNET_TIMER_LIST timerList;	
		boost::mutex timerListMutex;

		boost::mutex sendMsgMutex;
	};

	//
	// The distack module class needs to be registered with OMNeT++
	//

	Define_Module (DistackOmnetModule);

#endif // OMNET_SIMULATION
#endif // __DISTACK_H
