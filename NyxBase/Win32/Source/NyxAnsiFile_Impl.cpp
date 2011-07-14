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
}


