#include "NyxAnsiFile_Impl.hpp"

#include <string.h>

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
        m_EOL("\r\n"),
        m_pFile(NULL)
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
        if ( NULL != m_pFile )
            return Nyx::kNyxRes_Failure;

        size_t              len = strlen(filename);

        if ( len == 0 )
            return Nyx::kNyxRes_InvalidArgs;

        Nyx::NyxResult      res = Nyx::kNyxRes_Success;
        bool                bRet;

        m_pFile = fopen(filename, "w+");
        if ( NULL == m_pFile )
            return Nyx::kNyxRes_Failure;

        if ( Nyx::Succeeded(res) )
            m_Buffer.Alloc(4096);

        return res;
    }


    /**
     *
     */
    Nyx::NyxResult CAnsiFile_Impl::Open( const char* filename )
    {
        if ( NULL != m_pFile )
            return Nyx::kNyxRes_Failure;

        size_t              len = strlen(filename);

        if ( len == 0 )
            return Nyx::kNyxRes_InvalidArgs;

        Nyx::NyxResult      res = Nyx::kNyxRes_Success;

        m_pFile = fopen(filename, "r+");
        if ( NULL == m_pFile )
            return Nyx::kNyxRes_Failure;

        if ( Nyx::Succeeded(res) )
            m_Buffer.Alloc(4096);

        return Nyx::kNyxRes_Success;
    }


    /**
     *
     */
    void CAnsiFile_Impl::Close()
    {
        if ( NULL != m_pFile )
        {
            fclose(m_pFile);
            m_pFile = NULL;
        }

        m_Buffer.Free();
    }


    /**
     *
     */
    Nyx::NyxResult CAnsiFile_Impl::Write( const char* data, size_t data_length )
    {
        if ( NULL != m_pFile )
            return Nyx::kNyxRes_Failure;

        fwrite(data, data_length, 1, m_pFile);

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
        size_t              sizeRead = fread(pWritePos, SizeToRead, 1, m_pFile);

//        NSData*             data = [[m_idFile readDataOfLength:SizeToRead] retain];
//        Nyx::NyxSize        SizeRead = [data length];

        if ( sizeRead > 0 )
        {
            m_Buffer.addDataSize(sizeRead);
        }
    }

}
