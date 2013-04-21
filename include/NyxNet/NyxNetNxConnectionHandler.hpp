#ifndef _NYXNETNXCONNECTIONHANDLER_HPP_
#define _NYXNETNXCONNECTIONHANDLER_HPP_

namespace NyxNet
{
	class INxStreamRW;

	class INxConnectionHandler
	{
	public:

		virtual void HandleStream( NyxNet::INxStreamRW& rStream ) = 0;
		virtual Nyx::NyxResult OnNewConnection( NyxNet::IConnection* pConnection, NyxNet::INxConnectionHandler*& pCloneHandler ) = 0;
		virtual void OnConnectionTerminated( NyxNet::IConnection* pConnection ) = 0;
	};
}

#endif // _NYXNETNXCONNECTIONHANDLER_HPP_
