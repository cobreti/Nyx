#include "NyxThread_Impl.hpp"

#include "NyxTraceStream.hpp"


/**
 *
 */
Nyx::CThreadRef Nyx::CThread::Alloc()
{
	return new NyxLinux::CThread_Impl();
}


/**
 *
 */
NyxLinux::CThread_Impl::CThread_Impl() :
m_bRunning(false),
m_bThreadLoopStarted(false),
m_pThreadUserData(NULL)
{
	m_refInitializedEvent = Nyx::CEvent::Alloc();
}


/**
 *
 */
NyxLinux::CThread_Impl::~CThread_Impl()
{
	Stop();
}


/**
 *
 */
Nyx::NyxResult NyxLinux::CThread_Impl::Start(Nyx::CThreadProc* pTProc)
{
	Nyx::NyxResult		ret = Nyx::kNyxRes_Success;

	m_refThreadProc = pTProc;
	m_bThreadLoopStarted = false;
	
	pthread_create(&m_ID, NULL, CThread_Impl::ThreadEntryPoint, this);
	
    while ( !m_bThreadLoopStarted )
        m_refInitializedEvent->WaitSignaled(200);

	return ret;
}


/**
 *
 */
void NyxLinux::CThread_Impl::Stop()
{
	if ( m_bRunning )
	{
		m_refThreadProc->Stop();
		pthread_join(m_ID, NULL);
	}
}


/**
 *
 */
bool NyxLinux::CThread_Impl::IsRunning() const
{
	return m_bRunning;
}


/**
 *
 */
void NyxLinux::CThread_Impl::SetThreadUserData(void* pData)
{
	m_pThreadUserData = pData;
}


/**
 *
 */
void* NyxLinux::CThread_Impl::GetThreadUserData()
{
	return m_pThreadUserData;
}


/**
 *
 */
void* NyxLinux::CThread_Impl::ThreadEntryPoint( void* pParam )
{
	NyxLinux::CThread_Impl*		pThreadImpl = reinterpret_cast<NyxLinux::CThread_Impl*>(pParam);
	Nyx::CTraceCompositorRef	refTraceCompositor;
	
	if ( NULL != Nyx::CModule::GetDefault()->Traces().Reference() )
		refTraceCompositor = Nyx::CModule::GetDefault()->Traces().Reference()->Clone();

	Nyx::CModule::GetDefault()->Threads().SetThreadUserData(pThreadImpl->m_pThreadUserData);

	pThreadImpl->m_bRunning = true;
	
	pThreadImpl->m_refInitializedEvent->Signal(0);
	pThreadImpl->m_bThreadLoopStarted = true;
	
	pThreadImpl->m_refThreadProc->Run();
	
	pThreadImpl->m_refThreadProc = NULL;
	
	pThreadImpl->m_bRunning = false;

	return NULL;
}
