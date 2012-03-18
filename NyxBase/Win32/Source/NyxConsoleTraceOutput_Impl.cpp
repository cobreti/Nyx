#include "NyxConsoleTraceOutput_Impl.hpp"
#include "NyxLock.hpp"

#include <wchar.h>

/**
 *
 */
Nyx::CConsoleTraceOutputRef Nyx::CConsoleTraceOutput::Alloc()
{
	return new NyxWin32::CConsoleTraceOutput_Impl();
}


/**
 *
 */
NyxWin32::CConsoleTraceOutput_Impl::CConsoleTraceOutput_Impl() :
m_hConsole(NULL),
m_bOwnConsole(false),
m_wszNewLine(L"\n"),
m_dwNewLineSize(0)
{
	m_dwNewLineSize = (DWORD)wcslen(m_wszNewLine);
	m_hConsole = ::GetStdHandle(STD_OUTPUT_HANDLE);
	if ( NULL == m_hConsole )
	{
		AllocConsole();
		m_hConsole = ::GetStdHandle(STD_OUTPUT_HANDLE);
		m_bOwnConsole = true;
	}

	m_refMutex = Nyx::CMutex::Alloc();
}


/**
 *
 */
NyxWin32::CConsoleTraceOutput_Impl::~CConsoleTraceOutput_Impl()
{
	if ( m_bOwnConsole )
	{
		FreeConsole();
	}
}


/**
 *
 */
void NyxWin32::CConsoleTraceOutput_Impl::Write(const Nyx::CTraceHeader& header, const wchar_t *wszText)
{
	Nyx::TLock<Nyx::CMutex>		Lock(m_refMutex, true);

	DWORD		dwWritten(0);

	m_Header.Clear();
	m_Header += "[";
	m_Header += header.ThreadId().c_str();
	m_Header += "] [";
	m_Header += header.TickCount().c_str();
	m_Header += "] : ";

	::WriteConsoleW(m_hConsole, m_Header.c_str(), (DWORD)m_Header.Length(), &dwWritten, NULL);
	::WriteConsoleW(m_hConsole, wszText, (DWORD)wcslen(wszText), &dwWritten, NULL);
	::WriteConsoleW(m_hConsole, m_wszNewLine, m_dwNewLineSize, &dwWritten, NULL);
}


/**
 *
 */
void NyxWin32::CConsoleTraceOutput_Impl::Write(const Nyx::CTraceHeader& header, const char* szText)
{
	Nyx::TLock<Nyx::CMutex>		Lock(m_refMutex, true);

	DWORD		dwWritten(0);

	m_Header.Clear();
	m_Header += "[";
	m_Header += header.ThreadId().c_str();
	m_Header += "] [";
	m_Header += header.TickCount().c_str();
	m_Header += "] : ";

	::WriteConsoleW(m_hConsole, m_Header.c_str(), (DWORD)m_Header.Length(), &dwWritten, NULL);
	::WriteConsoleA(m_hConsole, szText, (DWORD)strlen(szText), &dwWritten, NULL);
	::WriteConsoleW(m_hConsole, m_wszNewLine, m_dwNewLineSize, &dwWritten, NULL);
}

