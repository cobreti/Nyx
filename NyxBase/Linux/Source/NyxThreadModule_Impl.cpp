#include <NyxTraceStream.hpp>

#include "NyxThreadModule_Impl.hpp"


/**
 *
 */
NyxLinux::CThreadModule_Impl::CThreadModule_Impl()
{
}


/**
 *
 */
NyxLinux::CThreadModule_Impl::~CThreadModule_Impl()
{
}


/**
 *
 */
void NyxLinux::CThreadModule_Impl::Init()
{
	pthread_key_create(&m_keyThreadUserData, NULL);
}


/**
 *
 */
void NyxLinux::CThreadModule_Impl::Terminate()
{
	pthread_key_delete(m_keyThreadUserData);
}


/**
 *
 */
void* NyxLinux::CThreadModule_Impl::GetThreadUserData()
{
	return pthread_getspecific(m_keyThreadUserData);
}


/**
 *
 */
void NyxLinux::CThreadModule_Impl::SetThreadUserData(void* pUserData)
{
	pthread_setspecific(m_keyThreadUserData, pUserData);
}


