#ifndef _NYXNETTCPIPSOCKET_IMPL_HPP_
#define _NYXNETTCPIPSOCKET_IMPL_HPP_

#include "NyxObject_Impl.hpp"
#include "NyxNetTcpIpSocket.hpp"
#include "NyxAString.hpp"
#include "NyxNetAddress.hpp"


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
		virtual bool Valid() const;
		virtual Nyx::NyxResult Renew();
        virtual const NyxNet::CAddress& ClientAddress() const { return m_ClientAddress; }
        virtual NyxNet::TcpIpSocketId TcpIpSocketId() { return m_Socket; }
        virtual CTcpIpSocket* TcpIpSocket() { return static_cast<NyxNet::CTcpIpSocket*>(this); }

	protected:
	
		int							m_Socket;
		Nyx::CAString				m_Ip;
		NyxNet::TcpIpPort			m_Port;
		NyxNet::ISocketListener*	m_pListener;
		bool						m_bValid;
        timeval						m_Timeout;
        NyxNet::CAddress            m_ClientAddress;
    };
}


#endif // _NYXNETTCPIPSOCKET_IMPL_HPP_
