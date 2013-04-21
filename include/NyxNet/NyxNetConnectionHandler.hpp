#ifndef _NYXNETCONNECTIONHANDLER_HPP_
#define _NYXNETCONNECTIONHANDLER_HPP_

#include <NyxStreamHandler.hpp>

namespace NyxNet
{
	class IConnection;

	class IConnectionHandler : public Nyx::IStreamHandler
	{
	public:
		virtual Nyx::NyxResult OnNewConnection( NyxNet::IConnection* pConnection, NyxNet::IConnectionHandler*& pCloneHandler ) = 0;
		virtual void OnConnectionTerminated( NyxNet::IConnection* pConnection ) = 0;
        virtual void CloseConnection( NyxNet::IConnection* pConnection ) = 0;
	};
}

#endif // _NYXNETCONNECTIONHANDLER_HPP_
