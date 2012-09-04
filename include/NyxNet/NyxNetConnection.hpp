#ifndef _NYXNETCONNECTION_HPP_
#define _NYXNETCONNECTION_HPP_

#include "NyxNetSocket.hpp"

namespace NyxNet
{
	class IConnection
	{
	public:

		virtual void Close() = 0;
        virtual CSocketRef Socket() = 0;
	};
}

#endif // _NYXNETCONNECTION_HPP_
