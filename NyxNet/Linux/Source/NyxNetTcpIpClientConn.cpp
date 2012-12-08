#include "NyxNetTcpIpClientConn.hpp"
#include "NyxStreamHandler.hpp"
#include "NyxTraceStream.hpp"

/**
 *
 */
NyxNetLinux::CTcpIpClientConn::CTcpIpClientConn(	NyxNet::CTcpIpSocketRef refConnSocket ) :
m_refConnSocket(refConnSocket),
m_pConnectionHandler(NULL)
{
}


/**
 *
 */
NyxNetLinux::CTcpIpClientConn::~CTcpIpClientConn()
{
	if ( m_pConnectionHandler != NULL )
		m_pConnectionHandler->OnConnectionTerminated(static_cast<NyxNet::IConnection*>(this));
}


/**
 *
 */
void NyxNetLinux::CTcpIpClientConn::SetConnectionHandler( NyxNet::IConnectionHandler* pConnHandler )
{
	m_pConnectionHandler = pConnHandler;
}


/**
 *
 */
Nyx::NyxResult NyxNetLinux::CTcpIpClientConn::Execute()
{
	Nyx::NyxResult		res = Nyx::kNyxRes_Success;
	
	m_pConnectionHandler->HandleStream( static_cast<Nyx::IStreamRW&>(*this) );
	
	m_pConnectionHandler->OnConnectionTerminated(static_cast<NyxNet::IConnection*>(this));
	m_pConnectionHandler = NULL;
	
	return res;
}


/**
 *
 */
Nyx::NyxResult NyxNetLinux::CTcpIpClientConn::Stop()
{
	Nyx::NyxResult		res = Nyx::kNyxRes_Success;
	
	m_refConnSocket->Disconnect();
	
	return res;
}


/**
 *
 */
Nyx::NyxResult NyxNetLinux::CTcpIpClientConn::Read(	void* pBuffer,
													const Nyx::NyxSize& SizeToRead,
													Nyx::NyxSize& SizeRead )
{
	return m_refConnSocket->Read(pBuffer, SizeToRead, SizeRead);
}


/**
 *
 */		
Nyx::NyxResult NyxNetLinux::CTcpIpClientConn::Write(	void* pBuffer,
													const Nyx::NyxSize& SizeToWrite,
													Nyx::NyxSize& SizeWritten )
{
	return m_refConnSocket->Write(pBuffer, SizeToWrite, SizeWritten);
}


/**
 *
 */
void NyxNetLinux::CTcpIpClientConn::Close()
{
	Stop();
}


/**
 *
 */
NyxNet::CSocketRef NyxNetLinux::CTcpIpClientConn::Socket()
{
	return (NyxNet::CSocket*)m_refConnSocket;
}
