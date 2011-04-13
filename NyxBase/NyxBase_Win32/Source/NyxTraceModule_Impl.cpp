#include "NyxTraceModule_Impl.hpp"


/**
 *
 */
NyxWin32::CTraceModule_Impl::CTraceModule_Impl() : 
m_TlsIndex(0),
m_pReference(NULL)
{
}


/**
 *
 */
NyxWin32::CTraceModule_Impl::~CTraceModule_Impl()
{
}


/**
 *
 */
void NyxWin32::CTraceModule_Impl::Init()
{
	m_TlsIndex = TlsAlloc();
}


/**
 *
 */
void NyxWin32::CTraceModule_Impl::Terminate()
{
	RemoveThreadDefault();
	TlsFree(m_TlsIndex);
	m_TlsIndex = 0;
}


/**
 *
 */
Nyx::CTraceCompositor* NyxWin32::CTraceModule_Impl::Reference()
{
	return m_pReference;
}


/**
 *
 */
void NyxWin32::CTraceModule_Impl::SetThreadDefault( Nyx::CTraceCompositor* pDefault )
{
	if ( NULL != pDefault )
	{
		TlsSetValue(m_TlsIndex, pDefault);
		
		if ( m_pReference == NULL )
			m_pReference = pDefault;
	}
}


/**
 *
 */
Nyx::CTraceCompositor* NyxWin32::CTraceModule_Impl::ThreadDefault()
{
	Nyx::CTraceCompositor*	pTraceCompositor = reinterpret_cast<Nyx::CTraceCompositor*>(TlsGetValue(m_TlsIndex));
	return pTraceCompositor;
}


/**
 *
 */
void NyxWin32::CTraceModule_Impl::RemoveThreadDefault()
{
	Nyx::CTraceCompositor*	pTraceCompositor = reinterpret_cast<Nyx::CTraceCompositor*>(TlsGetValue(m_TlsIndex));
	if (NULL != pTraceCompositor )
	{
		if ( pTraceCompositor == m_pReference )
			m_pReference = NULL;
	}
	TlsSetValue(m_TlsIndex, NULL);
}

