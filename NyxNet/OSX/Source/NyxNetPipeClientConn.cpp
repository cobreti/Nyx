#include "NyxNetPipeClientConn.hpp"


/**
 *
 */
NyxNetOSX::CPipeClientConn::CPipeClientConn( NyxNet::CPipeSocketReaderRef refSocket ) :
m_refSocket(refSocket),
m_pConnectionHandler(NULL)
{
}


/**
 *
 */
NyxNetOSX::CPipeClientConn::~CPipeClientConn()
{
	if ( m_pConnectionHandler != NULL )
		m_pConnectionHandler->OnConnectionTerminated( static_cast<NyxNet::IConnection*>(this) );
}


/**
 *
 */
void NyxNetOSX::CPipeClientConn::SetConnectionHandler( NyxNet::IConnectionHandler* pConnHandler )
{
	m_pConnectionHandler = pConnHandler;
}


/**
 *
 */
Nyx::NyxResult NyxNetOSX::CPipeClientConn::Execute()
{
	Nyx::NyxResult		res = Nyx::kNyxRes_Success;

	m_refSocket->Connect();

	m_pConnectionHandler->HandleStream( static_cast<Nyx::IStreamRW&>(*this) );
	m_pConnectionHandler->OnConnectionTerminated( static_cast<NyxNet::IConnection*>(this) );
	m_pConnectionHandler = NULL;

	m_refSocket->Disconnect();

	return res;
}


/**
 *
 */
Nyx::NyxResult NyxNetOSX::CPipeClientConn::Stop()
{
	Nyx::NyxResult		res = Nyx::kNyxRes_Success;

	m_refSocket->Disconnect();

	return res;
}


/**
 *
 */
Nyx::NyxResult NyxNetOSX::CPipeClientConn::Read(	void* pBuffer,
													const Nyx::NyxSize& SizeToRead,
													Nyx::NyxSize& SizeRead )
{
	return m_refSocket->Read(pBuffer, SizeToRead, SizeRead);
}


/**
 *
 */
Nyx::NyxResult NyxNetOSX::CPipeClientConn::Write(	void* pBuffer,
													const Nyx::NyxSize& SizeToWrite,
													Nyx::NyxSize& SizeWritten )
{
	return Nyx::kNyxRes_Failure;
}


/**
 *
 */
void NyxNetOSX::CPipeClientConn::Close()
{
	Stop();
}


/**
 *
 */
NyxNet::CSocketRef NyxNetOSX::CPipeClientConn::Socket()
{
    return (NyxNet::CSocket*)m_refSocket;
}
