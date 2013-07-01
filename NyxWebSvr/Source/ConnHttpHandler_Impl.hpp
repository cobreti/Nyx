//
//  ConnHttpHandler_Impl.hpp
//  NyxWebSvr
//
//  Created by Danny Thibaudeau on 2013-04-29.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#ifndef NyxWebSvr_ConnHttpHandler_Impl_hpp
#define NyxWebSvr_ConnHttpHandler_Impl_hpp

#include <NyxWebSvr/ConnHttpHandler.hpp>
#include <NyxWebSvr/HttpHandler.hpp>
#include <map>

namespace NyxWebSvr
{
    class CConnStream;
    class CHttpServer;
    
    /**
     *
     */
    class CConnHttpHandler_Impl : public Nyx::CRefCount_Impl<CConnHttpHandler>
    {
    public:
        CConnHttpHandler_Impl(CHttpServer* pServer);
        virtual ~CConnHttpHandler_Impl();
        
        virtual void HandleStream( const char* header, Nyx::IStreamRW& rStream );
        
        virtual void HandleStream( Nyx::IStreamRW& rStream );
        virtual Nyx::NyxResult OnNewConnection( NyxNet::IConnection* pConnection, NyxNet::IConnectionHandler*& pCloneHandler );
        virtual void OnConnectionTerminated( NyxNet::IConnection* pConnection );
        virtual void CloseConnection( NyxNet::IConnection* pConnection );       
        
        virtual void OnRequest( Nyx::IStreamRW& rStream );
        virtual void OnGetRequest( Nyx::IStreamRW& rStream, char* szPath, char* szParams );
        virtual void OnPostRequest( Nyx::IStreamRW& rStream, char* szPath, char* szParams );
        
        virtual void Write( char* MimeType, const void* pData, int DataLen );
        virtual CHttpHandlersTableRef Handlers();
        
//        virtual void SetPathHandler( const char* szPath, CHttpPathHandler* pHandler );
        
    protected:
        
        typedef     Nyx::TBuffer<char>                                  HeaderBuffer;
        
    protected:
        
        bool                        m_bRunning;
        HeaderBuffer                m_Header;
        Nyx::IStreamRW*             m_pStream;
        CHttpServer*                m_pServer;
        CHttpHandlersTableRef       m_refHandlersTable;
    };
    
}

#endif
