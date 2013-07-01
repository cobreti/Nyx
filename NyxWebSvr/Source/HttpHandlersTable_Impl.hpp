//
//  HttpHandlersTable_Impl.hpp
//  NyxWebSvr
//
//  Created by Danny Thibaudeau on 2013-07-01.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#ifndef NyxWebSvr_HttpHandlersTable_Impl_hpp
#define NyxWebSvr_HttpHandlersTable_Impl_hpp

#include <NyxWebSvr/HttpHandlersTable.hpp>
#include <map>

namespace NyxWebSvr
{
    /**
     *
     */
    class CHttpHandlersTable_Impl : public Nyx::CRefCount_Impl<CHttpHandlersTable>
    {
    public:
        CHttpHandlersTable_Impl();
        virtual ~CHttpHandlersTable_Impl();
        
        virtual void Set( const char* szPath, NyxWebSvr::CHttpHandlerRef );
        virtual NyxWebSvr::CHttpHandlerRef Get( const char* szPath );
        
        
    protected:
        
        typedef std::map<Nyx::CAString, NyxWebSvr::CHttpHandlerRef> HandlersTable;
        
    protected:
        
        HandlersTable       m_Handlers;
    };
}


#endif
