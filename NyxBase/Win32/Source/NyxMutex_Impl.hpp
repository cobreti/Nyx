#ifndef _NYXMUTEX_IMPL_HPP_
#define _NYXMUTEX_IMPL_HPP_

#include "NyxMutex.hpp"
#include "NyxObject_Impl.hpp"

#include <windows.h>

namespace NyxWin32
{
	class CMutex_Impl : public Nyx::CObject_Impl<Nyx::CMutex>
	{
	public:
		CMutex_Impl();
		virtual ~CMutex_Impl();
		
		virtual void Lock();
		virtual bool AttemptLock();
		virtual void Unlock();
		
	protected:

		HANDLE		m_hMutex;
	};
};


#endif // _NYXMUTEX_IMPL_HPP_
