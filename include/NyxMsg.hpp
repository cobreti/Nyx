#ifndef _NYXMSG_HPP_
#define _NYXMSG_HPP_

#include "NyxTypes.hpp"

namespace Nyx
{
	class CMsg
	{
	public:
        virtual ~CMsg() {}
        
		virtual const Nyx::MsgIdentifier Id() const = 0;
	};
};


#endif // _NYXMSG_HPP_
