#ifndef _NYXTHREAD_IMPL_HPP_
#define _NYXTHREAD_IMPL_HPP_

#include "NyxThread.hpp"
#include "NyxObject_Impl.hpp"
#include "NyxRef.hpp"
#include "NyxEvent.hpp"

#include <pthread.h>

DECLARE_NYXOBJECTREF(CThreadProc)

namespace NyxLinux
{
	class CThread_Impl : public Nyx::CObject_Impl<Nyx::CThread>
	{
	public:
		CThread_Impl();
		virtual ~CThread_Impl();
		
		virtual Nyx::NyxResult Start(Nyx::CThreadProc* pTProc);
		virtual void Stop();
		virtual bool IsRunning() const;
		virtual void SetThreadUserData(void* pData);
		virtual void* GetThreadUserData();
		
	protected:
	
		static void* ThreadEntryPoint( void* pParam );
		
	protected:
	
		Nyx::CThreadProcRef					m_refThreadProc;
		Nyx::CEventRef						m_refInitializedEvent;
		pthread_t							m_ID;
		bool								m_bRunning;
		bool								m_bThreadLoopStarted;
		void*								m_pThreadUserData;
	};
}

#endif //_NYXTHREAD_IMPL_HPP_
