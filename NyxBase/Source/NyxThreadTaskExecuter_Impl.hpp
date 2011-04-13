#ifndef _NYXTHREADTASKEXECUTER_IMPL_HPP_
#define _NYXTHREADTASKEXECUTER_IMPL_HPP_

#pragma managed(push, off)

#include "NyxTaskExecuter.hpp"
#include "NyxThreadProc.hpp"
#include "NyxThread.hpp"
#include "NyxObject_Impl.hpp"
#include "NyxEvent.hpp"

namespace NyxOSX
{
	class CTaskExecuterPool_Impl;

	class CThreadTaskExecuter_Impl : public Nyx::CObject_Impl<Nyx::CTaskExecuter>
	{
	public:
		CThreadTaskExecuter_Impl(CTaskExecuterPool_Impl& rOwnerPool);
		virtual ~CThreadTaskExecuter_Impl();
		
		virtual Nyx::NyxResult Start();
		virtual void Stop();

	public: // CTaskExecuter

		virtual Nyx::NyxResult Execute( Nyx::CTask* pTask );
		virtual Nyx::NyxResult StopCurrentTask();

	public: // CThreadProc

		virtual void RunningLoop();
		virtual void StopThread();

	protected:
	
		CTaskExecuterPool_Impl&		m_rOwnerPool;

		Nyx::CTaskRef				m_refTask;		
		Nyx::CThreadRef				m_refThread;
		Nyx::CEventRef				m_refWakeupEvent;
		bool						m_bKeepRunning;
	};
}

#pragma managed(pop)

#endif // _NYXTHREADTASKEXECUTER_IMPL_HPP_
