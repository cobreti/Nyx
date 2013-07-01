#ifndef NYXWEBSVR_HTTPSSERVER_HPP
#define NYXWEBSVR_HTTPSSERVER_HPP

#include <Nyx.hpp>
#include <NyxNet.hpp>
#include <NyxWebSvr/HttpHandlersTable.hpp>
#include <NyxWebSvr/HttpServer.hpp>


namespace NyxWebSvr
{
    DECLARE_OBJECTREF(CHttpsServer)
    
    /**
     *
     */
    class CHttpsServer : public NyxWebSvr::CHttpServer
    {
    public:
        
        static CHttpsServerRef Alloc();
        
        
//    public:
//        
//        virtual Nyx::NyxResult Create( NyxNet::TcpIpPort port, const Nyx::UInt32 maxConnections ) = 0;
//        virtual void Start() = 0;
//        virtual void Stop() = 0;
//        virtual CHttpHandlersTableRef Handlers() = 0;
    };
    
}


#endif // NYXWEBSVR_HTTPSERVER_HPP
