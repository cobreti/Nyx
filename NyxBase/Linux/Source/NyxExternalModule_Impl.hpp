#ifndef _NYXEXTERNALMODULE_IMPL_HPP_
#define _NYXEXTERNALMODULE_IMPL_HPP_

#include "NyxExternalModule.hpp"
#include "NyxObject_Impl.hpp"
#include "NyxAString.hpp"

namespace NyxLinux
{
	/**
	 *
	 */
	class CExternalModule_Impl : public Nyx::CObject_Impl<Nyx::CExternalModule>
	{
	public:
		CExternalModule_Impl(const char* module);
		virtual ~CExternalModule_Impl();

		virtual Nyx::NyxResult Load();
		virtual Nyx::NyxResult Unload();
		virtual void* GetFct(const char* name);
        virtual Nyx::ExternalModuleHandle GetHandle() const;
        virtual bool Valid() const;

	protected:

		Nyx::CAString		m_Module;
		void*				m_pHandle;
	};
}


#endif // _NYXEXTERNALMODULE_IMPL_HPP_

