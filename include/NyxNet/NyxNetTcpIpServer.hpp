#ifndef _NYXNETTCPIPSERVER_HPP_
#define _NYXNETTCPIPSERVER_HPP_

#include "NyxObject.hpp"
#include "NyxRef.hpp"
#include "NyxNetTypes.hpp"
#include "NyxNetServer.hpp"


DECLARE_NSPOBJECTREF(NyxNet, CTcpIpServer)

namespace NyxNet
{
	class IConnectionHandler;

	class CTcpIpServer : public NyxNet::CServer
	{
	public:
	
		static CTcpIpServerRef Alloc();
		
	public:
	
        virtual void SetUseSSL() = 0;
        virtual bool GetUseSSL() const = 0;
        virtual void SetSSLFiles(   const Nyx::CAString& privKeyFile,
                                    const Nyx::CAString& publicKeyFile,
                                    const Nyx::CAString& dhFile ) = 0;
		virtual Nyx::NyxResult Create(	const NyxNet::TcpIpPort& port,
										const Nyx::UInt32& MaxConnections,
										NyxNet::IConnectionHandler* pConnHandler ) = 0;
										
	};
}

#endif // _NYXNETTCPIPSERVER_HPP_
