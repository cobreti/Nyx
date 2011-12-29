#ifndef _NYXMODULE_IMPL_HPP_
#define _NYXMODULE_IMPL_HPP_


#include "NyxModule.hpp"
#include "NyxRef.hpp"
#include "NyxObject_Impl.hpp"
#include "NyxModule_Impl.hpp"
#include "NyxTraceModule_Impl.hpp"
#include "NyxThreadModule_Impl.hpp"


DECLARE_NYXOBJECTREF(CModule)

namespace NyxLinux
{
	class CModule_Impl : public Nyx::CObject_Impl<Nyx::CModule>
	{
	public:
		static Nyx::CModule*		s_pDefaultModule;

	public:
		CModule_Impl();
		virtual ~CModule_Impl();
		
	public:

		virtual void Init();
		virtual void Terminate();
		virtual Nyx::CTraceModule& Traces();
		virtual Nyx::CThreadModule& Threads();

	protected:
	
		NyxLinux::CTraceModule_Impl		m_TraceModule;
		NyxLinux::CThreadModule_Impl		m_ThreadModule;
  	};
}


#endif // _NYXMODULE_IMPL_HPP_
