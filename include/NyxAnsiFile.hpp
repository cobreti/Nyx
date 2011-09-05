#ifndef _NYXANSIFILE_HPP_
#define _NYXANSIFILE_HPP_

#include "NyxTextFile.hpp"
#include "NyxRef.hpp"


namespace Nyx
{
    class CWString;
    class CAString;

    DECLARE_OBJECTREF(CAnsiFile);

    class CAnsiFile : public CTextFile
    {
    public:

        static CAnsiFileRef Alloc();

    public:

        virtual NyxResult Create( const char* filename ) = 0;
        virtual NyxResult Open( const char* filename ) = 0;
        virtual void Close() = 0;

        virtual Nyx::NyxResult Write( const char* data, size_t length ) = 0;
        virtual Nyx::NyxResult Write( const Nyx::CAString& data ) = 0;
        virtual Nyx::NyxResult Write( const Nyx::CWString& data ) = 0;
        virtual Nyx::NyxResult WriteEOL() = 0;
        
        virtual Nyx::NyxResult Read( Nyx::CAString& data ) = 0;
        
        
    };
}


#endif // _NYXANSIFILE_HPP_
