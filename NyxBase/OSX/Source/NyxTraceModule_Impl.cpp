#include "NyxTraceModule_Impl.hpp"


/**
 *
 */
NyxOSX::CTraceModule_Impl::CTraceModule_Impl() :
m_pReference(NULL)
{
}


/**
 *
 */
NyxOSX::CTraceModule_Impl::~CTraceModule_Impl()
{
}


/**
 *
 */
void NyxOSX::CTraceModule_Impl::Init()
{
	pthread_key_create(&m_keyTraceCompositor, NULL);
}


/**
 *
 */
void NyxOSX::CTraceModule_Impl::Terminate()
{
	pthread_key_delete(m_keyTraceCompositor);
}


/**
 *
 */
Nyx::CTraceCompositor* NyxOSX::CTraceModule_Impl::Reference()
{
	return m_pReference;
}


/**
 *
 */
void NyxOSX::CTraceModule_Impl::SetThreadDefault( Nyx::CTraceCompositor* pDefault )
{
	if ( NULL != pDefault )
	{
		pthread_setspecific(m_keyTraceCompositor, pDefault);
		
		if ( m_pReference == NULL )
			m_pReference = pDefault;
	}
}


/**
 *
 */
Nyx::CTraceCompositor* NyxOSX::CTraceModule_Impl::ThreadDefault()
{
	Nyx::CTraceCompositor*	pTraceCompositor = reinterpret_cast<Nyx::CTraceCompositor*>(pthread_getspecific(m_keyTraceCompositor));
	return pTraceCompositor;
}


/**
 *
 */
void NyxOSX::CTraceModule_Impl::RemoveThreadDefault()
{
	Nyx::CTraceCompositor*	pTraceCompositor = reinterpret_cast<Nyx::CTraceCompositor*>(pthread_getspecific(m_keyTraceCompositor));
	if (NULL != pTraceCompositor )
	{
		if ( pTraceCompositor == m_pReference )
			m_pReference = NULL;
	}
	pthread_setspecific(m_keyTraceCompositor, NULL);
}

