#ifndef _NYXNETSOCKET_HPP_
#define _NYXNETSOCKET_HPP_

#include "NyxObject.hpp"
#include "NyxTypes.hpp"
#include "NyxRef.hpp"

DECLARE_NSPOBJECTREF(NyxNet, CSocket)

namespace NyxNet
{
	class ISocketListener;
    class CTcpIpSocket;

	class CSocket : public Nyx::CObject
	{
	public:
		virtual Nyx::NyxResult Write( const void* pBuffer, const Nyx::NyxSize& DataSize, Nyx::NyxSize& WrittenSize ) = 0;
		virtual Nyx::NyxResult Read( void* pBuffer, const Nyx::NyxSize& DataSize, Nyx::NyxSize& ReadSize ) = 0;
		virtual Nyx::NyxResult Connect() = 0;
		virtual void Disconnect() = 0;
		virtual void SetListener( NyxNet::ISocketListener* pListener ) = 0;
        virtual bool Valid() const = 0;
        virtual Nyx::NyxResult Renew() = 0;
        virtual CTcpIpSocket* TcpIpSocket() { return NULL; }
	};
}


#endif // _NYXNETSOCKET_HPP_
