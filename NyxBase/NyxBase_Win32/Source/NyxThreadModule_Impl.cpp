#include "NyxThreadModule_Impl.hpp"

/**
 *
 */
NyxWin32::CThreadModule_Impl::CThreadModule_Impl() :
m_TlsIndex(0)
{
}


/**
 *
 */
NyxWin32::CThreadModule_Impl::~CThreadModule_Impl()
{
}


/**
 *
 */
void NyxWin32::CThreadModule_Impl::Init()
{
	m_TlsIndex = TlsAlloc();
}


/**
 *
 */
void NyxWin32::CThreadModule_Impl::Terminate()
{
	TlsFree(m_TlsIndex);
	m_TlsIndex = 0;
}


/**
 *
 */
void* NyxWin32::CThreadModule_Impl::GetThreadUserData()
{
	return TlsGetValue(m_TlsIndex);
}


void NyxWin32::CThreadModule_Impl::SetThreadUserData(void* pData)
{
	TlsSetValue(m_TlsIndex, pData);
}
