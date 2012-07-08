#ifndef _NYXTRACEMODULE_IMPL_HPP_
#define _NYXTRACEMODULE_IMPL_HPP_

#include "NyxTraceModule.hpp"
#include "NyxTraceCompositor.hpp"

#include <windows.h>

namespace NyxWin32
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

		DWORD							m_TlsIndex;
		Nyx::CTraceCompositor*			m_pReference;
	};
}

#endif // _NYXTRACEMODULE_IMPL_HPP_
