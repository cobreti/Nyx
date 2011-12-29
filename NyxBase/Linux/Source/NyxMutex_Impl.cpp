#include "NyxMutex_Impl.hpp"


Nyx::CMutex* Nyx::CMutex::Alloc()
{
	return new NyxLinux::CMutex_Impl();
}


NyxLinux::CMutex_Impl::CMutex_Impl()
{
	pthread_mutexattr_init(&m_Attributes);
	pthread_mutexattr_settype(&m_Attributes, PTHREAD_MUTEX_RECURSIVE);
	pthread_mutex_init(&m_Mutex, &m_Attributes);
}


NyxLinux::CMutex_Impl::~CMutex_Impl()
{
	pthread_mutex_destroy(&m_Mutex);
	pthread_mutexattr_destroy(&m_Attributes);
}


void NyxLinux::CMutex_Impl::Lock()
{
	pthread_mutex_lock(&m_Mutex);
}


bool NyxLinux::CMutex_Impl::AttemptLock()
{
	return (0 == pthread_mutex_trylock(&m_Mutex));
}


void NyxLinux::CMutex_Impl::Unlock()
{
	pthread_mutex_unlock(&m_Mutex);
}
