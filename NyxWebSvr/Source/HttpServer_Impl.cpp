//
//  HttpServer_Impl.cpp
//  NyxWebSvr
//
//  Created by Danny Thibaudeau on 2013-04-27.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#include "HttpServer_Impl.hpp"
#include "ConnHandler_Impl.hpp"
#include "HttpHandlersTable_Impl.hpp"


NyxWebSvr::CHttpServerRef NyxWebSvr::CHttpServer::Alloc()
{
    return new NyxWebSvr::CHttpServer_Impl();
}


namespace NyxWebSvr
{
    /**
     *
     */
    CHttpServer_Impl::CHttpServer_Impl()
    {
        m_refHandlersTable = new NyxWebSvr::CHttpHandlersTable_Impl();
    }
    
    
    /**
     *
     */
    CHttpServer_Impl::~CHttpServer_Impl()
    {
        
    }
    
    
    /**
     *
     */
    Nyx::NyxResult CHttpServer_Impl::Create( NyxNet::TcpIpPort port, const Nyx::UInt32 maxConnections )
    {
        Nyx::NyxResult res = Nyx::kNyxRes_Success;
        CConnHandler_Impl*  pConnHandler = new CConnHandler_Impl(this);
        
        m_refTcpIpServer = NyxNet::CTcpIpServer::Alloc();
        m_refTcpIpServer->Create(port, maxConnections, pConnHandler);
        
        
        return res;
    }
    
    
    /**
     *
     */
    void CHttpServer_Impl::Start()
    {
        m_refTcpIpServer->Start();
    }
    
    
    /**
     *
     */
    void CHttpServer_Impl::Stop()
    {
        m_refTcpIpServer->Stop();
    }


    /**
     *
     */
    CHttpHandlersTableRef CHttpServer_Impl::Handlers()
    {
        return m_refHandlersTable;
    }
}

