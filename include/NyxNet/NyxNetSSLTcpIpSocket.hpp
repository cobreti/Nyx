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
        
	};
}


#endif // _NYXNETSSLTCPIPSOCKET_HPP_
