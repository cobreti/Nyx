#include "NyxNetTcpIpClientConn.hpp"
#include "NyxStreamHandler.hpp"

/**
 *
 */
NyxNetOSX::CTcpIpClientConn::CTcpIpClientConn(	NyxNet::CTcpIpSocketRef refConnSocket ) :
m_refConnSocket(refConnSocket),
m_pConnectionHandler(NULL)
{
}


/**
 *
 */
NyxNetOSX::CTcpIpClientConn::~CTcpIpClientConn()
{
	if ( m_pConnectionHandler != NULL )
		m_pConnectionHandler->OnConnectionTerminated(static_cast<NyxNet::IConnection*>(this));
}


/**
 *
 */
void NyxNetOSX::CTcpIpClientConn::SetConnectionHandler( NyxNet::IConnectionHandler* pConnHandler )
{
	m_pConnectionHandler = pConnHandler;
}


/**
 *
 */
Nyx::NyxResult NyxNetOSX::CTcpIpClientConn::Execute()
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
Nyx::NyxResult NyxNetOSX::CTcpIpClientConn::Stop()
{
	Nyx::NyxResult		res = Nyx::kNyxRes_Success;
	
	m_refConnSocket->Disconnect();
    m_pConnectionHandler->CloseConnection( static_cast<NyxNet::IConnection*>(this) );
	
	return res;
}


/**
 *
 */
Nyx::NyxResult NyxNetOSX::CTcpIpClientConn::Read(	void* pBuffer,
													const Nyx::NyxSize& SizeToRead,
													Nyx::NyxSize& SizeRead )
{
	return m_refConnSocket->Read(pBuffer, SizeToRead, SizeRead);
}


/**
 *
 */		
Nyx::NyxResult NyxNetOSX::CTcpIpClientConn::Write(	void* pBuffer,
													const Nyx::NyxSize& SizeToWrite,
													Nyx::NyxSize& SizeWritten )
{
	return m_refConnSocket->Write(pBuffer, SizeToWrite, SizeWritten);
}


/**
 *
 */
void NyxNetOSX::CTcpIpClientConn::Close()
{
	Stop();
}


/**
 *
 */
NyxNet::CSocketRef NyxNetOSX::CTcpIpClientConn::Socket()
{
    return (NyxNet::CSocket*)m_refConnSocket;
}
