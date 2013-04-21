#ifndef _NYXNETNXCONNECTION_IMPL_HPP_
#define _NYXNETNXCONNECTION_IMPL_HPP_

#include "NyxNetNxConnection.hpp"
#include "NyxObject_Impl.hpp"
#include "NyxNetSocket.hpp"
#include "NyxStreamRW.hpp"
#include "NyxThread.hpp"
#include "NyxEvent.hpp"
#include "NyxMutex.hpp"
#include "NyxNetNxConnectionHandler.hpp"
#include "NyxNetSocketListener.hpp"
#include "NyxBuffer.hpp"

#pragma managed(push, off)

namespace NyxNet
{
	/**
	 *
	 */
	class CSocketStream :	public Nyx::IStreamRW
	{
	public:
		CSocketStream() {}
		virtual ~CSocketStream() {}

		const NyxNet::CSocketRef& Socket() const	{ return m_refSocket; }
		NyxNet::CSocketRef& Socket()				{ return m_refSocket; }


		virtual Nyx::NyxResult Read(	void* pBuffer,
										const Nyx::NyxSize& SizeToRead,
										Nyx::NyxSize& SizeRead )
		{
			Nyx::NyxResult		res = Nyx::kNyxRes_Failure;

			try
			{
				res = m_refSocket->Read(pBuffer, SizeToRead, SizeRead);
			}
			catch (...)
			{
			}

			return res;
		}

		virtual Nyx::NyxResult Write(	void* pBuffer,
										const Nyx::NyxSize& SizeToWrite,
										Nyx::NyxSize& SizeWritten )
		{
			Nyx::NyxResult	res = Nyx::kNyxRes_Failure;

			try
			{
				res = m_refSocket->Write(pBuffer, SizeToWrite, SizeWritten);
			}
			catch (...)
			{
			}

			return res;
		}

	protected:
		NyxNet::CSocketRef		m_refSocket;
	};


	/**
	 *
	 */
	class CNxConnection_Impl :	public Nyx::CObject_Impl<NyxNet::CNxConnection>,
								public NyxNet::ISocketListener
	{
	public:
		CNxConnection_Impl();
		CNxConnection_Impl( NyxNet::IConnection* pConnection );
		virtual ~CNxConnection_Impl();

		virtual void SetConnectionHandler( NyxNet::INxConnectionHandler* pConnectionHandler );

        virtual bool GetUseHandshake() const;
        virtual void SetUseHandshake(bool bUseHandshake);

	public:

        virtual bool RequiresBytesSwap() const;

		virtual Nyx::NyxResult BeginRead( NyxNet::NxDataType& datatype );
		virtual Nyx::NyxResult BeginReadSection( NyxNet::NxDataSize& size );
		virtual Nyx::NyxResult Read( void* pBuffer, const NyxNet::NxDataSize& size );
		virtual void EndReadSection();
		virtual void EndRead();

		virtual Nyx::NyxResult BeginWrite( const NyxNet::NxDataType& datatype );
		virtual Nyx::NyxResult BeginWriteSection( const NyxNet::NxDataSize& size );
		virtual Nyx::NyxResult Write( void* pBuffer, const NyxNet::NxDataSize& DataSize );
		virtual void EndWriteSection();
		virtual void EndWrite();

		virtual void Open( NyxNet::CSocket* pSocket );
		virtual void Close();

		virtual void HandleStream( Nyx::IStreamRW& rStream );
		virtual Nyx::NyxResult OnNewConnection( NyxNet::IConnection* pConnection, NyxNet::IConnectionHandler*& pCloneHandler );
		virtual void OnConnectionTerminated( NyxNet::IConnection* pConnection );
        virtual void CloseConnection( NyxNet::IConnection* pConnection );

	public: // ISocketListener methods

		virtual void OnSocketConnected( NyxNet::CSocket* pSocket );
		virtual void OnSocketDisconnected( NyxNet::CSocket* pSocket );

	protected:

		virtual void SvrCheckHandshakeThreadProc();
		virtual void SvrStopCheckHandshakeThreadProc();

		virtual void ClientCheckHandshakeThreadProc();
		virtual void ClientStopCheckHandshakeThreadProc();

	protected:

		class XBuffer : public Nyx::TBuffer<Nyx::UInt8>
		{
			typedef		Nyx::TBuffer<Nyx::UInt8>		BaseType;

		public:
			XBuffer() : BaseType() {}
		};

		const Nyx::NyxSize					m_kBufferIncrement;

		NyxNet::IConnection*				m_pConnection;
		Nyx::IStreamRW*						m_pStreamRW;
		CSocketStream						m_SocketStream;
		int									m_ReceivedData;
		Nyx::CEventRef						m_refHSEvent;
		Nyx::CMutexRef						m_refWriteMutex;
		Nyx::CMutexRef						m_refReadMutex;
		Nyx::CThreadRef						m_refHSThread;
		bool								m_bRunning;
		Nyx::UInt32							m_HSTimeout;
		int									m_MissedHandshakes;
		NyxNet::INxConnectionHandler*		m_pConnectionHandler;
		XBuffer								m_WriteBuffer;
        XBuffer                             m_ReadBuffer;
        bool                                m_bUseHandshake;
        Nyx::UInt32							m_BytesOrderMarker;
	};
}

#pragma managed(pop)

#endif // _NYXNETNXCONNECTION_IMPL_HPP_
