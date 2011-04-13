#ifndef _NYXTASKEXECUTERPOOL_HPP_
#define _NYXTASKEXECUTERPOOL_HPP_

#include "NyxTaskExecuter.hpp"

DECLARE_NYXOBJECTREF(CTaskExecuterPool)

namespace Nyx
{
	class CTaskExecuterPool : public Nyx::CObject
	{
	public:
	
		static CTaskExecuterPoolRef Alloc();
		
	public:
	
		virtual Nyx::NyxResult Execute( Nyx::CTask* pTask ) = 0;
		virtual void StopAllTasks() = 0;
	};
}


#endif // _NYXTASKEXECUTERPOOL_HPP_
