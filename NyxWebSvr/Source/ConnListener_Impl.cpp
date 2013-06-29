//
//  ConnListener_Impl.cpp
//  NyxWebSvr
//
//  Created by Danny Thibaudeau on 2013-04-27.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#include "ConnListener_Impl.hpp"
#include "ConnHandler_Impl.hpp"


NyxWebSvr::CConnListenerRef NyxWebSvr::CConnListener::Alloc()
{
    return new NyxWebSvr::CConnListener_Impl();
}


namespace NyxWebSvr
{
    /**
     *
     */
    CConnListener_Impl::CConnListener_Impl()
    {
        
    }
    
    
    /**
     *
     */
    CConnListener_Impl::~CConnListener_Impl()
    {
        
    }
    
    
    /**
     *
     */
    Nyx::NyxResult CConnListener_Impl::Create( NyxNet::TcpIpPort port, const Nyx::UInt32 maxConnections )
    {
        Nyx::NyxResult res = Nyx::kNyxRes_Success;
        CConnHandler_Impl*  pConnHandler = new CConnHandler_Impl(NULL);
        
        m_refTcpIpServer = NyxNet::CTcpIpServer::Alloc();
        m_refTcpIpServer->SetUseSSL();
        m_refTcpIpServer->Create(port, maxConnections, pConnHandler);
        
        
        return res;
    }
    
    
    /**
     *
     */
    void CConnListener_Impl::Start()
    {
        m_refTcpIpServer->Start();
    }
    
    
    /**
     *
     */
    void CConnListener_Impl::Stop()
    {
        m_refTcpIpServer->Stop();
    }
}

