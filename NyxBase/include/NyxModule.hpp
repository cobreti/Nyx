#ifndef _NYXMODULE_HPP_
#define _NYXMODULE_HPP_

#include "NyxObject.hpp"
#include "NyxTraceModule.hpp"
#include "NyxThreadModule.hpp"
#include "NyxRef.hpp"

DECLARE_NYXOBJECTREF(CModule)

namespace Nyx
{
	class CModule : public CObject
	{
	public:

		static Nyx::CModuleRef Alloc();
		static CModule* GetDefault();

	public:

		virtual void Init() = 0;
		virtual void Terminate() = 0;
		virtual CTraceModule& Traces() = 0;
		virtual CThreadModule& Threads() = 0;
	};
}


#endif // _NYXMODULE_HPP_
