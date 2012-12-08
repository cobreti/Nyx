#include "NyxNetPipeClientConn.hpp"


/**
 *
 */
NyxNetLinux::CPipeClientConn::CPipeClientConn( NyxNet::CPipeSocketReaderRef refSocket ) :
m_refSocket(refSocket),
m_pConnectionHandler(NULL)
{
}


/**
 *
 */
NyxNetLinux::CPipeClientConn::~CPipeClientConn()
{
	if ( m_pConnectionHandler != NULL )
		m_pConnectionHandler->OnConnectionTerminated( static_cast<NyxNet::IConnection*>(this) );
}


/**
 *
 */
void NyxNetLinux::CPipeClientConn::SetConnectionHandler( NyxNet::IConnectionHandler* pConnHandler )
{
	m_pConnectionHandler = pConnHandler;
}


/**
 *
 */
Nyx::NyxResult NyxNetLinux::CPipeClientConn::Execute()
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
Nyx::NyxResult NyxNetLinux::CPipeClientConn::Stop()
{
	Nyx::NyxResult		res = Nyx::kNyxRes_Success;

	m_refSocket->Disconnect();

	return res;
}


/**
 *
 */
Nyx::NyxResult NyxNetLinux::CPipeClientConn::Read(	void* pBuffer,
													const Nyx::NyxSize& SizeToRead,
													Nyx::NyxSize& SizeRead )
{
	return m_refSocket->Read(pBuffer, SizeToRead, SizeRead);
}


/**
 *
 */
Nyx::NyxResult NyxNetLinux::CPipeClientConn::Write(	void* pBuffer,
													const Nyx::NyxSize& SizeToWrite,
													Nyx::NyxSize& SizeWritten )
{
	return Nyx::kNyxRes_Failure;
}


/**
 *
 */
void NyxNetLinux::CPipeClientConn::Close()
{
	Stop();
}


/**
 *
 */
NyxNet::CSocketRef NyxNetLinux::CPipeClientConn::Socket()
{
	return (NyxNet::CSocket*)m_refSocket;
}
