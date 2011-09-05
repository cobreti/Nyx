#include <NyxTraceStream.hpp>

#include "NyxThreadModule_Impl.hpp"


/**
 *
 */
NyxOSX::CThreadModule_Impl::CThreadModule_Impl()
{
}


/**
 *
 */
NyxOSX::CThreadModule_Impl::~CThreadModule_Impl()
{
}


/**
 *
 */
void NyxOSX::CThreadModule_Impl::Init()
{
	pthread_key_create(&m_keyThreadUserData, NULL);
}


/**
 *
 */
void NyxOSX::CThreadModule_Impl::Terminate()
{
	pthread_key_delete(m_keyThreadUserData);
}


/**
 *
 */
void* NyxOSX::CThreadModule_Impl::GetThreadUserData()
{
	return pthread_getspecific(m_keyThreadUserData);
}


/**
 *
 */
void NyxOSX::CThreadModule_Impl::SetThreadUserData(void* pUserData)
{
	pthread_setspecific(m_keyThreadUserData, pUserData);
}


