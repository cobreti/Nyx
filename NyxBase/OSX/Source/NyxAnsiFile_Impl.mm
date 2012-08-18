#include "NyxAnsiFile_Impl.h"


Nyx::CAnsiFileRef Nyx::CAnsiFile::Alloc()
{
    return new NyxOSX::CAnsiFile_Impl();
}


namespace NyxOSX
{
    /**
     *
     */
    CAnsiFile_Impl::CAnsiFile_Impl() :
        m_EOL("\r\n"),
        m_idFile(nil)
    {        
    }

    
    /**
     *
     */
    CAnsiFile_Impl::~CAnsiFile_Impl()
    {
        Close();
    }


    /**
     *
     */
    Nyx::NyxResult CAnsiFile_Impl::Create( const char* filename )
    {
        if ( nil != m_idFile )
            return Nyx::kNyxRes_Failure;
        
        size_t              len = strlen(filename);
        
        if ( len == 0 )
            return Nyx::kNyxRes_InvalidArgs;
        
        Nyx::NyxResult      res = Nyx::kNyxRes_Success;
        bool                bRet;
        
        NSString*   nsFilename = [[[NSString alloc] initWithCString:filename encoding:NSISOLatin2StringEncoding] retain];
        
        NSFileManager* fileManager = [[NSFileManager defaultManager] retain];
        if ( nil == fileManager )
            return Nyx::kNyxRes_Failure;
        
        if ( Nyx::Succeeded(res) )
        {
            bRet = [fileManager createFileAtPath:nsFilename contents:nil attributes:nil];
            if ( !bRet )
                res = Nyx::kNyxRes_Failure;
        }
        
        if ( Nyx::Succeeded(res) )
        {
            m_idFile = [NSFileHandle fileHandleForWritingAtPath:nsFilename];
            if ( nil == m_idFile )
                res = Nyx::kNyxRes_Failure;
            else
                [m_idFile retain];
        }
        else
            res = Nyx::kNyxRes_Failure;
        
        [fileManager release];
        [nsFilename release];

        return res;
    }

    
    /**
     *
     */
    Nyx::NyxResult CAnsiFile_Impl::Open( const char* filename )
    {
        if ( nil != m_idFile )
            return Nyx::kNyxRes_Failure;
        
        size_t              len = strlen(filename);
        
        if ( len == 0 )
            return Nyx::kNyxRes_InvalidArgs;

        Nyx::NyxResult      res = Nyx::kNyxRes_Success;
        
        NSString*   nsFilename = [[[NSString alloc] initWithCString:filename encoding:NSISOLatin2StringEncoding] retain];
        
        m_idFile = [NSFileHandle fileHandleForReadingAtPath:nsFilename];
        if ( nil == m_idFile )
            res = Nyx::kNyxRes_Failure;
        
        [m_idFile retain];
        
        if ( Nyx::Succeeded(res) )
            m_Buffer.Alloc(4096); 
        
        
        [nsFilename release];
        
        return Nyx::kNyxRes_Success;
    }
    

    /**
     *
     */
    void CAnsiFile_Impl::Close()
    {
        if ( nil != m_idFile )
        {
            [m_idFile closeFile];
            [m_idFile release];
            m_idFile = nil;
        }
        
        m_Buffer.Free();
    }


    /**
     *
     */
    Nyx::NyxResult CAnsiFile_Impl::Write( const char* data, size_t data_length )
    {
        if ( nil == m_idFile )
            return Nyx::kNyxRes_Failure;
        
        NSData* nsdata = [[NSData dataWithBytesNoCopy:(void*)data length:data_length freeWhenDone:NO] retain];
                
        [m_idFile writeData: nsdata];
        
        [nsdata release];

        return Nyx::kNyxRes_Success;
    }


    /**
     *
     */
    Nyx::NyxResult CAnsiFile_Impl::Write( const Nyx::CAString& data )
    {
        return Write( data.c_str(), data.length() );
    }


    /**
     *
     */
    Nyx::NyxResult CAnsiFile_Impl::Write( const Nyx::CWString& data )
    {
        m_AnsiBuffer = data;
        return Write(m_AnsiBuffer);
    }


    /**
     *
     */
    Nyx::NyxResult CAnsiFile_Impl::WriteEOL()
    {
        return Write(m_EOL);
    }
    
    
    /**
     *
     */
    Nyx::NyxResult CAnsiFile_Impl::Read( Nyx::CAString& data )
    {
        Nyx::NyxResult          res = Nyx::kNyxRes_Success;
        
        FillBuffer();
        
        if ( m_Buffer.DataSize() == 0 )
            return Nyx::kNyxRes_Failure;
        
        Nyx::NyxSize            index = 0;
        Nyx::NyxSize            len = 0;
        const char*             pC = m_Buffer.getReadPos();
        
        while ( index < m_Buffer.DataSize() && *pC != '\n' )
        {
            ++ pC;
            ++ index;
        }
        
        len = index;
        
        if ( *pC == '\n' )
            ++ index;
                
        if ( index > 0 )
        {
            data.Reserve(index);
            char* pDataPtr = data.BufferPtr();
            
            m_Buffer.ReadData(pDataPtr, index);
            pDataPtr[len] = '\0';
        }
        else
            res = Nyx::kNyxRes_Failure;
        
        return res;
    }
    
    
    /**
     *
     */
    void CAnsiFile_Impl::FillBuffer()
    {
        Nyx::NyxSize        SizeToRead = m_Buffer.FreeSize();
        
        if ( SizeToRead == 0 )
            return;
        
        char*               pWritePos = m_Buffer.getWritePos();
        
        NSData*             data = [[m_idFile readDataOfLength:SizeToRead] retain];
        Nyx::NyxSize        SizeRead = [data length];
        
        if ( SizeRead > 0 )
        {
            [data getBytes:pWritePos length:SizeRead];
            m_Buffer.addDataSize(SizeRead);
        }
        
        [data release];
    }
}


