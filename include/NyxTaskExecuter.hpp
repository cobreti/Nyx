#ifndef _NYXTASKEXECUTER_HPP_
#define _NYXTASKEXECUTER_HPP_

#include "NyxTask.hpp"

DECLARE_NYXOBJECTREF(CTaskExecuter)

namespace Nyx
{

	class CTaskExecuter : public Nyx::CObject
	{
	public:
		
		virtual Nyx::NyxResult Execute( Nyx::CTask* pTask ) = 0;
		virtual Nyx::NyxResult StopCurrentTask() = 0;
	};
}


#endif // _NYXTASKEXECUTER_HPP_
