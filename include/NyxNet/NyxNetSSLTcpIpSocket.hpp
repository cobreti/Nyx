#ifndef _NYXNETSSLTCPIPSOCKET_HPP_
#define _NYXNETSSLTCPIPSOCKET_HPP_

#include "NyxNetTcpIpSocket.hpp"

DECLARE_NSPOBJECTREF(NyxNet, CSSLTcpIpSocket)

namespace NyxNet
{
	class CSSLTcpIpSocket : public NyxNet::CTcpIpSocket
	{
	public:
        
		static CSSLTcpIpSocketRef Alloc();
        
    public:
        
        virtual void SetPrivKeyFile( const Nyx::CAString& privKeyFile ) = 0;
        virtual void SetPublicKeyFile( const Nyx::CAString& publicKeyFile ) = 0;
        virtual void SetDhKeyFile( const Nyx::CAString& dhKeyFile ) = 0;
	};
}


#endif // _NYXNETSSLTCPIPSOCKET_HPP_
