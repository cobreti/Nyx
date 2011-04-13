#ifndef _NYXCONSOLETRACEOUTPUT_IMPL_HPP_
#define _NYXCONSOLETRACEOUTPUT_IMPL_HPP_

#include "NyxConsoleTraceOutput.hpp"
#include "NyxObject_Impl.hpp"
#include "NyxMutex.hpp"
#include "NyxFixedString.hpp"

#include <Windows.h>

namespace NyxWin32
{
	class CConsoleTraceOutput_Impl : public Nyx::CObject_Impl<Nyx::CConsoleTraceOutput>
	{
	public:
		CConsoleTraceOutput_Impl();
		virtual ~CConsoleTraceOutput_Impl();

	public:
		virtual void Write( const Nyx::CTraceHeader& header, const wchar_t* wszText );
		virtual void Write( const Nyx::CTraceHeader& header, const char* szText );

	protected:

		HANDLE				m_hConsole;
		bool				m_bOwnConsole;
		wchar_t*			m_wszNewLine;
		DWORD				m_dwNewLineSize;
		Nyx::CMutexRef		m_refMutex;

		Nyx::TFixedString<wchar_t, 200>		m_Header;
	};
}


#endif

