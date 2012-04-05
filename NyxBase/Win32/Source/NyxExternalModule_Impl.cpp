#include "NyxExternalModule_impl.hpp"


/**
 *
 */
Nyx::CExternalModule* Nyx::CExternalModule::Alloc(const char* szModule)
{
    return new NyxWin32::CExternalModule_Impl(szModule);
}


namespace NyxWin32
{
    /**
     *
     */
    CExternalModule_Impl::CExternalModule_Impl(const char* szModuleFilename) :
    m_ModuleFilename(szModuleFilename),
    m_hModule(NULL)
    {
    }


    /**
     *
     */
    CExternalModule_Impl::~CExternalModule_Impl()
    {
        Unload();
    }


    /**
     *
     */
    Nyx::NyxResult CExternalModule_Impl::Load()
    {
        if ( m_hModule != NULL )
            return Nyx::kNyxRes_Failure;

        Nyx::NyxResult  ret = Nyx::kNyxRes_Success;

        m_hModule = ::LoadLibraryA(m_ModuleFilename.c_str());
        if ( m_hModule == NULL )
            ret = Nyx::kNyxRes_Failure;

        return ret;
    }


    /**
     *
     */
    Nyx::NyxResult CExternalModule_Impl::Unload()
    {
        Nyx::NyxResult  ret = Nyx::kNyxRes_Success;

        if ( m_hModule != NULL )
        {
            ::FreeLibrary(m_hModule);
            m_hModule = NULL;
        }

        return ret;
    }


    /**
     *
     */
    void* CExternalModule_Impl::GetFct(const char* name)
    {
        if ( m_hModule == NULL )
            return NULL;

        return ::GetProcAddress(m_hModule, name);
    }


    /**
     *
     */
    Nyx::ExternalModuleHandle CExternalModule_Impl::GetHandle() const
    {
        return m_hModule;
    }


    /**
     *
     */
    bool CExternalModule_Impl::Valid() const
    {
        return ( m_hModule != NULL );
    }
}
