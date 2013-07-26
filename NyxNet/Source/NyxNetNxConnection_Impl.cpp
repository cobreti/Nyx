#include <stdio.h>
#include <string.h>

#include "NyxNetNxConnection_Impl.hpp"
#include "NyxNetTypes.hpp"
#include "NyxStreamRW.hpp"
#include "NyxNetConnection.hpp"
#include "NyxLock.hpp"
#include "NyxTraceStream.hpp"
#include "NyxTraces.hpp"
#include "NyxSwap.hpp"


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
m_kBufferIncrement(8192),
m_pConnection(NULL),
m_pStreamRW(NULL),
m_ReceivedData(0),
m_bRunning(true),
m_HSTimeout(5000),
m_MissedHandshakes(0),
m_pConnectionHandler(NULL),
m_bUseHandshake(true),
m_BytesOrderMarker(0)
{
	m_refHSEvent = Nyx::CEvent::Alloc();
	m_refWriteMutex = Nyx::CMutex::Alloc();
	m_refReadMutex = Nyx::CMutex::Alloc();

	m_WriteBuffer.Alloc(m_kBufferIncrement);
}


/**
 *
 */
NyxNet::CNxConnection_Impl::CNxConnection_Impl(NyxNet::IConnection* pConnection) :
m_kBufferIncrement(8192),
m_pConnection(pConnection),
m_pStreamRW(NULL),
m_ReceivedData(0),
m_bRunning(true),
m_HSTimeout(5000),
m_MissedHandshakes(0),
m_pConnectionHandler(NULL),
m_bUseHandshake(true)
{
	m_refHSEvent = Nyx::CEvent::Alloc();
	m_refWriteMutex = Nyx::CMutex::Alloc();
	m_refReadMutex = Nyx::CMutex::Alloc();

	m_WriteBuffer.Alloc(m_kBufferIncrement);
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
bool NyxNet::CNxConnection_Impl::GetUseHandshake() const
{
    return m_bUseHandshake;
}


/**
 *
 */
void NyxNet::CNxConnection_Impl::SetUseHandshake(bool bUseHandshake)
{
    m_bUseHandshake = bUseHandshake;
}


/**
 *
 */
bool NyxNet::CNxConnection_Impl::RequiresBytesSwap() const
{
    return (m_BytesOrderMarker == 0xFEFF0000);
}

/**
 *
 */
Nyx::NyxResult NyxNet::CNxConnection_Impl::BeginRead( NyxNet::NxDataType& datatype )
{
	Nyx::NyxResult		    res = Nyx::kNyxRes_Success;
	Nyx::NyxSize			ReadSize;
    NyxNet::NxDataSize      DataSize = 0;
    Nyx::NyxSize      		RemainingSizeToRead = 0;

	m_refReadMutex->Lock();

	do
	{
        DataSize = 0;
        datatype = NyxNet::eNxDT_HandShake;
        res = m_pStreamRW->Read( &m_BytesOrderMarker, sizeof(m_BytesOrderMarker), ReadSize );
        
        if ( Nyx::Succeeded(res) )
            res = m_pStreamRW->Read( &DataSize, sizeof(NyxNet::NxDataSize), ReadSize );

        if ( Nyx::Succeeded(res) && RequiresBytesSwap() )
        	DataSize = Nyx::Swap_UInt32(DataSize);

        if ( Nyx::Succeeded(res) && DataSize > 0 && ReadSize > 0 )
        {
            m_ReadBuffer.Clear();
            m_ReadBuffer.Resize(DataSize);
            RemainingSizeToRead = DataSize;

            do
            {
                res = m_pStreamRW->Read( m_ReadBuffer.getWritePos(), RemainingSizeToRead, ReadSize );

                //NYXTRACE(0x0, L"--> CNxConnection - BeginRead - read " << ReadSize << L" of " << RemainingSizeToRead );

                m_ReadBuffer.addDataSize(ReadSize);
                RemainingSizeToRead -= ReadSize;

                //NYXTRACE(0x0, L"--> Remaining size to read : " << RemainingSizeToRead );
            }
            while ( Nyx::Succeeded(res) && RemainingSizeToRead > 0 );

		    if ( Nyx::Succeeded(res) )
		    {
			    ++ m_ReceivedData;
                m_ReadBuffer.ReadData( &datatype, sizeof(NyxNet::NxDataType) );

                if ( RequiresBytesSwap() )
                    datatype = Nyx::Swap_UInt32(datatype);

			    if ( datatype == NyxNet::eNxDT_HandShake )
			    {
				    //Nyx::CTraceStream(0x0).Write(L"Received handshake");
			    }
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
	Nyx::NyxResult		res = Nyx::kNyxRes_Failure;
	Nyx::NyxSize		ReadSize;

    ReadSize = m_ReadBuffer.ReadData( &size, sizeof(NyxNet::NxDataSize) );

    if ( RequiresBytesSwap() )
    	size = Nyx::Swap_UInt32(size);

    if ( sizeof(NyxNet::NxDataSize) == ReadSize )
    {
		++ m_ReceivedData;
        res = Nyx::kNyxRes_Success;
    }

	return res;
}


/**
 *
 */
Nyx::NyxResult NyxNet::CNxConnection_Impl::Read( void* pBuffer, const NyxNet::NxDataSize& size )
{
	Nyx::NyxResult		res = Nyx::kNyxRes_Failure;
	Nyx::NyxSize		ReadSize(0);

    ReadSize = m_ReadBuffer.ReadData( pBuffer, size );
    if ( size == ReadSize )
    {
		++ m_ReceivedData;
        res = Nyx::kNyxRes_Success;
    }

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
//	Nyx::NyxSize				WrittenSize(0);

	m_refWriteMutex->Lock();

	m_WriteBuffer.Clear();
    m_WriteBuffer.WriteDataResize( &datatype, sizeof(NyxNet::NxDataType), m_kBufferIncrement );

	if ( Nyx::Failed(res) )
		m_refWriteMutex->Unlock();			

	return res;
}


/**
 *
 */
Nyx::NyxResult NyxNet::CNxConnection_Impl::BeginWriteSection( const NyxNet::NxDataSize& size )
{
	Nyx::NyxResult				res = Nyx::kNyxRes_Success;

    m_WriteBuffer.WriteDataResize( &size, sizeof(NyxNet::NxDataSize), m_kBufferIncrement );

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
	Nyx::TLock<Nyx::CMutex>		WriteLock(m_refWriteMutex, true);

	m_WriteBuffer.WriteDataResize( pBuffer, DataSize, m_kBufferIncrement );

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
    NyxNet::NxDataSize          DataSize = m_WriteBuffer.DataSize();
    Nyx::UInt32                 BytesOrderMarker = 0xFFFE;

	Nyx::NyxSize				WrittenSize(0);

    m_pStreamRW->Write( &BytesOrderMarker, sizeof(BytesOrderMarker), WrittenSize );
    m_pStreamRW->Write( &DataSize, sizeof(NyxNet::NxDataSize), WrittenSize );
	m_pStreamRW->Write( m_WriteBuffer.Buffer(), m_WriteBuffer.DataSize(), WrittenSize );

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

    if ( m_bUseHandshake )
    {
        m_refHSThread = Nyx::CThread::Alloc();
        m_refHSThread->Start( new Nyx::CThreadDelegateNoRef<NyxNet::CNxConnection_Impl>(
            this,
            &NyxNet::CNxConnection_Impl::SvrCheckHandshakeThreadProc,
            &NyxNet::CNxConnection_Impl::SvrStopCheckHandshakeThreadProc ) );
    }

	while ( m_bRunning )
	{
		m_pConnectionHandler->HandleStream( static_cast<NyxNet::INxStreamRW&>(*this) );	
	}

    if ( m_bUseHandshake )
    {
        m_refHSThread->Stop();
        m_refHSThread = NULL;
    }

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
        pHandler->SetUseHandshake(m_bUseHandshake);
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
void NyxNet::CNxConnection_Impl::CloseConnection( NyxNet::IConnection* pConnection )
{
    
}


/**
 *
 */
void NyxNet::CNxConnection_Impl::OnSocketConnected( NyxNet::CSocket* pSocket )
{
    if ( m_bUseHandshake )
    {
        m_refHSThread = Nyx::CThread::Alloc();
        m_refHSThread->Start( new Nyx::CThreadDelegateNoRef<NyxNet::CNxConnection_Impl>(
            this,
            &NyxNet::CNxConnection_Impl::ClientCheckHandshakeThreadProc,
            &NyxNet::CNxConnection_Impl::ClientStopCheckHandshakeThreadProc) );
    }
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
				//Nyx::CTraceStream(0x0).Write(L"Missed data reception : %i", m_MissedHandshakes);
			}
			else
			{
				m_MissedHandshakes = 0;
				m_ReceivedData = 0;
			}

			if ( m_MissedHandshakes > 2 )
			{
				//Nyx::CTraceStream(0x0).Write(L"too many missed handshakes : closing connection");
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
                NyxNet::NxDataSize          DataSize = sizeof(NyxNet::NxDataType);
				Nyx::NyxSize				SizeWritten(0);
                Nyx::UInt32                 BytesOrderMarker = 0xFFFE;

                //NYXTRACE(0x0, L"DataSize = " << (int)DataSize << L" | DataType = " << Nyx::CTF_Hex(DataType) );

                m_pStreamRW->Write( &BytesOrderMarker, sizeof(BytesOrderMarker), SizeWritten );
                m_pStreamRW->Write( &DataSize, sizeof(NyxNet::NxDataSize), SizeWritten );
                m_pStreamRW->Write( &DataType, sizeof(NyxNet::NxDataType), SizeWritten );
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

