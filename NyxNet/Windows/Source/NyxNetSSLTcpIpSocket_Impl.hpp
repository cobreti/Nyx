#ifndef _NYXNETSSLTCPIPSOCKET_IMPL_HPP_
#define _NYXNETSSLTCPIPSOCKET_IMPL_HPP_

#include "NyxObject_Impl.hpp"
#include "NyxNetSSLTcpIpSocket.hpp"

#include <openssl/bio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

namespace NyxNetOSX
{
	class CSSLTcpIpSocket_Impl : public Nyx::CObject_Impl<NyxNet::CSSLTcpIpSocket>
	{
	public:
        CSSLTcpIpSocket_Impl();
		CSSLTcpIpSocket_Impl( NyxNet::CTcpIpSocketRef refSocket );
		virtual ~CSSLTcpIpSocket_Impl();

	public:
	
		virtual Nyx::NyxResult Listen( const Nyx::UInt32& MaxPendingConnections );
		virtual Nyx::NyxResult Bind( const NyxNet::TcpIpPort& Port );
		virtual Nyx::NyxResult Accept( NyxNet::CTcpIpSocketRef& NewSocket );
		virtual Nyx::NyxResult Connect();
		virtual void Disconnect();
        virtual CTcpIpSocket* TcpIpSocket() { return static_cast<NyxNet::CTcpIpSocket*>(this); }
        
		virtual Nyx::NyxResult Write( const void* pBuffer, const Nyx::NyxSize& DataSize, Nyx::NyxSize& WrittenSize );
		virtual Nyx::NyxResult Read( void* pBuffer, const Nyx::NyxSize& DataSize, Nyx::NyxSize& ReadSize );
		virtual Nyx::NyxResult Create( const char* szIp, const NyxNet::TcpIpPort& Port );
		virtual void SetListener( NyxNet::ISocketListener* pListener );
        virtual bool Valid() const;
        virtual Nyx::NyxResult Renew();
        virtual const NyxNet::CAddress& ClientAddress() const { return m_refSocket->ClientAddress(); }
        virtual NyxNet::TcpIpSocketId TcpIpSocketId() { return m_refSocket->TcpIpSocketId(); }
        
        virtual void SetPrivKeyFile( const Nyx::CAString& privKeyFile );
        virtual void SetPublicKeyFile( const Nyx::CAString& publicKeyFile );
        virtual void SetDhKeyFile( const Nyx::CAString& dhKeyFile );

    protected:
        
        void InitSSL();

	protected:
	
        NyxNet::CTcpIpSocketRef     m_refSocket;
        SSL_CTX*                    m_ctx;
        SSL*                        m_ssl;
        BIO*                        m_bio;
        bool                        m_bSSLOwner;
        Nyx::CAString               m_privKeyFile;
        Nyx::CAString               m_publicKeyFile;
        Nyx::CAString               m_dhKeyFile;
	};
}


#endif // _NYXNETTCPIPSOCKET_IMPL_HPP_
