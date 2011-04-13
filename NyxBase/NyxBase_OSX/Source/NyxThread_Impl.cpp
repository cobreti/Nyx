#include "NyxThread_Impl.hpp"

#include "NyxTraceStream.hpp"


/**
 *
 */
Nyx::CThreadRef Nyx::CThread::Alloc()
{
	return new NyxOSX::CThread_Impl();
}


/**
 *
 */
NyxOSX::CThread_Impl::CThread_Impl() :
m_bRunning(false)
{
}


/**
 *
 */
NyxOSX::CThread_Impl::~CThread_Impl()
{
	Stop();
}


/**
 *
 */
Nyx::NyxResult NyxOSX::CThread_Impl::Start(Nyx::CThreadProc* pTProc)
{
	Nyx::NyxResult		ret = Nyx::kNyxRes_Success;

	m_refThreadProc = pTProc;
	
	pthread_create(&m_ID, NULL, CThread_Impl::ThreadEntryPoint, this);

	return ret;
}


/**
 *
 */
void NyxOSX::CThread_Impl::Stop()
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
bool NyxOSX::CThread_Impl::IsRunning() const
{
	return m_bRunning;
}


/**
 *
 */
void NyxOSX::CThread_Impl::SetThreadUserData(void* pData)
{
}


/**
 *
 */
void* NyxOSX::CThread_Impl::GetThreadUserData()
{
	return NULL;
}


/**
 *
 */
void* NyxOSX::CThread_Impl::ThreadEntryPoint( void* pParam )
{
	NyxOSX::CThread_Impl*		pThreadImpl = reinterpret_cast<NyxOSX::CThread_Impl*>(pParam);
	Nyx::CTraceCompositorRef	refTraceCompositor;
	
	if ( NULL != Nyx::CModule::GetDefault()->Traces().Reference() )
		refTraceCompositor = Nyx::CModule::GetDefault()->Traces().Reference()->Clone();
		
	pThreadImpl->m_bRunning = true;
	
	pThreadImpl->m_refThreadProc->Run();
	
	pThreadImpl->m_refThreadProc = NULL;
	
	pThreadImpl->m_bRunning = false;
	
	return NULL;
}
