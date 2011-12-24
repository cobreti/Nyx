#ifndef _NYXNETPIPETRACEOUTPUT_IMPL_HPP_
#define _NYXNETPIPETRACEOUTPUT_IMPL_HPP_

#include <Nyx.hpp>

#include "NyxNetPipeTraceOutput.hpp"
#include "NyxObject_Impl.hpp"
#include "NyxNetPipeSocketWriter.hpp"
#include "NyxNetNxConnection.hpp"
#include "NyxNetTraceStreamWriter.hpp"


namespace NyxNet
{
	class CPipeTraceOutput_Impl : public Nyx::CObject_Impl<NyxNet::CPipeTraceOutput>
	{
	public:
		CPipeTraceOutput_Impl(const char* szName);
		virtual ~CPipeTraceOutput_Impl();

		virtual void Write( const Nyx::CTraceHeader& header, const wchar_t* wszText );
		virtual void Write( const Nyx::CTraceHeader& header, const char* szText );

	protected:

		Nyx::CAString                       m_PipeName;
		NyxNet::CPipeSocketWriterRef		m_refSocket;
		NyxNet::CNxConnectionRef			m_refConnection;
        NyxNet::CTraceStreamWriter          m_TraceStreamWriter;
	};
}


#endif // _NYXNETPIPETRACEOUTPUT_IMPL_HPP_
