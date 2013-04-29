//
//  ConnListener_Impl.hpp
//  NyxWebSvr
//
//  Created by Danny Thibaudeau on 2013-04-27.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#ifndef NyxWebSvr_ConnListener_Impl_hpp
#define NyxWebSvr_ConnListener_Impl_hpp

#include "ConnListener.hpp"

namespace NyxWebSvr
{
    /**
     *
     */
    class CConnListener_Impl : public Nyx::CRefCount_Impl<NyxWebSvr::CConnListener>
    {
    public:
        CConnListener_Impl();
        virtual ~CConnListener_Impl();
        
    public:
        
        virtual Nyx::NyxResult Create( NyxNet::TcpIpPort port, const Nyx::UInt32 maxConnections );
        virtual void Start();
        virtual void Stop();
        
    protected:
        
        NyxNet::CTcpIpServerRef     m_refTcpIpServer;
    };

}


#endif
