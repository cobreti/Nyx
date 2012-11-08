#ifndef _NYXNETTCPIPTRACEOUTPUT_IMPL_HPP_
#define _NYXNETTCPIPTRACEOUTPUT_IMPL_HPP_


#include <Nyx.hpp>
#include <NyxNet.hpp>

#include "NyxNetTcpIpTraceOutput.hpp"
#include "NyxObject_Impl.hpp"
#include "NyxNetNxConnection.hpp"
#include "NyxNetTraceStreamWriter.hpp"


namespace NyxNet
{
	class CTcpIpTraceOutput_Impl : public Nyx::CObject_Impl<NyxNet::CTcpIpTraceOutput>
	{
	public:
		CTcpIpTraceOutput_Impl(const char* szName, const char* addr, const Nyx::UInt32 port, bool bUseHandshake );
		virtual ~CTcpIpTraceOutput_Impl();
        
		virtual void Write( const Nyx::CTraceHeader& header, const wchar_t* wszText );
		virtual void Write( const Nyx::CTraceHeader& header, const char* szText );
        
	protected:
        
		Nyx::CAString                       m_Name;
        Nyx::CAString                       m_Addr;
		NyxNet::CNxConnectionRef			m_refConnection;
        NyxNet::CTcpIpSocketRef             m_refSocket;
        NyxNet::CTraceStreamWriter          m_TraceStreamWriter;
	};
}


#endif // _NYXNETTCPIPTRACEOUTPUT_IMPL_HPP_
