//
//  HttpHandlersTable_Impl.cpp
//  NyxWebSvr
//
//  Created by Danny Thibaudeau on 2013-07-01.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#ifndef NyxWebSvr_HttpHandlersTable_Impl_cpp
#define NyxWebSvr_HttpHandlersTable_Impl_cpp

#include <HttpHandlersTable_Impl.hpp>


namespace NyxWebSvr
{
    
    /**
     *
     */
    CHttpHandlersTable_Impl::CHttpHandlersTable_Impl()
    {
        
    }
    
    
    /**
     *
     */
    CHttpHandlersTable_Impl::~CHttpHandlersTable_Impl()
    {
        
    }
    
    
    /**
     *
     */
    void CHttpHandlersTable_Impl::Set( const char* szPath, NyxWebSvr::CHttpHandlerRef refHandler )
    {
        Nyx::CAString       path(szPath);
        
        m_Handlers[path] = refHandler;
    }
    
    
    /**
     *
     */
    NyxWebSvr::CHttpHandlerRef CHttpHandlersTable_Impl::Get( const char* szPath )
    {
        Nyx::CAString       path(szPath);
        
        if ( m_Handlers.count(path) > 0 )
            return m_Handlers[path];
        
        return NULL;
    }
}


#endif
