//
//  ConnHttpHandler.hpp
//  NyxWebSvr
//
//  Created by Danny Thibaudeau on 2013-07-01.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#ifndef NyxWebSvr_ConnHttpHandler_hpp
#define NyxWebSvr_ConnHttpHandler_hpp


#include <Nyx.hpp>
#include <NyxNet.hpp>
#include <NyxWebSvr/HttpHandlersTable.hpp>

namespace NyxWebSvr
{
    DECLARE_OBJECTREF(CConnHttpHandler)
 
//    class CHttpPathHandler;
    
    class CConnHttpHandler : public Nyx::CObject, public NyxNet::IConnectionHandler
    {
    public:
        
        static CConnHttpHandlerRef Alloc();
        
    public:
        
        virtual void HandleStream( const char* header, Nyx::IStreamRW& rStream ) = 0;
        virtual void OnRequest( Nyx::IStreamRW& rStream ) = 0;
        virtual void OnGetRequest( Nyx::IStreamRW& rStream, char* szPath, char* szParams ) = 0;
        virtual void OnPostRequest( Nyx::IStreamRW& rStream, char* szPath, char* szParams ) = 0;
        virtual void Write( char* MimeType, const void* pData, int DataLen ) = 0;
        virtual CHttpHandlersTableRef Handlers() = 0;
        
//        virtual void SetPathHandler( const char* szPath, CHttpPathHandler* pHandler ) = 0;
    };
}



#endif
