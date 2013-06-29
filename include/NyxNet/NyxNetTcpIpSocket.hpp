#ifndef _NYXNETTCPIPSOCKET_HPP_
#define _NYXNETTCPIPSOCKET_HPP_

#include "NyxObject.hpp"
#include "NyxRef.hpp"
#include "NyxNetTypes.hpp"
#include "NyxNetSocket.hpp"
#include "NyxNetAddress.hpp"

DECLARE_NSPOBJECTREF(NyxNet, CTcpIpSocket)

namespace NyxNet
{
	class CTcpIpSocket : public NyxNet::CSocket
	{
	public:
	
		static CTcpIpSocketRef Alloc();
	
	public:
	
		virtual Nyx::NyxResult Listen( const Nyx::UInt32& MaxPendingConnections ) = 0;
		virtual Nyx::NyxResult Bind( const NyxNet::TcpIpPort& Port ) = 0;
		virtual Nyx::NyxResult Accept( CTcpIpSocketRef& NewSocket ) = 0;
		virtual Nyx::NyxResult Create( const char* szIp, const NyxNet::TcpIpPort& Port ) = 0;
        virtual const NyxNet::CAddress& ClientAddress() const = 0;
        virtual NyxNet::TcpIpSocketId TcpIpSocketId() = 0;
	};
}


#endif // _NYXNETTCPIPSOCKET_HPP_
