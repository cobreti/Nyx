#ifndef _NYXMODULE_IMPL_HPP_
#define _NYXMODULE_IMPL_HPP_


#include "NyxModule.hpp"
#include "NyxRef.hpp"
#include "NyxObject_Impl.hpp"
#include "NyxModule_Impl.hpp"
#include "NyxTraceModule_Impl.hpp"
#include "NyxThreadModule_Impl.hpp"


DECLARE_NYXOBJECTREF(CModule)

namespace NyxOSX
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
	
		NyxOSX::CTraceModule_Impl		m_TraceModule;
		NyxOSX::CThreadModule_Impl		m_ThreadModule;
        
    private:
        
        NSAutoreleasePool*          m_AutoReleasePool;
	};
}


#endif // _NYXMODULE_IMPL_HPP_
