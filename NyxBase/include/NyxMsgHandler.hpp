#ifndef _NYXMSGHANDLER_HPP_
#define _NYXMSGHANDLER_HPP_


#include "NyxObject.hpp"


namespace Nyx
{
	class CMsg;

	class CMsgHandler : public Nyx::CObject
	{
	public:
	
		virtual void HandleMessage( Nyx::CMsg& msg ) = 0;
	
	};
}


#endif // _NYXMSGHANDLER_HPP_

