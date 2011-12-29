#ifndef _NYXEVENT_IMPL_HPP_
#define _NYXEVENT_IMPL_HPP_

#include "NyxEvent.hpp"
#include "NyxObject_Impl.hpp"

#include <pthread.h>

namespace NyxLinux
{
	class CEvent_Impl : public Nyx::CObject_Impl<Nyx::CEvent>
	{
	public:
		CEvent_Impl();
		virtual ~CEvent_Impl();
		
		virtual void Signal( const Nyx::UInt32& unFlag );
		virtual Nyx::NyxResult WaitSignaled( const Nyx::UInt32& unTimeout );
		virtual Nyx::NyxResult WaitSignaled();
		
	protected:
	
		pthread_cond_t			m_Cond;
		pthread_mutex_t			m_Mutex;
		pthread_mutexattr_t		m_MutexAttributes;
	};
};

#endif // _NYXEVENT_IMPL_HPP_

