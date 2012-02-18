#ifndef _NYXNETTRACEFLAGS_HPP_
#define _NYXNETTRACEFLAGS_HPP_

#include <Nyx.hpp>

namespace NyxNet
{
    class CTraceFlags
    {
    public:

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

    public:
        CTraceFlags();
        CTraceFlags(const CTraceFlags& flags);
        CTraceFlags(const CTraceFlags& flags, const Nyx::UInt16& extra_flags);
        ~CTraceFlags();

        const CTraceFlags& operator = (const CTraceFlags& flags);

        const Nyx::UInt8&       WideCharSize() const        { return m_WideCharSize; }

        bool IsAnsi() const                                 { return (m_Flags & TFlags_Ansi) != 0; }
        bool IsWideChar() const                             { return (m_Flags & TFlags_WideChar) != 0; }

        bool IsWindows() const                              { return (m_Flags & TFlags_Windows) != 0; }
        bool IsOSX() const                                  { return (m_Flags & TFlags_OSX) != 0; }
        bool IsLinux() const                                { return (m_Flags & TFlags_Linux) != 0; }

        bool Is32Bits() const                               { return (m_Flags & TFlags_32Bits) != 0; }
        bool Is64Bits() const                               { return (m_Flags & TFlags_64Bits) != 0; }

    protected:

        
        Nyx::UInt16     m_Flags;
        Nyx::UInt8      m_WideCharSize;
        Nyx::UInt8      m_Reserved;
    };
    /**
     *
     */
    //typedef     Nyx::UInt32     TraceFlags;
    
    /**
     *  Flags for string format
     *      Bits 0 - 3
     */
    //enum
    //{
    //    TFlags_Ansi = 0x0001,
    //    TFlags_WideChar = 0x0002
    //};
    
    
    /**
     *  Flags for platform the trace comes from
     */
    //enum
    //{
    //    TFlags_Windows  = 0x0010,
    //    TFlags_OSX      = 0x0020,
    //    TFlags_Linux    = 0x0040
    //};
    
    
    /**
     *  Flags for the platform version (32 or 64 bits)
     */
    //enum
    //{
    //    TFlags_32Bits   = 0x1000,
    //    TFlags_64Bits   = 0x2000
    //};
}


#endif // _NYXNETTRACEFLAGS_HPP_
