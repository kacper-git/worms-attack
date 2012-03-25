#include "InterruptableSleeper.h"

InterruptableSleeper::InterruptableSleeper ()
{
	boost::mutex::scoped_lock scopedLock( m_mutex );

#ifdef WIN32
	m_handle = CreateEvent( NULL, TRUE, FALSE, NULL );
	assert (m_handle != NULL);
#else
	m_handle = new MUTEX_COND();
	int ret = 0;

	ret = pthread_mutex_init (&(m_handle->mutex), NULL);
	assert (ret == 0);
	
	ret = pthread_cond_init (&(m_handle->cond), NULL);
	assert (ret == 0);
#endif
}

InterruptableSleeper::~InterruptableSleeper ()
{
	boost::mutex::scoped_lock scopedLock (m_mutex);

#ifdef WIN32
	BOOL ret = CloseHandle (m_handle);
	assert (ret == TRUE);
#else
	int ret = 0;

	ret = pthread_cond_destroy (&(m_handle->cond));
	assert (ret == 0);

	ret = pthread_mutex_destroy (&(m_handle->mutex));
	assert (ret == 0);

	delete m_handle;
#endif
}

void InterruptableSleeper::interrupt ()
{
	boost::mutex::scoped_lock scopedLock (m_mutex);

#ifdef WIN32
	BOOL ret = SetEvent (m_handle);	
	assert (ret == TRUE);
#else
	int ret = pthread_cond_signal (&(m_handle)->cond);
	assert (ret == 0);
#endif
}

void InterruptableSleeper::sleep (unsigned long millis)
{	
	//
	// NO mutex, otherwise the ::interrupt 
	// function can not be called at all
	//

#ifdef WIN32

	DWORD dret = WaitForSingleObject (m_handle, millis);
	assert (dret != WAIT_FAILED);

#else

	int				ret;
	struct timespec tm;
	struct timeb	tp;

	ret = pthread_mutex_lock (&(m_handle->mutex));
	assert (ret == 0);

	long sec		= millis / 1000;
	long millisec	= millis % 1000;
	
	ftime (&tp);
	tp.time			+= sec;
	tp.millitm		+= millisec;
	
	if (tp.millitm > 999) {
		tp.millitm -= 1000;
		tp.time++;
	}

	tm.tv_sec  = tp.time;
	tm.tv_nsec = tp.millitm * 1000000;

	ret = pthread_cond_timedwait (&(m_handle->cond), &(m_handle->mutex), &tm);
	assert (ret == 0 || ret == ETIMEDOUT);
	
	ret = pthread_mutex_unlock (&(m_handle->mutex));
	assert (ret == 0);

#endif

	//
	// under Windows we have to reset the event again
	//

#ifdef WIN32
	{
		boost::mutex::scoped_lock scopedLock (m_mutex);

		BOOL bret;
		bret = ResetEvent (m_handle);
		assert (bret == TRUE);
	}
#endif
}
