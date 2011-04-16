#include "NyxThreadId_Impl.hpp"


/**
 *
 */
Nyx::CThreadIdRef Nyx::CThreadId::GetCurrent()
{
	return new NyxOSX::CThreadId_Impl();
}


/**
 *
 */
NyxOSX::CThreadId_Impl::CThreadId_Impl()
{
	m_id = pthread_self();
}


/**
 *
 */
NyxOSX::CThreadId_Impl::~CThreadId_Impl()
{
}


bool NyxOSX::CThreadId_Impl::IsCurrent() const
{
	return (0 != pthread_equal(m_id, pthread_self()));
}
