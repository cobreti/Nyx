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
        m_OpennedFork(false),
        m_EOL("\r\n")
    {
    }

    
    /**
     *
     */
    CAnsiFile_Impl::~CAnsiFile_Impl()
    {
        if ( m_OpennedFork )
            Close();
    }


    /**
     *
     */
    Nyx::NyxResult CAnsiFile_Impl::Create( const char* filename )
    {
        if ( m_OpennedFork )
            return Nyx::kNyxRes_Failure;

        FSRef               parentRef;
        FSRef               fileRef;
        Boolean             res;
        CFURLRef            refUrl;
        size_t              len = strlen(filename);
        OSErr               err;
        HFSUniStr255        DataForkName;
        
        err = FSGetDataForkName(&DataForkName);
        if ( err != noErr )
            return Nyx::kNyxRes_Failure;

        //
        // attempt to open the file as existing first
        //
        refUrl = CFURLCreateWithBytes(kCFAllocatorDefault, (uint8*)filename, len, kCFStringEncodingMacRoman, NULL);
        res = CFURLGetFSRef(refUrl, &fileRef);
        
        if ( res ) // file exists : clear data fork
        {
            err = FSDeleteFork(&fileRef, DataForkName.length, DataForkName.unicode);
        }
        else    // file doesn't exists : create it
        {        
            --len;
            while (len > 0 && filename[len] != '/' )
                -- len;

            refUrl = CFURLCreateWithBytes(kCFAllocatorDefault, (uint8*)filename, len, kCFStringEncodingMacRoman, NULL);
            
            res = CFURLGetFSRef(refUrl, &parentRef);
            if ( res == false  )
                return Nyx::kNyxRes_Failure;
        
            UniChar         name[1024];
            UniCharCount    namelen = strlen(filename) - len;
            size_t          index = 0;
            
            while ( len < strlen(filename) )
                name[index++] = filename[++len];
                       
            err = FSCreateFileUnicode( &parentRef, namelen, name, kFSCatInfoNone, NULL, &fileRef, NULL);
            if ( err != noErr )
                return Nyx::kNyxRes_Failure;
        }
        
        
        err = FSOpenFork(&fileRef, DataForkName.length, DataForkName.unicode, fsRdWrPerm, &m_ForkRef);
        if ( err != noErr )
            return Nyx::kNyxRes_Failure;

        m_OpennedFork = true;
        
        return Nyx::kNyxRes_Success;
    }


    /**
     *
     */
    void CAnsiFile_Impl::Close()
    {
        if ( !m_OpennedFork )
            return;

        FSCloseFork(m_ForkRef);
        m_OpennedFork = false;
    }


    /**
     *
     */
    Nyx::NyxResult CAnsiFile_Impl::Write( const char* data, size_t length )
    {
        if ( !m_OpennedFork )
            return Nyx::kNyxRes_Failure;

        OSErr       err;
        
        err = FSWriteFork( m_ForkRef, 0, 0, length, data, NULL);
        if ( err != noErr )
            return Nyx::kNyxRes_Failure;

        return Nyx::kNyxRes_Success;
    }


    /**
     *
     */
    Nyx::NyxResult CAnsiFile_Impl::Write( const Nyx::CAString& data )
    {
        if ( !m_OpennedFork )
            return Nyx::kNyxRes_Failure;

        OSErr       err;
        
        err = FSWriteFork( m_ForkRef, 0, 0, data.length(), data.c_str(), NULL);
        if ( err != noErr )
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


