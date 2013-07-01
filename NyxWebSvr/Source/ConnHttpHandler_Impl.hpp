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

namespace NyxWebSvr
{
    class CConnStream;
    
    
    /**
     *
     */
    class CConnHttpHandler_Impl : public Nyx::CRefCount_Impl<CConnHttpHandler>
    {
    public:
        CConnHttpHandler_Impl();
        virtual ~CConnHttpHandler_Impl();
        
        virtual void HandleStream( const char* header, Nyx::IStreamRW& rStream );
        
        virtual void HandleStream( Nyx::IStreamRW& rStream );
        virtual Nyx::NyxResult OnNewConnection( NyxNet::IConnection* pConnection, NyxNet::IConnectionHandler*& pCloneHandler );
        virtual void OnConnectionTerminated( NyxNet::IConnection* pConnection );
        virtual void CloseConnection( NyxNet::IConnection* pConnection );       
        
        virtual void OnRequest( Nyx::IStreamRW& rStream );
        virtual void OnGetRequest( Nyx::IStreamRW& rStream, char* szPath, char* szParams );
        virtual void OnPostRequest( Nyx::IStreamRW& rStream, char* szPath, char* szParams );
        
        virtual void Write( Nyx::IStreamRW& rStream, char* MimeType, void* pData, int DataLen );
        
    protected:
        
        typedef     Nyx::TBuffer<char>      HeaderBuffer;
        
    protected:
        
        bool            m_bRunning;
        HeaderBuffer    m_Header;
    };
    
}

#endif
