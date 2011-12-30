#include "NyxModule_Impl.hpp"
#include "NyxTraceStream.hpp"

Nyx::CModule* NyxOSX::CModule_Impl::s_pDefaultModule = NULL;


/**
 *
 */
Nyx::CModuleRef Nyx::CModule::Alloc()
{
	return new NyxOSX::CModule_Impl();
}


/**
 *
 */
Nyx::CModule* Nyx::CModule::GetDefault()
{
	return NyxOSX::CModule_Impl::s_pDefaultModule;
}


/**
 *
 */
NyxOSX::CModule_Impl::CModule_Impl()
{
	s_pDefaultModule = this;
	Init();
}


/**
 *
 */
NyxOSX::CModule_Impl::~CModule_Impl()
{
	Terminate();
	s_pDefaultModule = NULL;
}


/**
 *
 */
void NyxOSX::CModule_Impl::Init()
{
	m_ThreadModule.Init();
	m_TraceModule.Init();
    
}


/**
 *
 */
void NyxOSX::CModule_Impl::Terminate()
{
	m_TraceModule.Terminate();
	m_ThreadModule.Terminate();
}


/**
 *
 */
Nyx::CTraceModule& NyxOSX::CModule_Impl::Traces()
{
	return m_TraceModule;
}


/**
 *
 */
Nyx::CThreadModule& NyxOSX::CModule_Impl::Threads()
{
	return m_ThreadModule;
}


