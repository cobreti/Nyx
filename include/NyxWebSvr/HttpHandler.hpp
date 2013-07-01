//
//  HttpHandler.hpp
//  NyxWebSvr
//
//  Created by Danny Thibaudeau on 2013-07-01.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#ifndef NyxWebSvr_HttpHandler_hpp
#define NyxWebSvr_HttpHandler_hpp

//#include <NyxWebSvr/ConnHttpHandler.hpp>

namespace NyxWebSvr
{
    DECLARE_OBJECTREF(CHttpHandler)
    
    class CConnHttpHandler;
    
    class CHttpHandler : public Nyx::CObject
    {
    public:
        
        virtual void OnGetRequest( CConnHttpHandler& rConnHttpHandler, char* szPath, char* szParams ) = 0;
        virtual void OnPostRequest( CConnHttpHandler& rConnHttpHandler, char* szPath, char* szParams ) = 0;
        
    };
}


#endif
