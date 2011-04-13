#ifndef _NYXNETSOCKETLISTENER_HPP_
#define _NYXNETSOCKETLISTENER_HPP_

namespace NyxNet
{
	class CSocket;

	class ISocketListener
	{
	public:

		virtual void OnSocketConnected( NyxNet::CSocket* pSocket ) = 0;
		virtual void OnSocketDisconnected( NyxNet::CSocket* pSocket ) = 0;
	};
}

#endif // _NYXNETSOCKETLISTENER_HPP_
