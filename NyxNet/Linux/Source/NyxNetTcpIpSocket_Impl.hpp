#ifndef _NYXNETTCPIPSOCKET_IMPL_HPP_
#define _NYXNETTCPIPSOCKET_IMPL_HPP_

#include "NyxObject_Impl.hpp"
#include "NyxNetTcpIpSocket.hpp"
#include "NyxAString.hpp"


namespace NyxNetLinux
{
	class CTcpIpSocket_Impl : public Nyx::CObject_Impl<NyxNet::CTcpIpSocket>
	{
	public:
		CTcpIpSocket_Impl();
		CTcpIpSocket_Impl( const int& SocketValue );
		virtual ~CTcpIpSocket_Impl();

	public:
	
		virtual Nyx::NyxResult Listen( const Nyx::UInt32& MaxPendingConnections );
		virtual Nyx::NyxResult Bind( const NyxNet::TcpIpPort& Port );
		virtual Nyx::NyxResult Accept( NyxNet::CTcpIpSocketRef& NewSocket );
		virtual Nyx::NyxResult Connect();
		virtual void Disconnect();
		virtual Nyx::NyxResult Write( const void* pBuffer, const Nyx::NyxSize& DataSize, Nyx::NyxSize& WrittenSize );
		virtual Nyx::NyxResult Read( void* pBuffer, const Nyx::NyxSize& DataSize, Nyx::NyxSize& ReadSize );
		virtual Nyx::NyxResult Create( const char* szIp, const NyxNet::TcpIpPort& Port );
		virtual void SetListener( NyxNet::ISocketListener* pListener );

	protected:
	
		int							m_Socket;
		Nyx::CAString				m_Ip;
		NyxNet::TcpIpPort			m_Port;
		NyxNet::ISocketListener*	m_pListener;
	};
}


#endif // _NYXNETTCPIPSOCKET_IMPL_HPP_
