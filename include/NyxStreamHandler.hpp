#ifndef _NYXISTREAMHANDLER_HPP_
#define _NYXISTREAMHANDLER_HPP_

#include "NyxTypes.hpp"

namespace Nyx
{
	class IStreamRW;
	
	class IStreamHandler
	{
	public:

		virtual void HandleStream( Nyx::IStreamRW& rStream ) = 0;
	};
};


#endif // _NYXISTREAMHANDLER_HPP_
