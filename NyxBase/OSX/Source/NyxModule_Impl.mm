#include "NyxModule_Impl.hpp"
#include "NyxTraceStream.hpp"

Nyx::CModule* NyxLinux::CModule_Impl::s_pDefaultModule = NULL;


/**
 *
 */
Nyx::CModuleRef Nyx::CModule::Alloc()
{
	return new NyxLinux::CModule_Impl();
}


/**
 *
 */
Nyx::CModule* Nyx::CModule::GetDefault()
{
	return NyxLinux::CModule_Impl::s_pDefaultModule;
}


/**
 *
 */
NyxLinux::CModule_Impl::CModule_Impl()
{
	s_pDefaultModule = this;
	Init();
}


/**
 *
 */
NyxLinux::CModule_Impl::~CModule_Impl()
{
	Terminate();
	s_pDefaultModule = NULL;
}


/**
 *
 */
void NyxLinux::CModule_Impl::Init()
{
	m_ThreadModule.Init();
	m_TraceModule.Init();
    
}


/**
 *
 */
void NyxLinux::CModule_Impl::Terminate()
{
	m_TraceModule.Terminate();
	m_ThreadModule.Terminate();
}


/**
 *
 */
Nyx::CTraceModule& NyxLinux::CModule_Impl::Traces()
{
	return m_TraceModule;
}


/**
 *
 */
Nyx::CThreadModule& NyxLinux::CModule_Impl::Threads()
{
	return m_ThreadModule;
}


