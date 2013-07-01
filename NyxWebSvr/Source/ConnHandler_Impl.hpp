//
//  ConnHandler_Impl.hpp
//  NyxWebSvr
//
//  Created by Danny Thibaudeau on 2013-04-28.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#ifndef NyxWebSvr_ConnHandler_Impl_hpp
#define NyxWebSvr_ConnHandler_Impl_hpp

#include <Nyx.hpp>
#include <NyxNet.hpp>

#include "ConnStream.hpp"

namespace NyxWebSvr
{
    class CHttpServer;
    
    /**
     *
     */
    class CConnHandler_Impl :   public Nyx::CRefCount_Impl<NyxNet::IConnectionHandler>,
                                public NyxWebSvr::CConnStream
    {
    public:
        CConnHandler_Impl(CHttpServer* pServer);
        virtual ~CConnHandler_Impl();
        
    public: // IConnectionHandler methods
        
        virtual void HandleStream( Nyx::IStreamRW& rStream );
        virtual Nyx::NyxResult OnNewConnection( NyxNet::IConnection* pConnection, NyxNet::IConnectionHandler*& pCloneHandler );
        virtual void OnConnectionTerminated( NyxNet::IConnection* pConnection );
        virtual void CloseConnection( NyxNet::IConnection* pConnection );

    public: // CConnStream
        
        virtual Nyx::NyxResult Read( void* pBuffer, const Nyx::NyxSize& sizeToRead, Nyx::NyxSize& readSize );
        virtual Nyx::NyxResult Write( void* pBuffer, const Nyx::NyxSize& sizeToWrite, Nyx::NyxSize& writtenSize );
        virtual NyxNet::CSocketRef Socket() { return NULL; }
        
    protected:

//        NyxNet::IConnection*        m_pConnection;
        CHttpServer*                m_pServer;
        bool                        m_bRunning;
        Nyx::IStreamRW*             m_pStream;

    };
}



#endif
