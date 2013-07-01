#ifndef NYXWEBSVR_HTTPSERVER_HPP
#define NYXWEBSVR_HTTPSERVER_HPP

#include <Nyx.hpp>
#include <NyxNet.hpp>
#include <NyxWebSvr/HttpHandlersTable.hpp>

namespace NyxWebSvr
{
    DECLARE_OBJECTREF(CHttpServer)
    
    /**
     *
     */
    class CHttpServer : public Nyx::CObject
    {
    public:
        
        static CHttpServerRef Alloc();
        
    public:
        
        virtual Nyx::NyxResult Create( NyxNet::TcpIpPort port, const Nyx::UInt32 maxConnections ) = 0;
        virtual void Start() = 0;
        virtual void Stop() = 0;
        virtual CHttpHandlersTableRef Handlers() = 0;
    };
    
}


#endif // NYXWEBSVR_HTTPSERVER_HPP
