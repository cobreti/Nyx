#ifndef NYXANSIFILE_IMPL_HPP
#define NYXANSIFILE_IMPL_HPP

#include <memory.h>

#include "NyxAnsiFile.hpp"
#include "NyxObject_Impl.hpp"
#include "NyxAString.hpp"
#include "NyxWString.hpp"
#include "NyxBuffer.hpp"

#include <stdio.h>


namespace NyxLinux
{
    class CAnsiFile_Impl : public Nyx::CObject_Impl<Nyx::CAnsiFile>
    {
    public:
        CAnsiFile_Impl();
        virtual ~CAnsiFile_Impl();

    public:

        virtual Nyx::NyxResult Create( const char* filename );
        virtual Nyx::NyxResult Open( const char* filename );
        virtual void Close();

        virtual Nyx::NyxResult Write( const char* data, size_t length );
        virtual Nyx::NyxResult Write( const Nyx::CAString& data );
        virtual Nyx::NyxResult Write( const Nyx::CWString& data );
        virtual Nyx::NyxResult WriteEOL();

        virtual Nyx::NyxResult Read( Nyx::CAString& data );

    protected:

        virtual void FillBuffer();

    protected:

        Nyx::CAString           m_AnsiBuffer;
        Nyx::CAString           m_EOL;

        FILE*                   m_pFile;

        Nyx::TBuffer<char>      m_Buffer;

    };
}


#endif // NYXANSIFILE_IMPL_HPP
