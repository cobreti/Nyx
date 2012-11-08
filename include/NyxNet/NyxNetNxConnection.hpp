#ifndef _NYXNETNXPROTOCOLCONNECTION_HPP_
#define _NYXNETNXPROTOCOLCONNECTION_HPP_

#include "NyxNetNxStreamRW.hpp"
#include "NyxNetConnectionHandler.hpp"
#include "NyxObject.hpp"
#include "NyxRef.hpp"


DECLARE_NSPOBJECTREF(NyxNet, CNxConnection)

namespace NyxNet
{
	class CSocket;
	class INxConnectionHandler;

	class CNxConnection :	public Nyx::CObject,
							public NyxNet::INxStreamRW,
							public NyxNet::IConnectionHandler
	{
	public:

		static CNxConnectionRef Alloc();

	public:

		virtual void Open( NyxNet::CSocket* pSocket ) = 0;
		virtual void Close() = 0;
		virtual void SetConnectionHandler( NyxNet::INxConnectionHandler* pConnectionHandler ) = 0;
        virtual bool GetUseHandshake() const = 0;
        virtual void SetUseHandshake(bool bUseHandshake) = 0;
	};
}


#endif // _NYXNETNXPROTOCOLCONNECTION_HPP_
