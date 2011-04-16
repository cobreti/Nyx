#ifndef _NYXTHREADMODULE_IMPL_HPP_
#define _NYXTHREADMODULE_IMPL_HPP_

#include "NyxThreadModule.hpp"
#include "NyxObject_Impl.hpp"


#include <pthread.h>


namespace NyxOSX
{
	class CThreadModule_Impl : public Nyx::CObject_Impl<Nyx::CThreadModule>
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
	
		pthread_key_t					m_keyThreadUserData;
	};
}


#endif // _NYXTHREADMODULE_IMPL_HPP_
