#include "NyxAnsiFile_Impl.hpp"


Nyx::CAnsiFileRef Nyx::CAnsiFile::Alloc()
{
    return new NyxWin32::CAnsiFile_Impl();
}


namespace NyxWin32
{
    /**
     *
     */
    CAnsiFile_Impl::CAnsiFile_Impl() :
        m_hFile(INVALID_HANDLE_VALUE),
        m_EOL("\r\n")
    {
    }

    
    /**
     *
     */
    CAnsiFile_Impl::~CAnsiFile_Impl()
    {
        if ( m_hFile != INVALID_HANDLE_VALUE )
            CloseHandle(m_hFile);
    }


    /**
     *
     */
    Nyx::NyxResult CAnsiFile_Impl::Create( const char* filename )
    {
        if ( m_hFile != INVALID_HANDLE_VALUE )
            return Nyx::kNyxRes_Failure;

        m_hFile = ::CreateFileA(    filename,
                                    GENERIC_READ | GENERIC_WRITE,
                                    0,
                                    NULL,
                                    CREATE_ALWAYS,
                                    FILE_ATTRIBUTE_NORMAL,
                                    NULL );
        
        if ( m_hFile == INVALID_HANDLE_VALUE )
            return Nyx::kNyxRes_Failure;

        return Nyx::kNyxRes_Success;
    }


    /**
     *
     */
    Nyx::NyxResult CAnsiFile_Impl::Open( const char* filename )
    {
        if ( m_hFile != INVALID_HANDLE_VALUE )
            return Nyx::kNyxRes_Failure;

        m_hFile = ::CreateFileA(    filename,
                                    GENERIC_READ | GENERIC_WRITE,
                                    0,
                                    NULL,
                                    OPEN_EXISTING,
                                    FILE_ATTRIBUTE_NORMAL,
                                    NULL );
        
        if ( m_hFile == INVALID_HANDLE_VALUE )
            return Nyx::kNyxRes_Failure;

        m_Buffer.Alloc(4096); 

        return Nyx::kNyxRes_Success;
    }


    /**
     *
     */
    void CAnsiFile_Impl::Close()
    {
        if ( m_hFile != INVALID_HANDLE_VALUE )
            ::CloseHandle(m_hFile);
        m_hFile = INVALID_HANDLE_VALUE;
    }


    /**
     *
     */
    Nyx::NyxResult CAnsiFile_Impl::Write( const char* data, size_t length )
    {
        if ( m_hFile == INVALID_HANDLE_VALUE )
            return Nyx::kNyxRes_Failure;

        DWORD       dwBytesWritten = 0;
        BOOL        bRet;

        bRet = ::WriteFile(     m_hFile,
                                data,
                                (DWORD)length,
                                &dwBytesWritten,
                                NULL );

        if ( bRet == FALSE || dwBytesWritten != length )
            return Nyx::kNyxRes_Failure;

        return Nyx::kNyxRes_Success;
    }


    /**
     *
     */
    Nyx::NyxResult CAnsiFile_Impl::Write( const Nyx::CAString& data )
    {
        if ( m_hFile == INVALID_HANDLE_VALUE )
            return Nyx::kNyxRes_Failure;

        DWORD       dwBytesWritten = 0;
        BOOL        bRet;

        bRet = ::WriteFile(     m_hFile,
                                data.c_str(),
                                (DWORD)data.length(),
                                &dwBytesWritten,
                                NULL );

        if ( bRet == FALSE || dwBytesWritten != m_AnsiBuffer.length() )
            return Nyx::kNyxRes_Failure;

        return Nyx::kNyxRes_Success;
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
            data.Reserve(index+1);
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
        
        char*       pWritePos = m_Buffer.getWritePos();    
        DWORD       dwSizeRead(0);
        BOOL        bRet = ReadFile(    m_hFile,
                                        pWritePos,
                                        (DWORD)SizeToRead,
                                        &dwSizeRead,
                                        NULL );
        
        if ( bRet && dwSizeRead > 0 )
        {
            m_Buffer.addDataSize(dwSizeRead);
        }
    }
}


