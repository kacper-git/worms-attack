#include "Timer.h"

#ifdef OMNET_SIMULATION
	#include "Distack.h"
	short Timer::GLOBAL_TIMER_ID = SHRT_MIN;
#endif // OMNET_SIMULATION

Timer::Timer ()
{
#ifdef OMNET_SIMULATION
	boost::mutex::scoped_lock scopedLock (scheduledMessageMutex);

	distackModule		= NULL;
	scheduledMessage	= NULL;
	timerId				= ++GLOBAL_TIMER_ID;
#else
	m_threadRunning		= false;
	m_thread			= NULL;
#endif // OMNET_SIMULATION
}

Timer::~Timer ()
{
#ifdef OMNET_SIMULATION
	boost::mutex::scoped_lock scopedLock (scheduledMessageMutex);
	if (scheduledMessage != NULL)
#else
	if (m_threadRunning)
#endif // OMNET_SIMULATION
		stop ();
}

void Timer::setInterval (unsigned int millis)
{
	m_millis = millis;
}

/**
  * starts the timer schedule
  * @param lib the name of the library module that called this timer. only used in Omnet++
  */
void Timer::start (string lib)
{
#ifdef OMNET_SIMULATION
	boost::mutex::scoped_lock scopedLock (scheduledMessageMutex);
	assert (distackModule != NULL);

	lib = "DistackTimer" + lib;
	scheduledMessage = distackModule->createTimerMsg (timerId, lib);
	double fireDelay = (double)m_millis / 1000.0; //TODO: firetime zu firedelay geändert, da man SimTime in omnet4 nicht zu double casten sollte -Claus
	
	distackModule->scheduleTimerMsg (simTime() + fireDelay, scheduledMessage);
#else
	m_threadRunning = true;
	m_thread		= new boost::thread (boost::bind (&Timer::threadFunction, this));
#endif // OMNET_SIMULATION
}

void Timer::stop ()
{
#ifdef OMNET_SIMULATION
	boost::mutex::scoped_lock scopedLock (scheduledMessageMutex);
	
	distackModule->cancelAndDelete (scheduledMessage);
	scheduledMessage = NULL;
#else
	m_threadRunning		= false;
	m_sleeper.interrupt ();
	m_thread->join		();

	delete m_thread;
	m_thread = NULL;
#endif // OMNET_SIMULATION
}

#ifdef OMNET_SIMULATION

void Timer::setDistackModule (DistackOmnetModule* module)
{
	distackModule = module;
}

bool Timer::receiveMessage (cMessage* msg)
{
	//
	// only handle timer messages with our timerid
	//

	if (msg->getKind() != timerId) return false;
		
	//
	// call the event function and reschedule the message
	// record the delivery time before callin the event function
	// to make sure that the eventFunction processing does not
	// influence the timer
	// 

	double fireDelay = (double)m_millis / 1000.0; //TODO: firetime zu firedelay geändert, da man SimTime in omnet4 nicht zu double casten sollte -Claus

	{
		boost::mutex::scoped_lock scopedLock (scheduledMessageMutex);
		// reuse the scheduled message and schedule again
		scheduledMessage = distackModule->cancelEvent(msg);
		distackModule->scheduleTimerMsg (simTime() + fireDelay, scheduledMessage);
	}

	eventFunction ();
	return true;
}

int Timer::getTimerId ()
{
	return timerId;
}

#else 

void Timer::threadFunction (Timer* timer)
{
	while (timer->m_threadRunning) {
		
		timer->m_sleeper.sleep (timer->m_millis);
		if (! timer->m_threadRunning) break;

		timer->eventFunction ();

	} // while (timer->m_threadRunning)

	return;
}

#endif // OMNET_SIMULATION
