#ifndef _NYXNETPIPESOCKET_HPP_
#define _NYXNETPIPESOCKET_HPP_

#include "NyxObject.hpp"
#include "NyxRef.hpp"
#include "NyxNetSocket.hpp"

DECLARE_NSPOBJECTREF(NyxNet, CPipeSocket)

namespace NyxNet 
{
	class CPipeSocket : public NyxNet::CSocket
	{
	public:

		//virtual Nyx::NyxResult Connect() = 0;
		//virtual Nyx::NyxResult Disconnect() = 0;
	};
}


#endif // _NYXNETPIPESOCKET_HPP_


