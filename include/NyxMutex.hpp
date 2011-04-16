#ifndef _NYXMUTEX_HPP_
#define _NYXMUTEX_HPP_

#include "NyxObject.hpp"
#include "NyxRef.hpp"

namespace Nyx
{
	class CMutex : public Nyx::CObject
	{
	public:
		static CMutex* Alloc();
		
	public:
	
		virtual void Lock() = 0;
		virtual bool AttemptLock() = 0;
		virtual void Unlock() = 0;
	};
};

DECLARE_NYXOBJECTREF(CMutex);


#endif // _NYXMUTEX_HPP_
