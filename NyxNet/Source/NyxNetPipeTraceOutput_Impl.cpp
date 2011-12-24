#include "NyxNetPipeTraceOutput_Impl.hpp"
#include "NyxNetNxStreamRW.hpp"


NyxNet::CPipeTraceOutputRef NyxNet::CPipeTraceOutput::Alloc(const char* szName)
{
	return new NyxNet::CPipeTraceOutput_Impl(szName);
}


/**
 *
 */
NyxNet::CPipeTraceOutput_Impl::CPipeTraceOutput_Impl(const char* szName)
{
	m_PipeName = szName;
	m_PipeName += "_Pipe";

	m_refSocket = NyxNet::CPipeSocketWriter::Alloc();
	m_refSocket->Create(m_PipeName.c_str());

	m_refConnection = NyxNet::CNxConnection::Alloc();
	m_refConnection->Open(m_refSocket);

    m_TraceStreamWriter.Init(m_refConnection);
    
	m_refSocket->Connect();
}


/**
 *
 */
NyxNet::CPipeTraceOutput_Impl::~CPipeTraceOutput_Impl()
{
	m_refSocket->Disconnect();
}


/**
 *
 */
void NyxNet::CPipeTraceOutput_Impl::Write( const Nyx::CTraceHeader& header, const wchar_t* wszText )
{
    m_TraceStreamWriter.Write(header, wszText);
}


/**
 *
 */
void NyxNet::CPipeTraceOutput_Impl::Write( const Nyx::CTraceHeader& header, const char* szText )
{
    m_TraceStreamWriter.Write(header, szText);
}
