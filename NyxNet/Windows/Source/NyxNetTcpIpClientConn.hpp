#ifndef _NYXNETTCPIPCLIENTCONN_HPP_
#define _NYXNETTCPIPCLIENTCONN_HPP_

#include "NyxTask.hpp"
#include "NyxObject_Impl.hpp"
#include "NyxNetTcpipSocket.hpp"
#include "NyxStreamRW.hpp"
#include "NyxNetConnection.hpp"
#include "NyxNetConnectionHandler.hpp"

DECLARE_NSPOBJECTREF(NyxNetWin32, CTcpIpClientConn)

namespace NyxNetWin32
{
	class CTcpIpClientConn :	public Nyx::CObject_Impl<Nyx::CTask>,
								public Nyx::IStreamRW,
								public NyxNet::IConnection
	{
	public:
		CTcpIpClientConn(	NyxNet::CTcpIpSocketRef refConnSocket );
		virtual ~CTcpIpClientConn();

		virtual void SetConnectionHandler( NyxNet::IConnectionHandler* pConnHandler );

	public: // CTask methods

		virtual Nyx::NyxResult Execute();
		virtual Nyx::NyxResult Stop();
	
	public: // CStreamRW methods

		virtual Nyx::NyxResult Read(	void* pBuffer,
										const Nyx::NyxSize& SizeToRead,
										Nyx::NyxSize& SizeRead );
		
		virtual Nyx::NyxResult Write(	void* pBuffer,
										const Nyx::NyxSize& SizeToWrite,
										Nyx::NyxSize& SizeWritten );

	public: // IConnection methods

		virtual void Close();
        virtual NyxNet::CSocketRef Socket();

	protected:

		NyxNet::CTcpIpSocketRef			m_refConnSocket;
		NyxNet::IConnectionHandler*		m_pConnectionHandler;
	};
}


#endif // _NYXNETTCPIPCLIENTCONN_HPP_

