#include "NyxConsoleTraceOutput_Impl.hpp"
#include "NyxLock.hpp"
#include "NyxTraceHeader.hpp"
#include <wchar.h>


/**
 *
 */
Nyx::CConsoleTraceOutputRef Nyx::CConsoleTraceOutput::Alloc()
{
	return new NyxLinux::CConsoleTraceOutput_Impl();
}


/**
 *
 */
NyxLinux::CConsoleTraceOutput_Impl::CConsoleTraceOutput_Impl()
{
	m_refMutex = Nyx::CMutex::Alloc();
}


/**
 *
 */
NyxLinux::CConsoleTraceOutput_Impl::~CConsoleTraceOutput_Impl()
{
}


/**
 *
 */
void NyxLinux::CConsoleTraceOutput_Impl::Write( const Nyx::CTraceHeader& header, const wchar_t* wszText )
{
	Nyx::TLock<Nyx::CMutex>		Lock(m_refMutex, true);
	
	m_Header.Clear();
	m_Header += "[";
	m_Header += (const char*)header.ThreadId();
	m_Header += "] [";
	m_Header += (const char*)header.TickCount();
	m_Header += "] : ";
	
	wprintf(L"%S", (const wchar_t*)m_Header);
	wprintf(L"%S\n", wszText);
	fflush(stdout);
}


/**
 *
 */
void NyxLinux::CConsoleTraceOutput_Impl::Write( const Nyx::CTraceHeader& header, const char* szText )
{
	Nyx::TLock<Nyx::CMutex>		Lock(m_refMutex, true);
	
	m_Header.Clear();
	m_Header += "[";
	m_Header += (const char*)header.ThreadId();
	m_Header += "] [";
	m_Header += (const char*)header.TickCount();
	m_Header += "] : ";
	
	printf("%S", (const wchar_t*)m_Header);
	printf("%s\n", szText);
	fflush(stdout);
}
