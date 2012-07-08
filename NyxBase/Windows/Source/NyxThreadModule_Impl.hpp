#ifndef _NYXTHREADMODULE_IMPL_HPP_
#define _NYXTHREADMODULE_IMPL_HPP_

#include "NyxThreadModule.hpp"

#include <Windows.h>

namespace NyxWin32
{
	class CThreadModule_Impl : public Nyx::CThreadModule
	{
	public:
		CThreadModule_Impl();
		virtual ~CThreadModule_Impl();

	public:

		virtual void Init();
		virtual void Terminate();
		virtual void* GetThreadUserData();
		virtual void SetThreadUserData(void* pData);

	protected:

		DWORD							m_TlsIndex;
	};
};


#endif // _NYXTHREADMODULE_IMPL_HPP_
