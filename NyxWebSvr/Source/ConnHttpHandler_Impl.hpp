//
//  ConnHttpHandler_Impl.hpp
//  NyxWebSvr
//
//  Created by Danny Thibaudeau on 2013-04-29.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#ifndef NyxWebSvr_ConnHttpHandler_Impl_hpp
#define NyxWebSvr_ConnHttpHandler_Impl_hpp

namespace NyxWebSvr
{
    class CConnStream;
    
    
    /**
     *
     */
    class CConnHttpHandler_Impl
    {
    public:
        CConnHttpHandler_Impl();
        virtual ~CConnHttpHandler_Impl();
        
        virtual void HandleStream( CConnStream& rStream );
        
    protected:
        
        bool            m_bRunning;
    };
    
}

#endif
