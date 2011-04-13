#ifndef _NYXNETMODULE_HPP_
#define _NYXNETMODULE_HPP_

#include "NyxObject.hpp"
#include "NyxRef.hpp"
#include "NyxAnsiString.hpp"


DECLARE_NSPOBJECTREF(NyxNet, CModule)

namespace NyxNet
{
	class CModule : public Nyx::CObject
	{
	public:
	
		static CModuleRef Alloc();
		static CModule* Default();
		
	public:
	
		virtual Nyx::NyxResult GetHostname( Nyx::CAnsiString& rHostname ) = 0;
		virtual Nyx::NyxResult GetHostIp( const char* szComputerName, Nyx::CAnsiString& rHostIp ) = 0;
	};
}

#endif // _NYXNETMODULE_HPP_
