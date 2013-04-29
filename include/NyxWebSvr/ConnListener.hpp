//
//  ConnListener.hpp
//  NyxWebSvr
//
//  Created by Danny Thibaudeau on 2013-04-27.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#ifndef NyxWebSvr_ConnListener_hpp
#define NyxWebSvr_ConnListener_hpp

#include <Nyx.hpp>
#include <NyxNet.hpp>

namespace NyxWebSvr
{
    DECLARE_OBJECTREF(CConnListener)
    
    /**
     *
     */
    class CConnListener : public Nyx::CObject
    {
    public:
        
        static CConnListenerRef Alloc();
        
        
    public:
        
        virtual Nyx::NyxResult Create( NyxNet::TcpIpPort port, const Nyx::UInt32 maxConnections ) = 0;
        virtual void Start() = 0;
        virtual void Stop() = 0;
    };
    
}


#endif
