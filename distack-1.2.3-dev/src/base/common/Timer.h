#ifndef __TIMER_H
#define __TIMER_H

#include <boost/thread/mutex.hpp>
#include <climits>
#include <string>

#ifdef OMNET_SIMULATION
	class DistackOmnetModule;	// forward decl
	class cMessage;			// forward decl
#else
	#include "base/common/InterruptableSleeper.h"
	#include <boost/thread/thread.hpp>
	#include <boost/thread/xtime.hpp>
	#include <boost/bind.hpp>
	#include "base/common/Helper.h"
#endif // OMNET_SIMULATION

using std::string;

/** @class Timer
  * an independent implementation of a timer. For the pcap interface InterruptableSleeper is used, based on threads. For Omnet++ the self messaging functionality of Omnet++ is used.
  */
class Timer {
public:		
						Timer				();
						~Timer				();

	void					setInterval			(unsigned int millis);
	void					start					(string lib = "dt");
	void					stop				();

#ifdef OMNET_SIMULATION
	void					setDistackModule		(DistackOmnetModule* module);
	bool					receiveMessage			(cMessage* msg);
	int					getTimerId			();
#endif // OMNET_SIMULATION

protected:

	virtual void				eventFunction			() {};

private:
	
	unsigned int				m_millis;

#ifdef OMNET_SIMULATION
	DistackOmnetModule*			distackModule;
	cMessage*				scheduledMessage; 
	boost::mutex				scheduledMessageMutex;
	/// every new Timer instance increases this id
	static short				GLOBAL_TIMER_ID;
	short						timerId;
#else
	static void				threadFunction			(Timer* timer);
	boost::thread*				m_thread;
	volatile bool				m_threadRunning;
	InterruptableSleeper			m_sleeper;
#endif // OMNET_SIMULATION

};

#endif // __TIMER_H
