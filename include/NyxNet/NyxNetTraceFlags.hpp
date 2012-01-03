#ifndef _NYXNETTRACEFLAGS_HPP_
#define _NYXNETTRACEFLAGS_HPP_

#include <Nyx.hpp>

namespace NyxNet
{
    /**
     *
     */
    typedef     Nyx::UInt32     TraceFlags;
    
    /**
     *  Flags for string format
     *      Bits 0 - 3
     */
    enum
    {
        TFlags_Ansi = 0x0001,
        TFlags_WideChar = 0x0002
    };
    
    
    /**
     *  Flags for platform the trace comes from
     */
    enum
    {
        TFlags_Windows  = 0x0010,
        TFlags_OSX      = 0x0020,
        TFlags_Linux    = 0x0040
    };
    
    
    /**
     *  Flags for the platform version (32 or 64 bits)
     */
    enum
    {
        TFlags_32Bits   = 0x1000,
        TFlags_64Bits   = 0x2000
    };
}


#endif // _NYXNETTRACEFLAGS_HPP_
