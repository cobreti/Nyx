#include "NyxNetTcpIpClientConn.hpp"
#include "NyxStreamHandler.hpp"

/**
 *
 */
NyxNetWin32::CTcpIpClientConn::CTcpIpClientConn(	NyxNet::CTcpIpSocketRef refConnSocket ) :
m_refConnSocket(refConnSocket),
m_pConnectionHandler(NULL)
{
}


/**
 *
 */
NyxNetWin32::CTcpIpClientConn::~CTcpIpClientConn()
{
	if ( m_pConnectionHandler != NULL )
		m_pConnectionHandler->OnConnectionTerminated( static_cast<NyxNet::IConnection*>(this) );
}


/**
 *
 */
void NyxNetWin32::CTcpIpClientConn::SetConnectionHandler( NyxNet::IConnectionHandler* pConnHandler )
{
	m_pConnectionHandler = pConnHandler;
}


/**
 *
 */
Nyx::NyxResult NyxNetWin32::CTcpIpClientConn::Execute()
{
	Nyx::NyxResult		res = Nyx::kNyxRes_Success;
	
	m_pConnectionHandler->HandleStream( static_cast<Nyx::IStreamRW&>(*this) );
	
	m_pConnectionHandler->OnConnectionTerminated( static_cast<NyxNet::IConnection*>(this) );
	m_pConnectionHandler = NULL;
	
	return res;
}


/**
 *
 */
Nyx::NyxResult NyxNetWin32::CTcpIpClientConn::Stop()
{
	Nyx::NyxResult		res = Nyx::kNyxRes_Success;
	
	m_refConnSocket->Disconnect();
	
	return res;
}


/**
 *
 */
Nyx::NyxResult NyxNetWin32::CTcpIpClientConn::Read(	void* pBuffer,
													const Nyx::NyxSize& SizeToRead,
													Nyx::NyxSize& SizeRead )
{
	return m_refConnSocket->Read(pBuffer, SizeToRead, SizeRead);
}


/**
 *
 */		
Nyx::NyxResult NyxNetWin32::CTcpIpClientConn::Write(	void* pBuffer,
													const Nyx::NyxSize& SizeToWrite,
													Nyx::NyxSize& SizeWritten )
{
	return m_refConnSocket->Write(pBuffer, SizeToWrite, SizeWritten);
}


/**
 *
 */
void NyxNetWin32::CTcpIpClientConn::Close()
{
	Stop();
}


/**
 *
 */
NyxNet::CSocketRef NyxNetWin32::CTcpIpClientConn::Socket()
{
    return (NyxNet::CSocket*)m_refConnSocket;
}
