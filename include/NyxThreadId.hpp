#ifndef _NYX_THREADID_HPP_
#define _NYX_THREADID_HPP_

#include <NyxObject.hpp>
#include <NyxRef.hpp>

DECLARE_NYXOBJECTREF(CThreadId);

namespace Nyx
{
	class CThreadId : public Nyx::CObject
	{
	public:
	
		static CThreadIdRef GetCurrent();
		
	public:
	
		virtual bool IsCurrent() const = 0;
	};
};


#endif // _NYX_THREADID_HPP_
