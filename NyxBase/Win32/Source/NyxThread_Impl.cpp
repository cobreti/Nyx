#include "NyxThread_Impl.hpp"
#include "NyxModule.hpp"
#include "NyxTraceCompositor.hpp"
#include "NyxLock.hpp"

/**
 *
 */
Nyx::CThreadRef Nyx::CThread::Alloc()
{
	return new NyxWin32::CThread_Impl();
}


/**
 *
 */
NyxWin32::CThread_Impl::CThread_Impl() :
m_hThread(INVALID_HANDLE_VALUE),
m_ThreadId(0L),
m_bRunning(false),
m_pThreadUserData(NULL)
{
	m_refThreadDataMutex = Nyx::CMutex::Alloc();
}


/**
 *
 */
NyxWin32::CThread_Impl::~CThread_Impl()
{
	Stop();
}


/**
 *
 */
Nyx::NyxResult NyxWin32::CThread_Impl::Start(Nyx::CThreadProc* pTProc)
{
	Nyx::NyxResult		ret = Nyx::kNyxRes_Success;

	m_refThreadProc = pTProc;

	m_hThread = ::CreateThread(NULL, 0, NyxWin32::CThread_Impl::ThreadEntryPoint, this, 0, &m_ThreadId);

	return ret;
}


/**
 *
 */
void NyxWin32::CThread_Impl::Stop()
{
	HANDLE					hThread = INVALID_HANDLE_VALUE;
	Nyx::CThreadProcRef		refThreadProc;

	{
		Nyx::TLock<Nyx::CMutex>		Lock(m_refThreadDataMutex, true);

		hThread = m_hThread;
		refThreadProc = m_refThreadProc;

	}

	if ( m_bRunning )
	{
		refThreadProc->Stop();
		WaitForSingleObject(hThread, INFINITE);
	}
}


/**
 *
 */
bool NyxWin32::CThread_Impl::IsRunning() const
{
	return m_bRunning;
}


/**
 *
 */
void NyxWin32::CThread_Impl::SetThreadUserData(void* pData)
{
	m_pThreadUserData = pData;
}


/**
 *
 */
void* NyxWin32::CThread_Impl::GetThreadUserData()
{
	return Nyx::CModule::GetDefault()->Threads().GetThreadUserData();
}


/**
 *
 */
DWORD WINAPI NyxWin32::CThread_Impl::ThreadEntryPoint( void* pParam )
{
	Nyx::CTraceCompositorRef	refTraceCompositor;

	if ( NULL != Nyx::CModule::GetDefault()->Traces().Reference() )
		refTraceCompositor = Nyx::CModule::GetDefault()->Traces().Reference()->Clone();

	NyxWin32::CThread_Impl*		pThreadImpl = reinterpret_cast<NyxWin32::CThread_Impl*>(pParam);

	Nyx::CModule::GetDefault()->Threads().SetThreadUserData(pThreadImpl->m_pThreadUserData);

	pThreadImpl->m_bRunning = true;

	pThreadImpl->m_refThreadProc->Run();
	
	{
		Nyx::TLock<Nyx::CMutex>		Lock(pThreadImpl->m_refThreadDataMutex, true);
		pThreadImpl->m_refThreadProc = NULL;
		
		pThreadImpl->m_bRunning = false;
		CloseHandle(pThreadImpl->m_hThread);
		pThreadImpl->m_hThread = INVALID_HANDLE_VALUE;
		pThreadImpl->m_ThreadId = 0;
	}

	return 0;
}
