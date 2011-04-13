#include "NyxThreadTaskExecuter_Impl.hpp"
#include "NyxTaskExecuterPool_Impl.hpp"
#include "NyxTraceStream.hpp"

#pragma unmanaged

/**
 *
 */
NyxOSX::CThreadTaskExecuter_Impl::CThreadTaskExecuter_Impl(CTaskExecuterPool_Impl& rOwnerPool) :
m_rOwnerPool(rOwnerPool),
m_bKeepRunning(true)
{
	m_refWakeupEvent = Nyx::CEvent::Alloc();
}


/**
 *
 */
NyxOSX::CThreadTaskExecuter_Impl::~CThreadTaskExecuter_Impl()
{
}


/**
 *
 */
Nyx::NyxResult NyxOSX::CThreadTaskExecuter_Impl::Start()
{
	Nyx::NyxResult		res = Nyx::kNyxRes_Success;
	
	m_refThread = Nyx::CThread::Alloc();
	res = m_refThread->Start( new Nyx::CThreadDelegate<NyxOSX::CThreadTaskExecuter_Impl>( this,
								&NyxOSX::CThreadTaskExecuter_Impl::RunningLoop,
								&NyxOSX::CThreadTaskExecuter_Impl::StopThread) );
	
	return res;
}


/**
 *
 */
void NyxOSX::CThreadTaskExecuter_Impl::Stop()
{
	if ( m_refThread.Valid() )
	{
		m_refThread->Stop();
		m_refThread = NULL;
	}
}


/**
 *
 */
Nyx::NyxResult NyxOSX::CThreadTaskExecuter_Impl::Execute( Nyx::CTask* pTask )
{
	if ( pTask == NULL )
		return Nyx::kNyxRes_InvalidArgs;
		
	if ( m_refTask.Valid() )
		return Nyx::kNyxRes_Failure;

	Nyx::NyxResult		res = Nyx::kNyxRes_Success;
		
	m_refTask = pTask;
	
	m_refWakeupEvent->Signal(0);
		
	return res;
}


/**
 *
 */
Nyx::NyxResult NyxOSX::CThreadTaskExecuter_Impl::StopCurrentTask()
{
	if ( !m_refTask.Valid() )
		return Nyx::kNyxRes_Failure;

	Nyx::NyxResult		res = Nyx::kNyxRes_Success;
	
	m_refTask->Stop();
	
	return res;
}


/**
 *
 */
void NyxOSX::CThreadTaskExecuter_Impl::RunningLoop()
{
	while ( m_bKeepRunning )
	{
		if ( m_bKeepRunning && m_refTask.Valid() )
		{
			m_refTask->Execute();
			m_refTask = NULL;
			m_rOwnerPool.OnTaskExecuterAvailable(this);
		}

		m_refWakeupEvent->WaitSignaled();
	}
}


/**
 *
 */
void NyxOSX::CThreadTaskExecuter_Impl::StopThread()
{
	m_bKeepRunning = false;
	
	if ( m_refTask.Valid() )
		m_refTask->Stop();
	
	m_refWakeupEvent->Signal(0);
}

