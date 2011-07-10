#ifndef _NYXANSIFILE_IMPL_HPP_
#define _NYXANSIFILE_IMPL_HPP_

#include "NyxAnsiFile.hpp"
#include "NyxObject_Impl.hpp"
#include "NyxAString.hpp"
#include "NyxWString.hpp"

#include <Windows.h>

namespace NyxWin32
{
    class CAnsiFile_Impl : public Nyx::CObject_Impl<Nyx::CAnsiFile>
    {
    public:
        CAnsiFile_Impl();
        virtual ~CAnsiFile_Impl();

    public:

        virtual Nyx::NyxResult Create( const char* filename );
        virtual void Close();
        virtual Nyx::NyxResult Write( const char* data, size_t length );
        virtual Nyx::NyxResult Write( const Nyx::CAString& data );
        virtual Nyx::NyxResult Write( const Nyx::CWString& data );
        virtual Nyx::NyxResult WriteEOL();

    protected:

        HANDLE                  m_hFile;
        Nyx::CAString           m_AnsiBuffer;
        Nyx::CAString           m_EOL;
    };
};

#endif // _NYXANSIFILE_IMPL_HPP_
