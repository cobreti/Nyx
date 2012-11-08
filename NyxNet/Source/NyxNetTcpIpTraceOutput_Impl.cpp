#include "NyxNetTcpIpTraceOutput_Impl.hpp"
#include "NyxNetNxStreamRW.hpp"


NyxNet::CTcpIpTraceOutputRef NyxNet::CTcpIpTraceOutput::Alloc(const char* szName, const char* addr, const Nyx::UInt32 port, bool bUseHandshake )
{
	return new NyxNet::CTcpIpTraceOutput_Impl(szName, addr, port, bUseHandshake);
}


/**
 *
 */
NyxNet::CTcpIpTraceOutput_Impl::CTcpIpTraceOutput_Impl(const char* szName, const char* addr, const Nyx::UInt32 port, bool bUseHandshake )
{
	m_Name = szName;
    m_Addr = addr;
    
	m_refSocket = NyxNet::CTcpIpSocket::Alloc();
	m_refSocket->Create(m_Addr.c_str(), port);
    
	m_refConnection = NyxNet::CNxConnection::Alloc();
    m_refConnection->SetUseHandshake(bUseHandshake);
	m_refConnection->Open(m_refSocket);
    
    m_TraceStreamWriter.Init(m_refConnection);
    
	m_refSocket->Connect();
}


/**
 *
 */
NyxNet::CTcpIpTraceOutput_Impl::~CTcpIpTraceOutput_Impl()
{
	m_refSocket->Disconnect();
}


/**
 *
 */
void NyxNet::CTcpIpTraceOutput_Impl::Write( const Nyx::CTraceHeader& header, const wchar_t* wszText )
{
    m_TraceStreamWriter.Write(m_Name, header, wszText);
}


/**
 *
 */
void NyxNet::CTcpIpTraceOutput_Impl::Write( const Nyx::CTraceHeader& header, const char* szText )
{
    m_TraceStreamWriter.Write(m_Name, header, szText);
}
