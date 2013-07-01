//
//  ConnHttpHandler_Impl.cpp
//  NyxWebSvr
//
//  Created by Danny Thibaudeau on 2013-04-29.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#include <Nyx.hpp>
#include <NyxNet.hpp>

#include "ConnHttpHandler_Impl.hpp"
#include "ConnStream.hpp"


namespace NyxWebSvr
{
    
    /**
     *
     */
    CConnHttpHandlerRef CConnHttpHandler::Alloc()
    {
        return new CConnHttpHandler_Impl();
    }
    
    
    /**
     *
     */
    CConnHttpHandler_Impl::CConnHttpHandler_Impl() :
    m_bRunning(true)
    {
        m_Header.Alloc(64 * 1024);
    }
    
    
    /**
     *
     */
    CConnHttpHandler_Impl::~CConnHttpHandler_Impl()
    {
        
    }
    
    
    /**
     *
     */
    void CConnHttpHandler_Impl::HandleStream( const char* header, Nyx::IStreamRW& rStream )
    {
        Nyx::NyxSize readSize = 0;
        Nyx::NyxResult res;

        m_Header.Clear();
        m_Header.WriteData(header, strlen(header));

        if ( NULL != strstr(m_Header.Buffer(), "\n\r") || NULL != strstr(m_Header.Buffer(), "\n\n") )
        {
            OnRequest(rStream);
        }
        else
        {
            while (m_bRunning)
            {
                res = rStream.Read(m_Header.getWritePos(), m_Header.FreeSize(), readSize);
                
                if ( readSize > 0 )
                {
                    m_Header.addDataSize(readSize);
                    *m_Header.getWritePos() = '\0';
                    
                    if ( NULL != strstr(m_Header.Buffer(), "\n\r") || NULL != strstr(m_Header.Buffer(), "\n\n") )
                        OnRequest(rStream);
                }
                
                
                m_bRunning = ( readSize > 0 );
            }
        }
    }
    

    /**
     *
     */
    void CConnHttpHandler_Impl::HandleStream( Nyx::IStreamRW& rStream )
    {
        m_Header.Clear();
        
        Nyx::NyxSize readSize = 0;
        Nyx::NyxResult res;

        while (m_bRunning)
        {
            res = rStream.Read(m_Header.getWritePos(), m_Header.FreeSize(), readSize);
            
            if ( readSize > 0 )
            {
                m_Header.addDataSize(readSize);
                *m_Header.getWritePos() = '\0';
                
                if ( NULL != strstr(m_Header.Buffer(), "\n\r") || NULL != strstr(m_Header.Buffer(), "\n\n") )
                    OnRequest(rStream);
            }
            
            
            m_bRunning = ( readSize > 0 );
        }
        
        NYXTRACE(0x0, L"ending Connection stream handler");
    }
    
    
    /**
     *
     */
    Nyx::NyxResult CConnHttpHandler_Impl::OnNewConnection( NyxNet::IConnection* pConnection, NyxNet::IConnectionHandler*& pCloneHandler )
    {
        NyxNet::CSocketRef      refSocket = pConnection->Socket();
        NyxNet::CTcpIpSocket*   pTcpIpSocket = refSocket->TcpIpSocket();
        
        NYXTRACE(0x0, L"new connection from "
                 << Nyx::CTF_AnsiText(pTcpIpSocket->ClientAddress().Ip().c_str())
                 << L" port "
                 << Nyx::CTF_Int(pTcpIpSocket->ClientAddress().Port()) );
        
        CConnHttpHandler_Impl* pNewConnection = new CConnHttpHandler_Impl();
        
        pCloneHandler = static_cast<NyxNet::IConnectionHandler*>(pNewConnection);
        
        return Nyx::kNyxRes_Success;
    }
    
    
    /**
     *
     */
    void CConnHttpHandler_Impl::OnConnectionTerminated( NyxNet::IConnection* pConnection )
    {
        NYXTRACE(0x0, L"connection terminated");
        delete this;
    }
    
    
    /**
     *
     */
    void CConnHttpHandler_Impl::CloseConnection( NyxNet::IConnection* pConnection )
    {
        
    }
    
    
    /**
     *
     */
    void CConnHttpHandler_Impl::OnRequest( Nyx::IStreamRW& rStream )
    {       
        NYXTRACE(0x0, L"HTTP Header : " << Nyx::CTF_AnsiText(m_Header.Buffer()) );
        
        char* szOp = m_Header.Buffer();
        char* szPath = strstr(szOp, " ");
        *szPath = '\0';
        szPath++;
        char* szProtocol = strstr(szPath, " ");
        *szProtocol = '\0';
        szProtocol ++;
        char* szParams = strstr(szProtocol, "\n");
        *szParams = '\0';
        szParams ++;
        
        NYXTRACE(0x0, L"Operation : " << Nyx::CTF_AnsiText(szOp) );
        NYXTRACE(0x0, L"Path : " << Nyx::CTF_AnsiText(szPath) );
        NYXTRACE(0x0, L"Protocol : " << Nyx::CTF_AnsiText(szProtocol));
        NYXTRACE(0x0, L"Params : " << Nyx::CTF_AnsiText(szParams));
        
        if ( strcmp(szOp, "GET") == 0 )
        {
            OnGetRequest(rStream, szPath, szParams);
        }
        else if ( strcmp(szOp, "POST") == 0 )
        {
            OnPostRequest(rStream, szPath, szParams);
        }
        
        m_Header.Clear();
    }
    

    /**
     *
     */
    void CConnHttpHandler_Impl::OnGetRequest( Nyx::IStreamRW& rStream, char* szPath, char* szParams )
    {
        Nyx::CAString content;

        content = "";
        
        if ( strcmp(szPath, "/") == 0 )
        {
            content =   "<html>\r\n"
                        "<title>WebTraceSvr</title>\r\n"
                        "<body>"
                        "<h1>Web Trace Server</h1>\r\n"
                        "<h2>content at root</h2>\r\n"
                        "</body>\r\n"
                        "</html>\r\n";
        }
        
        if ( strcmp(szPath, "/index" ) == 0 )
        {
            content =   "<html>\r\n"
                        "<title>WebTraceSvr</title>\r\n"
                        "<body>"
                        "<h1>Web Trace Server</h1>\r\n"
                        "<h2>index</h2>\r\n"
                        "</body>\r\n"
                        "</html>\r\n";
        }


        Write(rStream, "text/html; charset=utf-8", content.BufferPtr(), content.length());
}

    
    /**
     *
     */
    void CConnHttpHandler_Impl::OnPostRequest( Nyx::IStreamRW& rStream, char* szPath, char* szParams )
    {
        
    }
    
    
    /**
     *
     */
    void CConnHttpHandler_Impl::Write( Nyx::IStreamRW& rStream, char* MimeType, void* pData, int DataLen )
    {
        char    szDataLen[10];
        Nyx::NyxSize writtenSize = 0;
        
        sprintf(szDataLen, "%i", DataLen);
        
        Nyx::CAString header;
        
        header =    "HTTP/1.1 200 OK\r\n"
                    "Content-Type: ";
        header += MimeType;
        header += "\r\nContent-Length: ";
        header += szDataLen;
        header += "\r\n\r\n";

        rStream.Write(header.BufferPtr(), header.length(), writtenSize);
        rStream.Write(pData, DataLen, writtenSize);
    }
}


