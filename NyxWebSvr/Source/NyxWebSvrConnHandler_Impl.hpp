//
//  NyxWebSvrConnHandler_Impl.hpp
//  NyxWebSvr
//
//  Created by Danny Thibaudeau on 2013-04-28.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#ifndef NyxWebSvr_NyxWebSvrConnHandler_Impl_hpp
#define NyxWebSvr_NyxWebSvrConnHandler_Impl_hpp

#include <Nyx.hpp>
#include <NyxNet.hpp>

namespace NyxWebSvr
{
    /**
     *
     */
    class CConnHandler_Impl : public Nyx::CRefCount_Impl<NyxNet::IConnectionHandler>
    {
    public:
        CConnHandler_Impl(NyxNet::IConnection* pConnection);
        virtual ~CConnHandler_Impl();
        
    public: // IConnectionHandler methods
        
        virtual void HandleStream( Nyx::IStreamRW& rStream );
        virtual Nyx::NyxResult OnNewConnection( NyxNet::IConnection* pConnection, NyxNet::IConnectionHandler*& pCloneHandler );
        virtual void OnConnectionTerminated( NyxNet::IConnection* pConnection );
        virtual void CloseConnection( NyxNet::IConnection* pConnection );

    protected:

        NyxNet::IConnection*        m_pConnection;
        bool                        m_bRunning;

    };
}



#endif
