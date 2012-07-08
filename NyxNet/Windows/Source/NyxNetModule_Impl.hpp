#ifndef _NYXNETMODULE_IMPL_H_
#define _NYXNETMODULE_IMPL_H_

#include "NyxNetModule.hpp"
#include "NyxObject_Impl.hpp"


namespace NyxNetWin32
{
	class CModule_Impl : public Nyx::CObject_Impl<NyxNet::CModule>
	{
	public:

		static NyxNet::CModule* s_pDefault;

	public:
		CModule_Impl();
		virtual ~CModule_Impl();

	public:

		virtual Nyx::NyxResult GetHostname( Nyx::CAString& rHostname );
		virtual Nyx::NyxResult GetHostIp( const char* szComputerName, Nyx::CAString& rHostIp );

	protected:

		virtual void Init();
		virtual void Terminate();
	};
}


#endif // _NYXNETMODULE_IMPL_H_
