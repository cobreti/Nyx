#ifndef _NYXANSIFILE_IMPL_HPP_
#define _NYXANSIFILE_IMPL_HPP_

#include <stdio.h>
#include <memory.h>

#include "NyxAnsiFile.hpp"
#include "NyxObject_Impl.hpp"
#include "NyxAString.hpp"
#include "NyxWString.hpp"
#include "NyxBuffer.hpp"


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

        FILE*                  	m_pFile;
        Nyx::CAString           m_AnsiBuffer;
        Nyx::CAString           m_EOL;
        Nyx::TBuffer<char>      m_Buffer;
    };
};

#endif // _NYXANSIFILE_IMPL_HPP_
