//
//  HttpHandlersTable.hpp
//  NyxWebSvr
//
//  Created by Danny Thibaudeau on 2013-07-01.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#ifndef NyxWebSvr_HttpHandlersTable_hpp
#define NyxWebSvr_HttpHandlersTable_hpp

#include <Nyx.hpp>
#include <NyxWebSvr/HttpHandler.hpp>

namespace NyxWebSvr
{
    DECLARE_OBJECTREF(CHttpHandlersTable)
    
    class CHttpHandlersTable : public Nyx::CObject
    {
    public:
        
        virtual void Set( const char* szPath, NyxWebSvr::CHttpHandlerRef ) = 0;
        virtual NyxWebSvr::CHttpHandlerRef Get( const char* szPath ) = 0;
    };
}


#endif
