#include "NyxModule_Impl.hpp"


Nyx::CModule* NyxWin32::CModule_Impl::s_pDefaultModule = NULL;


/**
 *
 */
Nyx::CModuleRef Nyx::CModule::Alloc()
{
	return new NyxWin32::CModule_Impl();
}


/**
 *
 */
Nyx::CModule* Nyx::CModule::GetDefault()
{
	return NyxWin32::CModule_Impl::s_pDefaultModule;
}


/**
 *
 */
NyxWin32::CModule_Impl::CModule_Impl()
{
	s_pDefaultModule = this;
	Init();
}


/**
 *
 */
NyxWin32::CModule_Impl::~CModule_Impl()
{
	Terminate();
	s_pDefaultModule = NULL;
}


/**
 *
 */
void NyxWin32::CModule_Impl::Init()
{
	m_ThreadModule.Init();
	m_TraceModule.Init();
}


/**
 *
 */
void NyxWin32::CModule_Impl::Terminate()
{
	m_TraceModule.Terminate();
	m_ThreadModule.Terminate();
}


/**
 *
 */
Nyx::CTraceModule& NyxWin32::CModule_Impl::Traces()
{
	return m_TraceModule;
}


/**
 *
 */
Nyx::CThreadModule& NyxWin32::CModule_Impl::Threads()
{
	return m_ThreadModule;
}
