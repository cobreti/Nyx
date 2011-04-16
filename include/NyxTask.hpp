#ifndef _NYXTASK_HPP_
#define _NYXTASK_HPP_

#include "NyxObject.hpp"
#include "NyxRef.hpp"

DECLARE_NYXOBJECTREF(CTask)

namespace Nyx
{
	class CTask : public Nyx::CObject
	{
	public:
		virtual Nyx::NyxResult Execute() = 0;
		virtual Nyx::NyxResult Stop() = 0;
	};
}



#endif // _NYXTASK_HPP_
