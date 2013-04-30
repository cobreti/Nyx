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
    CConnHttpHandler_Impl::CConnHttpHandler_Impl() :
    m_bRunning(true)
    {
        
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
    void CConnHttpHandler_Impl::HandleStream( CConnStream& rStream )
    {
        Nyx::TBuffer<char>          sockBuffer;
        
        sockBuffer.Alloc(4096);
        
        while (m_bRunning)
        {
            Nyx::CAString content;
            Nyx::CAString header;
            char buffer[4096];
            Nyx::NyxResult res;
            Nyx::NyxSize readSize = 0;
            Nyx::NyxSize writtenSize = 0;
            
            header =    "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html; charset=utf-8\r\n"
            //                    "set-Cookie: test;\r\n"
            "Content-Length: 82\r\n\r\n";
            //                "Server: NyxWebServer\n";
            
            content =   "<html>\r\n"
            "<title>WebTraceSvr</title>\r\n"
            "<body>"
            "<h1>Web Trace Server</h1>\r\n"
            "</body>\r\n"
            "</html>\r\n";
            
            
            //        ::memset(buffer, 0, sizeof(buffer));
            
            
            res = rStream.Read(sockBuffer.getWritePos(), sockBuffer.FreeSize(), readSize);
            //            readSize = SSL_read(m_ssl, sockBuffer.getWritePos(), sockBuffer.FreeSize());
            if ( readSize > 0 )
            {
//                NyxNet::CSocketRef refSocket = m_pConnection->Socket();
                NyxNet::CSocketRef      refSocket = rStream.Socket();
                NyxNet::CTcpIpSocket*   pTcpIpSocket = refSocket->TcpIpSocket();
                
                NYXTRACE(0x0, L"receiving data from "
                         << Nyx::CTF_AnsiText(pTcpIpSocket->ClientAddress().Ip().c_str())
                         << L" port "
                         << Nyx::CTF_Int(pTcpIpSocket->ClientAddress().Port()) );
                
                sockBuffer.addDataSize(readSize);
                char* pStart = sockBuffer.getReadPos();
                char* pCur = pStart;
                size_t size = 0;
                //                size_t readBufferSize = 0;
                
                while ( size < sockBuffer.DataSize() )
                {
                    if ( *pCur == '\n' )
                    {
                        *pCur = '\0';
                        sockBuffer.ReadData(buffer, size+1);
                        pCur = sockBuffer.getReadPos();
                        size = 0;
                        
                        NYXTRACE(0x0, L"line received : " << Nyx::CTF_AnsiText(buffer) );
                        NYXTRACE(0x0, L"line len : " << Nyx::CTF_Int(buffer[0]) << L" : " << Nyx::CTF_Int(strlen(buffer)) );
                    }
                    else
                    {
                        if ( *pCur == '\r' )
                            *pCur = 0;
                        
                        ++ pCur;
                        ++ size;
                    }
                }
                
                NYXTRACE(0x0, L"sockbuffer remaining data size : " << Nyx::CTF_Int(sockBuffer.DataSize()) );
                
                //            readSize = BIO_read(m_bio, buffer, 4095);
                
                
                //            NYXTRACE(0x0, L"data received - readsize : " << readSize );
                
                //    if ( readSize == 0 )
                //    {
                //        int errorCode = SSL_get_error(m_ssl, readSize);
                //
                //        NYXTRACE(0x0, L"ssl error code: " << ERR_error_string(errorCode, NULL) );
                //    }
                
                //    if ( readSize > 0 )
                {
                    //                NYXTRACE(0x0, Nyx::CTF_AnsiText(buffer) );
                }
                
                //                SSL_write(m_ssl, header.BufferPtr(), header.length());
                //                SSL_write(m_ssl, content.BufferPtr(), content.length());
                rStream.Write(header.BufferPtr(), header.length(), writtenSize);
                rStream.Write(content.BufferPtr(), content.length(), writtenSize );
            }
            
            m_bRunning = ( readSize > 0 );
            //        else
            //        {
            //            NYXTRACE(0x0, L"SSL_read return value : " << Nyx::CTF_Int(readSize));
            //
            //            sleep(1);
            //        }
        }
        
        NYXTRACE(0x0, L"ending Connection stream handler");        
    }
}