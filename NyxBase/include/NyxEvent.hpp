#ifndef _NYXEVENT_HPP_
#define _NYXEVENT_HPP_

#include "NyxObject.hpp"
#include "NyxRef.hpp"

DECLARE_NYXOBJECTREF(CEvent)

namespace Nyx
{
	/*typedef		Nyx::UInt32		WaitResult;
	
	enum
	{
		kWR_Failure = -1,
		kWR_TimedOut = 1,
		kWR_Signaled = 2
	};*/

	class CEvent : public Nyx::CObject
	{
	public:
		
		static CEvent* Alloc();
		
	public:
	
		virtual void Signal( const Nyx::UInt32& unFlag ) = 0;
		virtual Nyx::NyxResult WaitSignaled( const Nyx::UInt32& unTimeout ) = 0;
		virtual Nyx::NyxResult WaitSignaled() = 0;
	};
};


#endif // _NYXEVENT_HPP_

