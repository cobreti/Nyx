#ifndef _NYXNETSERVER_HPP_
#define _NYXNETSERVER_HPP_

#include "NyxObject.hpp"
#include "NyxTypes.hpp"

namespace NyxNet
{
	class CServer : public Nyx::CObject
	{
	public:

		virtual Nyx::NyxResult Start() = 0;
		virtual Nyx::NyxResult Stop() = 0;
		virtual bool IsRunning() const = 0;
	};
}


#endif // _NYXNETSERVER_HPP_
