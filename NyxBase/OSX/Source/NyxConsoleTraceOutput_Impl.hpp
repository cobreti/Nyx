#ifndef _NYXCONSOLETRACEOUTPUT_IMPL_HPP_
#define _NYXCONSOLETRACEOUTPUT_IMPL_HPP_

#include "NyxConsoleTraceOutput.hpp"
#include "NyxObject_Impl.hpp"
#include "NyxMutex.hpp"
#include "NyxFixedString.hpp"

namespace NyxOSX
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
	
		Nyx::CMutexRef							m_refMutex;
		Nyx::TFixedString<wchar_t, 200>			m_Header;
	};
}


#endif // _NYXCONSOLETRACEOUTPUT_IMPL_HPP_
