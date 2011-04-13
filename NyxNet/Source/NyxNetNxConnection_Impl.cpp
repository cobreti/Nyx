#include "NyxNetNxConnection_Impl.hpp"
//#include "NyxBodyBlock.hpp"
#include "NyxNetTypes.hpp"
#include "NyxStreamRW.hpp"
#include "NyxNetConnection.hpp"
#include "NyxLock.hpp"
#include "NyxTraceStream.hpp"

#include <stdio.h>

#pragma unmanaged


/**
 *
 */
NyxNet::CNxConnectionRef NyxNet::CNxConnection::Alloc()
{
	return new NyxNet::CNxConnection_Impl();
}


/**
 *
 */
NyxNet::CNxConnection_Impl::CNxConnection_Impl() :
m_pConnection(NULL),
m_pStreamRW(NULL),
m_ReceivedData(0),
m_bRunning(true),
m_HSTimeout(5000),
m_MissedHandshakes(0),
m_pConnectionHandler(NULL)
{
	m_refHSEvent = Nyx::CEvent::Alloc();
	m_refWriteMutex = Nyx::CMutex::Alloc();
	m_refReadMutex = Nyx::CMutex::Alloc();
}


/**
 *
 */
NyxNet::CNxConnection_Impl::CNxConnection_Impl(NyxNet::IConnection* pConnection) :
m_pConnection(pConnection),
m_pStreamRW(NULL),
m_ReceivedData(0),
m_bRunning(true),
m_HSTimeout(5000),
m_MissedHandshakes(0),
m_pConnectionHandler(NULL)
{
	m_refHSEvent = Nyx::CEvent::Alloc();
	m_refWriteMutex = Nyx::CMutex::Alloc();
	m_refReadMutex = Nyx::CMutex::Alloc();
}


/**
 *
 */
NyxNet::CNxConnection_Impl::~CNxConnection_Impl()
{
}


/**
 *
 */
void NyxNet::CNxConnection_Impl::SetConnectionHandler( NyxNet::INxConnectionHandler* pConnectionHandler )
{
	m_pConnectionHandler = pConnectionHandler;
}


/**
 *
 */
Nyx::NyxResult NyxNet::CNxConnection_Impl::BeginRead( NyxNet::NxDataType& datatype )
{
	Nyx::NyxResult		res = Nyx::kNyxRes_Success;
	Nyx::NyxSize		ReadSize;

	m_refReadMutex->Lock();

	do
	{
		res = m_pStreamRW->Read(&datatype, sizeof(datatype), ReadSize);

		if ( Nyx::Succeeded(res) )
		{
			++ m_ReceivedData;

			if ( datatype == NyxNet::eNxDT_HandShake )
			{
				Nyx::CTraceStream(0x0).Write(L"Received handshake");
			}
		}
	}
	while ( datatype == NyxNet::eNxDT_HandShake && Nyx::Succeeded(res) );

	m_bRunning = Nyx::Succeeded(res);

	if ( Nyx::Failed(res) )
		m_refReadMutex->Unlock();

	return res;
}


/**
 *
 */
Nyx::NyxResult NyxNet::CNxConnection_Impl::BeginReadSection( NyxNet::NxDataSize& size )
{
	Nyx::NyxResult		res = Nyx::kNyxRes_Success;
	Nyx::NyxSize		ReadSize;

	res = m_pStreamRW->Read(&size, sizeof(size), ReadSize);

	if ( Nyx::Succeeded(res) )
		++ m_ReceivedData;

	return res;
}


/**
 *
 */
Nyx::NyxResult NyxNet::CNxConnection_Impl::Read( void* pBuffer, const NyxNet::NxDataSize& size )
{
	Nyx::NyxResult		res = Nyx::kNyxRes_Success;
	Nyx::NyxSize		ReadSize(0);

	res = m_pStreamRW->Read(pBuffer, size, ReadSize);

	if ( Nyx::Succeeded(res) )
		++ m_ReceivedData;

	m_bRunning = Nyx::Succeeded(res);

	return res;
}


/**
 *
 */
void NyxNet::CNxConnection_Impl::EndReadSection()
{
}


/**
 *
 */
void NyxNet::CNxConnection_Impl::EndRead()
{
	m_refReadMutex->Unlock();
}


/**
 *
 */
Nyx::NyxResult NyxNet::CNxConnection_Impl::BeginWrite( const NyxNet::NxDataType& datatype )
{
	Nyx::NyxResult				res = Nyx::kNyxRes_Success;
	Nyx::NyxSize				WrittenSize(0);

	m_refWriteMutex->Lock();

	res = m_pStreamRW->Write( (void*)&datatype, sizeof(datatype), WrittenSize);
	if ( Nyx::Failed(res) )
	{
		m_SocketStream.Socket()->Disconnect();
		m_SocketStream.Socket()->Connect();

		res = m_pStreamRW->Write( (void*)&datatype, sizeof(datatype), WrittenSize);
	}

	if ( Nyx::Failed(res) )
		m_refWriteMutex->Unlock();			

	return res;
}


/**
 *
 */
Nyx::NyxResult NyxNet::CNxConnection_Impl::BeginWriteSection( const NyxNet::NxDataType& size )
{
	Nyx::NyxResult				res = Nyx::kNyxRes_Success;
	Nyx::NyxSize				WrittenSize(0);

	res = m_pStreamRW->Write( (void*)&size, sizeof(size), WrittenSize);

	if ( Nyx::Failed(res) )
		m_refWriteMutex->Unlock();			

	return res;
}


/**
 *
 */
Nyx::NyxResult NyxNet::CNxConnection_Impl::Write( void* pBuffer, const NyxNet::NxDataSize& DataSize )
{
	Nyx::NyxResult				res = Nyx::kNyxRes_Success;
	Nyx::NyxSize				WrittenSize(0);
	Nyx::TLock<Nyx::CMutex>		WriteLock(m_refWriteMutex, true);

	res = m_pStreamRW->Write( pBuffer, DataSize, WrittenSize );

	return res;
}


/**
 *
 */
void NyxNet::CNxConnection_Impl::EndWriteSection()
{
}


/**
 *
 */
void NyxNet::CNxConnection_Impl::EndWrite()
{
	m_refWriteMutex->Unlock();
}


/**
 *
 */
void NyxNet::CNxConnection_Impl::Open( NyxNet::CSocket* pSocket )
{
	m_SocketStream.Socket() = pSocket;
	m_pStreamRW = static_cast<Nyx::IStreamRW*>(&m_SocketStream);

	pSocket->SetListener( static_cast<NyxNet::ISocketListener*>(this) );
}


/**
 *
 */
void NyxNet::CNxConnection_Impl::Close()
{
	m_SocketStream.Socket() = NULL;
}


/**
 *
 */
void NyxNet::CNxConnection_Impl::HandleStream( Nyx::IStreamRW& rStream )
{
	m_pStreamRW = &rStream;

	m_refHSThread = Nyx::CThread::Alloc();
	m_refHSThread->Start( new Nyx::CThreadDelegateNoRef<NyxNet::CNxConnection_Impl>(
		this,
		&NyxNet::CNxConnection_Impl::SvrCheckHandshakeThreadProc,
		&NyxNet::CNxConnection_Impl::SvrStopCheckHandshakeThreadProc ) );

	while ( m_bRunning )
	{
		m_pConnectionHandler->HandleStream( static_cast<NyxNet::INxStreamRW&>(*this) );	
	}

	m_refHSThread->Stop();
	m_refHSThread = NULL;

	m_pStreamRW = NULL;
}


/**
 *
 */
Nyx::NyxResult NyxNet::CNxConnection_Impl::OnNewConnection( NyxNet::IConnection* pConnection, NyxNet::IConnectionHandler*& pCloneHandler )
{
	Nyx::NyxResult					res = Nyx::kNyxRes_Success;
	NyxNet::CNxConnection_Impl*		pHandler = NULL;
	NyxNet::INxConnectionHandler*	pNxCloneHandler = NULL;

	res = m_pConnectionHandler->OnNewConnection(pConnection, pNxCloneHandler);

	if ( Nyx::Succeeded(res) )
	{
		pHandler = new NyxNet::CNxConnection_Impl(pConnection);
		pHandler->SetConnectionHandler(pNxCloneHandler);

		pCloneHandler = pHandler;
	}

	return res;
}


/**
 *
 */
void NyxNet::CNxConnection_Impl::OnConnectionTerminated( NyxNet::IConnection* pConnection )
{
	m_pConnectionHandler->OnConnectionTerminated(pConnection);
	delete this;
}


/**
 *
 */
void NyxNet::CNxConnection_Impl::OnSocketConnected( NyxNet::CSocket* pSocket )
{
	m_refHSThread = Nyx::CThread::Alloc();
	m_refHSThread->Start( new Nyx::CThreadDelegateNoRef<NyxNet::CNxConnection_Impl>(
		this,
		&NyxNet::CNxConnection_Impl::ClientCheckHandshakeThreadProc,
		&NyxNet::CNxConnection_Impl::ClientStopCheckHandshakeThreadProc) );
}


/**
 *
 */
void NyxNet::CNxConnection_Impl::OnSocketDisconnected( NyxNet::CSocket* pSocket )
{
	if ( m_refHSThread.Valid() )
	{
		m_refHSThread->Stop();
		m_refHSThread = NULL;
	}
}


/**
 *
 */
void NyxNet::CNxConnection_Impl::SvrCheckHandshakeThreadProc()
{
	while ( m_bRunning )
	{
		m_refHSEvent->WaitSignaled(m_HSTimeout*2);

		if ( m_bRunning )
		{
			if ( m_ReceivedData == 0 )
			{
				m_MissedHandshakes ++;
				Nyx::CTraceStream(0x0).Write(L"Missed data reception : %i", m_MissedHandshakes);
			}
			else
			{
				m_MissedHandshakes = 0;
				m_ReceivedData = 0;
			}

			if ( m_MissedHandshakes > 2 )
			{
				Nyx::CTraceStream(0x0).Write(L"too many missed handshakes : closing connection");
				m_bRunning = false;
				m_pConnection->Close();
			}
		}
	}

	//Nyx::CTraceStream(0x0).Write(L"SvrCheckHandshakeThreadProc terminating");
}


/**
 *
 */
void NyxNet::CNxConnection_Impl::SvrStopCheckHandshakeThreadProc()
{
	m_bRunning = false;
	m_refHSEvent->Signal(0);
}


/**
 *
 */
void NyxNet::CNxConnection_Impl::ClientCheckHandshakeThreadProc()
{
	while ( m_bRunning )
	{
		m_refHSEvent->WaitSignaled(m_HSTimeout);

		if ( m_bRunning )
		{
			//Nyx::CTraceStream(0x0).Write(L"Sending handshake");
			//printf("sending handshake");

			{
				Nyx::TLock<Nyx::CMutex>		WriteLock(m_refWriteMutex, true);
				NyxNet::NxDataType			DataType = NyxNet::eNxDT_HandShake;
				Nyx::NyxSize				SizeWritten(0);

				m_pStreamRW->Write( (void*)&DataType, sizeof(DataType), SizeWritten );
			}

		}
	}

	//Nyx::CTraceStream(0x0).Write(L"ClientCheckHandshakeThreadProc terminating");
}


/**
 *
 */
void NyxNet::CNxConnection_Impl::ClientStopCheckHandshakeThreadProc()
{
	m_bRunning = false;
	m_refHSEvent->Signal(0);
}

