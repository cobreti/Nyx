#include "NyxAnsiFile_Impl.h"


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
        m_EOL("\r\n"),
        m_idFile(nil)
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
        if ( nil != m_idFile )
            return Nyx::kNyxRes_Failure;
        
        Nyx::NyxResult      res = Nyx::kNyxRes_Success;
        bool                bRet;
        
        NSString*   nsFilename = [[[NSString alloc] initWithCString:filename encoding:NSISOLatin2StringEncoding] retain];
        
        NSFileManager* fileManager = [[NSFileManager defaultManager] retain];
        if ( nil == fileManager )
            return Nyx::kNyxRes_Failure;
        
        if ( Nyx::Succeeded(res) )
        {
            bRet = [fileManager createFileAtPath:nsFilename contents:nil attributes:nil];
            if ( !bRet )
                res = Nyx::kNyxRes_Failure;
        }
        
        if ( Nyx::Succeeded(res) )
        {
            m_idFile = [NSFileHandle fileHandleForWritingAtPath:nsFilename];
            if ( nil == m_idFile )
                res = Nyx::kNyxRes_Failure;
        
            [m_idFile retain];
        }
        else
            res = Nyx::kNyxRes_Failure;
        
        [fileManager release];

        return res;
    }

    
    /**
     *
     */
    Nyx::NyxResult CAnsiFile_Impl::Open( const char* filename )
    {
//        if ( m_OpennedFork )
//            return Nyx::kNyxRes_Failure;
//        
////        FSRef               parentRef;
//        FSRef               fileRef;
//        Boolean             res;
//        CFURLRef            refUrl;
//        size_t              len = strlen(filename);
//        OSErr               err;
//        HFSUniStr255        DataForkName;
//        
//        err = FSGetDataForkName(&DataForkName);
//        if ( err != noErr )
//            return Nyx::kNyxRes_Failure;
//        
//        //
//        // attempt to open the file
//        //
//        refUrl = CFURLCreateWithBytes(kCFAllocatorDefault, (uint8*)filename, len, kCFStringEncodingMacRoman, NULL);
//        res = CFURLGetFSRef(refUrl, &fileRef);
//        
//        if ( !res )
//            return Nyx::kNyxRes_Failure;
//        
//        err = FSOpenFork(&fileRef, DataForkName.length, DataForkName.unicode, fsRdWrPerm, &m_ForkRef);
//        if ( err != noErr )
//            return Nyx::kNyxRes_Failure;
//        
//        m_OpennedFork = true;
        
        return Nyx::kNyxRes_Success;
    }
    

    /**
     *
     */
    void CAnsiFile_Impl::Close()
    {
        if ( nil != m_idFile )
        {
            [m_idFile closeFile];
            [m_idFile release];
            m_idFile = nil;
        }
    }


    /**
     *
     */
    Nyx::NyxResult CAnsiFile_Impl::Write( const char* data, size_t data_length )
    {
        if ( nil == m_idFile )
            return Nyx::kNyxRes_Failure;
        
        NSData* nsdata = [[NSData dataWithBytesNoCopy:(void*)data length:data_length freeWhenDone:NO] retain];
                
        [m_idFile writeData: nsdata];
        
        [nsdata release];

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
}


