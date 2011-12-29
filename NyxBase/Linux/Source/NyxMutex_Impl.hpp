#ifndef _NYXMUTEX_IMPL_HPP_
#define _NYXMUTEX_IMPL_HPP_

#include "NyxMutex.hpp"
#include "NyxObject_Impl.hpp"

#include <pthread.h>

namespace NyxOSX
{
	class CMutex_Impl : public Nyx::CObject_Impl<Nyx::CMutex>
	{
	public:
		CMutex_Impl();
		virtual ~CMutex_Impl();
		
		virtual void Lock();
		virtual bool AttemptLock();
		virtual void Unlock();
		
	protected:
	
		pthread_mutex_t			m_Mutex;
		pthread_mutexattr_t		m_Attributes;
	};
};


#endif // _NYXMUTEX_IMPL_HPP_
