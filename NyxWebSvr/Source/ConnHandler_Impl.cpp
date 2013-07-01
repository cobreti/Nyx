//
//  NyxWebSvrConnHandler.cpp
//  NyxWebSvr
//
//  Created by Danny Thibaudeau on 2013-04-28.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#include <NyxNetConnection.hpp>
#include <NyxStreamRW.hpp>

#include "ConnHandler_Impl.hpp"
#include "ConnHttpHandler_Impl.hpp"


namespace NyxWebSvr
{
    
    /**
     *
     */
    CConnHandler_Impl::CConnHandler_Impl(CHttpServer* pServer) :
//    m_pConnection(pConnection),
    m_pServer(pServer),
    m_bRunning(true),
    m_pStream(NULL)
    {
        
    }
    
    
    /**
     *
     */
    CConnHandler_Impl::~CConnHandler_Impl()
    {
        
    }
    
    
    /**
     *
     */
    void CConnHandler_Impl::HandleStream( Nyx::IStreamRW& rStream )
    {
        m_pStream = &rStream;
        //    NyxNet::CSocketRef refSocket = m_pConnection->Socket();
        //    int socketid = refSocket->tcpsocket();
        
        CConnHttpHandler_Impl*      pHandler = new CConnHttpHandler_Impl(m_pServer);
        
        pHandler->HandleStream(rStream);
        
        m_pStream = NULL;
    }

    
    /**
     *
     */
    Nyx::NyxResult CConnHandler_Impl::OnNewConnection( NyxNet::IConnection* pConnection, NyxNet::IConnectionHandler*& pCloneHandler )
    {
        NyxNet::CSocketRef      refSocket = pConnection->Socket();
        NyxNet::CTcpIpSocket*   pTcpIpSocket = refSocket->TcpIpSocket();
        
        NYXTRACE(0x0, L"new connection from "
                 << Nyx::CTF_AnsiText(pTcpIpSocket->ClientAddress().Ip().c_str())
                 << L" port "
                 << Nyx::CTF_Int(pTcpIpSocket->ClientAddress().Port()) );
        
        CConnHandler_Impl* pNewConnection = new CConnHandler_Impl(m_pServer);
        
        pCloneHandler = static_cast<NyxNet::IConnectionHandler*>(pNewConnection);
        
        return Nyx::kNyxRes_Success;
    }
    
    
    /**
     *
     */
    void CConnHandler_Impl::OnConnectionTerminated( NyxNet::IConnection* pConnection )
    {
        NYXTRACE(0x0, L"connection terminated");
        delete this;
    }
    
    
    /**
     *
     */
    void CConnHandler_Impl::CloseConnection( NyxNet::IConnection* pConnection )
    {
        
    }
    
    
    /**
     *
     */
    Nyx::NyxResult CConnHandler_Impl::Read( void* pBuffer, const Nyx::NyxSize& sizeToRead, Nyx::NyxSize& readSize )
    {
        Nyx::NyxResult res = Nyx::kNyxRes_Success;
        
        res = m_pStream->Read(pBuffer, sizeToRead, readSize);
        
        return res;
    }
    
    
    /**
     *
     */
    Nyx::NyxResult CConnHandler_Impl::Write( void* pBuffer, const Nyx::NyxSize& sizeToWrite, Nyx::NyxSize& writtenSize )
    {
        Nyx::NyxResult res = Nyx::kNyxRes_Success;
        
        res = m_pStream->Write(pBuffer, sizeToWrite, writtenSize);
        
        return res;
    }
    
}

