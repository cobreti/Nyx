#ifndef _NYXEVENT_IMPL_HPP_
#define _NYXEVENT_IMPL_HPP_

#include "NyxEvent.hpp"
#include "NyxObject_Impl.hpp"

#include <Windows.h>

namespace NyxWin32
{
	class CEvent_Impl : public Nyx::CObject_Impl<Nyx::CEvent>
	{
	public:
		CEvent_Impl();
		virtual ~CEvent_Impl();
		
		virtual void Signal( const Nyx::UInt32& unFlag );
		virtual Nyx::NyxResult WaitSignaled( const Nyx::UInt32& unTimeout );
		virtual Nyx::NyxResult WaitSignaled();
		
	protected:
		
		HANDLE		m_hEvent;
	};
};

#endif // _NYXEVENT_IMPL_HPP_

