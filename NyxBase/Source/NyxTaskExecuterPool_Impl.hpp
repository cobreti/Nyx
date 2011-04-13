#ifndef _NYXTASKEXECUTERPOOL_IMPL_HPP_
#define _NYXTASKEXECUTERPOOL_IMPL_HPP_

#include "NyxTaskExecuterPool.hpp"
#include "NyxTaskExecuter.hpp"
#include "NyxObject_Impl.hpp"
#include "NyxMutex.hpp"

#include <list>

namespace NyxOSX
{
	class CTaskExecuterPool_Impl : public Nyx::CObject_Impl<Nyx::CTaskExecuterPool>
	{
	public:
		CTaskExecuterPool_Impl();
		virtual ~CTaskExecuterPool_Impl();
		
		virtual void OnTaskExecuterAvailable( Nyx::CTaskExecuterRef refExecuter );
		
	public:
	
		virtual Nyx::NyxResult Execute( Nyx::CTask* pTask );
		virtual void StopAllTasks();
		
	protected:	// protected types
	
		typedef		std::list<Nyx::CTaskExecuterRef>			TaskExecuterList;
	
	protected:	// protected methods
	
		virtual Nyx::NyxResult GetTaskExecuter( Nyx::CTaskExecuterRef& refTaskExecuter );
		virtual void ReleaseTaskExecuters();
	
	protected:	// protected members

		Nyx::CMutexRef			m_refExecutersAccess;
	
		TaskExecuterList		m_FreeExecuters;
		TaskExecuterList		m_UsedExecuters;
	};
}


#endif // _NYXTASKEXECUTERPOOL_IMPL_HPP_
