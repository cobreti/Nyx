//
//  HttpServer_Impl.hpp
//  NyxWebSvr
//
//  Created by Danny Thibaudeau on 2013-04-27.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#ifndef NyxWebSvr_HttpServer_Impl_hpp
#define NyxWebSvr_HttpServer_Impl_hpp

#include "HttpServer.hpp"

namespace NyxWebSvr
{
    /**
     *
     */
    class CHttpServer_Impl : public Nyx::CRefCount_Impl<NyxWebSvr::CHttpServer>
    {
    public:
        CHttpServer_Impl();
        virtual ~CHttpServer_Impl();
        
    public:
        
        virtual Nyx::NyxResult Create( NyxNet::TcpIpPort port, const Nyx::UInt32 maxConnections );
        virtual void Start();
        virtual void Stop();
        virtual CHttpHandlersTableRef Handlers();
        
    protected:
        
        NyxNet::CTcpIpServerRef     m_refTcpIpServer;
        CHttpHandlersTableRef       m_refHandlersTable;
    };

}


#endif
