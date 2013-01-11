#include "NyxAnsiFile_Impl.hpp"


Nyx::CAnsiFileRef Nyx::CAnsiFile::Alloc()
{
    return new NyxLinux::CAnsiFile_Impl();
}


namespace NyxLinux
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
        if ( m_pFile )
            return Nyx::kNyxRes_Failure;

        m_pFile = fopen(filename, "w+");
        
        if ( !m_pFile )
            return Nyx::kNyxRes_Failure;

        return Nyx::kNyxRes_Success;
    }


    /**
     *
     */
    Nyx::NyxResult CAnsiFile_Impl::Open( const char* filename )
    {
        if ( m_pFile )
            return Nyx::kNyxRes_Failure;

        m_pFile = fopen( filename, "r" );
        
        if ( !m_pFile )
            return Nyx::kNyxRes_Failure;

        m_Buffer.Alloc(4096); 

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
        if ( !m_pFile )
            return Nyx::kNyxRes_Failure;

        size_t		writtenSize = 0;

        writtenSize = fwrite(data, length, sizeof(char), m_pFile );

        if ( writtenSize != length )
            return Nyx::kNyxRes_Failure;

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
        
        char*       pWritePos = m_Buffer.getWritePos();    
        size_t		sizeRead = 0;

        sizeRead = fread( pWritePos, SizeToRead, 1, m_pFile );
        
        if ( sizeRead > 0 )
        {
            m_Buffer.addDataSize(sizeRead);
        }
    }
}


