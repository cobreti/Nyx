#ifndef _NYXEXTERNALMODULE_IMPL_HPP_
#define _NYXEXTERNALMODULE_IMPL_HPP_

#include "NyxExternalModule.hpp"
#include "NyxObject_Impl.hpp"
#include "NyxAString.hpp"

namespace NyxWin32
{
    /**
     *
     */
    class CExternalModule_Impl : public Nyx::CObject_Impl<Nyx::CExternalModule>
    {
    public:
        CExternalModule_Impl(const char* szModuleFilename);
        virtual ~CExternalModule_Impl();

        virtual Nyx::NyxResult Load();
        virtual Nyx::NyxResult Unload();
		virtual void* GetFct(const char* name);

    protected:

        Nyx::CAString       m_ModuleFilename;
        HMODULE             m_hModule;
    };
}

#endif // _NYXEXTERNALMODULE_IMPL_HPP_
