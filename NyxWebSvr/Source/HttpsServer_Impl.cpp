//
//  HttpsServer_Impl.cpp
//  NyxWebSvr
//
//  Created by Danny Thibaudeau on 2013-04-27.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#include "HttpsServer_Impl.hpp"
#include "ConnHandler_Impl.hpp"
#include "HttpHandlersTable_Impl.hpp"


NyxWebSvr::CHttpsServerRef NyxWebSvr::CHttpsServer::Alloc()
{
    return new NyxWebSvr::CHttpsServer_Impl();
}


namespace NyxWebSvr
{
    /**
     *
     */
    CHttpsServer_Impl::CHttpsServer_Impl()
    {        
        m_refHandlersTable = new NyxWebSvr::CHttpHandlersTable_Impl();
    }
    
    
    /**
     *
     */
    CHttpsServer_Impl::~CHttpsServer_Impl()
    {
        
    }
    
    
    /**
     *
     */
    Nyx::NyxResult CHttpsServer_Impl::Create( NyxNet::TcpIpPort port, const Nyx::UInt32 maxConnections )
    {
        Nyx::NyxResult res = Nyx::kNyxRes_Success;
        CConnHandler_Impl*  pConnHandler = new CConnHandler_Impl(this);
        
        m_refTcpIpServer = NyxNet::CTcpIpServer::Alloc();
        m_refTcpIpServer->SetUseSSL();
        m_refTcpIpServer->Create(port, maxConnections, pConnHandler);
        
        
        return res;
    }
    
    
    /**
     *
     */
    void CHttpsServer_Impl::Start()
    {
        m_refTcpIpServer->Start();
    }
    
    
    /**
     *
     */
    void CHttpsServer_Impl::Stop()
    {
        m_refTcpIpServer->Stop();
    }
    
    
    /**
     *
     */
    CHttpHandlersTableRef CHttpsServer_Impl::Handlers()
    {
        return m_refHandlersTable;
    }
}

