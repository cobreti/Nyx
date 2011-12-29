#include "NyxEvent_Impl.hpp"

#include <sys/time.h>

Nyx::CEvent* Nyx::CEvent::Alloc()
{
	return new NyxLinux::CEvent_Impl();
}



NyxLinux::CEvent_Impl::CEvent_Impl()
{
	pthread_mutexattr_init(&m_MutexAttributes);
	pthread_mutexattr_settype(&m_MutexAttributes, PTHREAD_MUTEX_RECURSIVE);
	pthread_mutex_init(&m_Mutex, &m_MutexAttributes);
	pthread_cond_init(&m_Cond, NULL);
}


NyxLinux::CEvent_Impl::~CEvent_Impl()
{
	pthread_cond_destroy(&m_Cond);
	pthread_mutex_destroy(&m_Mutex);
	pthread_mutexattr_destroy(&m_MutexAttributes);
}


void NyxLinux::CEvent_Impl::Signal( const Nyx::UInt32& unFlag )
{
	pthread_cond_signal(&m_Cond);
}


Nyx::NyxResult NyxLinux::CEvent_Impl::WaitSignaled( const Nyx::UInt32& unTimeout )
{
	Nyx::NyxResult		res = Nyx::kNyxRes_Failure;
	int					nRes = 0;
	timespec			ts;
	timeval				tp;

	pthread_mutex_lock(&m_Mutex);

	gettimeofday(&tp, NULL);

	/* Convert from timeval to timespec */
	ts.tv_sec  = tp.tv_sec;
	ts.tv_nsec = tp.tv_usec * 1000;
	ts.tv_sec += unTimeout / 1000;
	ts.tv_nsec += (unTimeout % 1000) * 1000000;

	nRes = pthread_cond_timedwait(&m_Cond, &m_Mutex, &ts);
	res = (nRes >= 0) ? Nyx::kNyxRes_Success : Nyx::kNyxRes_Failure;
	
	pthread_mutex_unlock(&m_Mutex);

	return res;
}


Nyx::NyxResult NyxLinux::CEvent_Impl::WaitSignaled()
{
	Nyx::NyxResult				res = Nyx::kNyxRes_Failure;
	int							nRes = 0;
	
	pthread_mutex_lock(&m_Mutex);
	
	nRes = pthread_cond_wait(&m_Cond, &m_Mutex);
	res = (nRes >= 0) ? Nyx::kNyxRes_Success : Nyx::kNyxRes_Failure;

	pthread_mutex_unlock(&m_Mutex);

	return res;
}



