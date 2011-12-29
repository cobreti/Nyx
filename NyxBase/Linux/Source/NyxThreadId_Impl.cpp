#include "NyxThreadId_Impl.hpp"


/**
 *
 */
Nyx::CThreadIdRef Nyx::CThreadId::GetCurrent()
{
	return new NyxLinux::CThreadId_Impl();
}


/**
 *
 */
NyxLinux::CThreadId_Impl::CThreadId_Impl()
{
	m_id = pthread_self();
}


/**
 *
 */
NyxLinux::CThreadId_Impl::~CThreadId_Impl()
{
}


bool NyxLinux::CThreadId_Impl::IsCurrent() const
{
	return (0 != pthread_equal(m_id, pthread_self()));
}
