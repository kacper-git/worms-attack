#ifndef __INTERRUPTABLE_SLEEPER_H
#define __INTERRUPTABLE_SLEEPER_H

#include <boost/thread/mutex.hpp>
#include <cassert>
#include <iostream>

using std::cout;

#ifdef WIN32
	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>
#else	
	#include <pthread.h>
	#include <time.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <sys/types.h>
	#include <sys/timeb.h>
	#include <unistd.h>
	#include <errno.h>
#endif

/** @class InterruptableSleeper
  * an implementation of an interruptable sleeper used for timers with the pcap interface. omnet++ has its own timer mechanism using self messages, so this is not used within omnet++ (it would also break simulation functionality, as it operates in its own thread outside of the simulation time)
  */
class InterruptableSleeper {
public:
					InterruptableSleeper		();
					~InterruptableSleeper		();

	void			sleep						(unsigned long millis);
	void			interrupt					();

private:
	
#ifdef WIN32
	HANDLE			m_handle;
#else
	typedef struct _MUTEX_COND {
		pthread_cond_t	cond;
		pthread_mutex_t mutex;
	} MUTEX_COND, *PMUTEX_COND;

	PMUTEX_COND		m_handle;
#endif

	boost::mutex	m_mutex;
};

#endif // __INTERRUPTABLE_SLEEPER_H
