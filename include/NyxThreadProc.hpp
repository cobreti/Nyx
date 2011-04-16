#ifndef _NYXTHREADPROC_HPP_
#define _NYXTHREADPROC_HPP_

#include "NyxObject.hpp"
#include "NyxRef.hpp"

DECLARE_NYXOBJECTREF(CThreadProc)

namespace Nyx
{
	class CThreadProc : public Nyx::CObject
	{
	public:
	
		virtual void Run() = 0;
		virtual void Stop() = 0;
	};
}


#endif // _NYXTHREADPROC_HPP_
