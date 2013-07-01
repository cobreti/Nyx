//
//  ConnHttpHandler_Impl.hpp
//  NyxWebSvr
//
//  Created by Danny Thibaudeau on 2013-04-29.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#ifndef NyxWebSvr_ConnHttpHandler_Impl_hpp
#define NyxWebSvr_ConnHttpHandler_Impl_hpp

namespace NyxWebSvr
{
    class CConnStream;
    
    
    /**
     *
     */
    class CConnHttpHandler_Impl
    {
    public:
        CConnHttpHandler_Impl();
        virtual ~CConnHttpHandler_Impl();
        
        virtual void HandleStream( Nyx::IStreamRW& rStream );
        
    protected:
        
        typedef     Nyx::TBuffer<char>      HeaderBuffer;
        
    protected:
        
        virtual void OnGetRequest( Nyx::IStreamRW& rStream, char* szPath, char* szParams );
        virtual void OnPostRequest( Nyx::IStreamRW& rStream, char* szPath, char* szParams );
        
        virtual void Write( Nyx::IStreamRW& rStream, char* MimeType, void* pData, int DataLen );

    protected:
        
        bool            m_bRunning;
        HeaderBuffer    m_Header;
    };
    
}

#endif
