#ifndef _NYXTRACEMODULE_IMPL_HPP_
#define _NYXTRACEMODULE_IMPL_HPP_

#include "NyxTraceModule.hpp"
#include "NyxTraceCompositor.hpp"

#include <pthread.h>

namespace NyxOSX
{
	class CTraceModule_Impl : public Nyx::CTraceModule
	{
	public:
		CTraceModule_Impl();
		virtual ~CTraceModule_Impl();
		
		virtual void Init();
		virtual void Terminate();
	
	public:
		virtual Nyx::CTraceCompositor* Reference();
		
		virtual void SetThreadDefault( Nyx::CTraceCompositor* pDefault );
		virtual Nyx::CTraceCompositor* ThreadDefault();
		virtual void RemoveThreadDefault();

	protected:

		pthread_key_t					m_keyTraceCompositor;
		Nyx::CTraceCompositor*			m_pReference;
	};
}

#endif // _NYXTRACEMODULE_IMPL_HPP_
