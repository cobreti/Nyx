#include "NyxAnsiFile_Impl.hpp"


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
        m_pFile(NULL),
        m_EOL("\r\n")
    {
    }

    
    /**
     *
     */
    CAnsiFile_Impl::~CAnsiFile_Impl()
    {
        if ( m_pFile )
            fclose(m_pFile);
    }


    /**
     *
     */
    Nyx::NyxResult CAnsiFile_Impl::Create( const char* filename )
    {
        if ( m_pFile != NULL )
            return Nyx::kNyxRes_Failure;

        m_pFile = fopen( filename, "w+");
                
        if ( m_pFile == NULL )
            return Nyx::kNyxRes_Failure;

        return Nyx::kNyxRes_Success;
    }


    /**
     *
     */
    void CAnsiFile_Impl::Close()
    {
        if ( m_pFile )
            fclose(m_pFile);
        
        m_pFile = NULL;
    }


    /**
     *
     */
    Nyx::NyxResult CAnsiFile_Impl::Write( const char* data, size_t length )
    {
        if ( m_pFile == NULL )
            return Nyx::kNyxRes_Failure;

        size_t      SizeWritten = 0;
        
        SizeWritten = fwrite(data, length, 1, m_pFile);
        
        if ( SizeWritten != length )
            return Nyx::kNyxRes_Failure;

        return Nyx::kNyxRes_Success;
    }


    /**
     *
     */
    Nyx::NyxResult CAnsiFile_Impl::Write( const Nyx::CAString& data )
    {
        if ( m_pFile == NULL )
            return Nyx::kNyxRes_Failure;

        size_t      SizeWritten = 0;
        
        SizeWritten = fwrite( data.c_str(), data.length(), 1, m_pFile );

        if ( SizeWritten != data.length() )
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


