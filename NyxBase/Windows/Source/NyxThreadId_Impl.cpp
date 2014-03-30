#include "NyxThreadId_Impl.hpp"


/**
 *
 */
Nyx::CThreadIdRef Nyx::CThreadId::GetCurrent()
{
    return new NyxWin32::CThreadId_Impl();
}


/**
 *
 */
NyxWin32::CThreadId_Impl::CThreadId_Impl()
{
    m_id = GetCurrentThreadId();
}


/**
 *
 */
NyxWin32::CThreadId_Impl::~CThreadId_Impl()
{
}


bool NyxWin32::CThreadId_Impl::IsCurrent() const
{
    return GetCurrentThreadId() == m_id;
}
