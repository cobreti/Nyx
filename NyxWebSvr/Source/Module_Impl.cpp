#include "Module_Impl.hpp"


NyxWebSvr::CModuleRef NyxWebSvr::CModule::Alloc()
{
    return new NyxWebSvr::CModule_Impl();
}


namespace NyxWebSvr
{
    
    /**
     *
     */
    CModule_Impl::CModule_Impl()
    {
        
    }
    
    
    /**
     *
     */
    CModule_Impl::~CModule_Impl()
    {
        
    }
    
}
