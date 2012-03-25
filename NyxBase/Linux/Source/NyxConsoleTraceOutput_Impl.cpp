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
	m_Header += header.ThreadId().c_str();
	m_Header += "] [";
	m_Header += header.TickCount().c_str();
	m_Header += "] : ";
	
	wprintf(L"%S", m_Header.c_str());
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
	m_Header += header.ThreadId().c_str();
	m_Header += "] [";
	m_Header += header.TickCount().c_str();
	m_Header += "] : ";
	
	printf("%S", m_Header.c_str());
	printf("%s\n", szText);
	fflush(stdout);
}
