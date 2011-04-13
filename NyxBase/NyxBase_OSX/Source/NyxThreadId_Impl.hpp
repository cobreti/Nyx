#ifndef _NYX_THREADID_IMPL_HPP_
#define _NYX_THREADID_IMPL_HPP_

#include "NyxThreadId.hpp"
#include "NyxRefCount_Impl.hpp"

#include <pthread.h>

namespace NyxOSX
{
	class CThreadId_Impl : public Nyx::CRefCount_Impl<Nyx::CThreadId>
	{
	public:
		CThreadId_Impl();
		virtual ~CThreadId_Impl();
		
	public:
	
		virtual bool IsCurrent() const;

	protected:
	
		pthread_t		m_id;
	};
};


#endif // _NYX_THREADID_IMPL_HPP_
