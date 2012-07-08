#ifndef _NYXTHREAD_IMPL_HPP_
#define _NYXTHREAD_IMPL_HPP_

#include "NyxThread.hpp"
#include "NyxObject_Impl.hpp"
#include "NyxRef.hpp"
#include "NyxMutex.hpp"

#include <Windows.h>

DECLARE_NYXOBJECTREF(CThreadProc)

namespace NyxWin32
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
	
		static DWORD WINAPI ThreadEntryPoint( void* pParam );
		
	protected:
	
		Nyx::CThreadProcRef					m_refThreadProc;
		Nyx::CMutexRef						m_refThreadDataMutex;
		HANDLE								m_hThread;
		DWORD								m_ThreadId;
		bool								m_bRunning;
		void*								m_pThreadUserData;
	};
}

#endif //_NYXTHREAD_IMPL_HPP_
