#include "NyxExternalModule_Impl.hpp"

#include <dlfcn.h>

/**
 *
 */
Nyx::CExternalModule* Nyx::CExternalModule::Alloc(const char* module)
{
	return new NyxLinux::CExternalModule_Impl(module);
}


namespace NyxLinux
{
	/**
	 *
	 */
	CExternalModule_Impl::CExternalModule_Impl(const char* module) :
	m_Module(module),
	m_pHandle(NULL)
	{
		if ( !m_Module.Find("/", NULL) )
		{
			m_Module = "./";
			m_Module += module;
		}
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
		if ( m_pHandle )
			return Nyx::kNyxRes_Failure;

		m_pHandle = dlopen(m_Module.c_str(), RTLD_LAZY);
		if ( m_pHandle == NULL )
			return Nyx::kNyxRes_Failure;

		return Nyx::kNyxRes_Success;
	}


	/**
	 *
	 */
	Nyx::NyxResult CExternalModule_Impl::Unload()
	{
		if ( m_pHandle )
		{
			dlclose(m_pHandle);
			m_pHandle = NULL;
		}

		return Nyx::kNyxRes_Success;
	}


	/**
	 *
	 */
	void* CExternalModule_Impl::GetFct(const char* name)
	{
		return dlsym(m_pHandle, name);
	}


	/**
	 *
	 */
    Nyx::ExternalModuleHandle CExternalModule_Impl::GetHandle() const
    {
    	return m_pHandle;
    }


    /**
     *
     */
    bool CExternalModule_Impl::Valid() const
    {
    	return m_pHandle != NULL;
    }
}

