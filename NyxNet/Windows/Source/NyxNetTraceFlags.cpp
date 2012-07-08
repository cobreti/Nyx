#include "NyxNetTraceFlags.hpp"


namespace NyxNet
{
    /**
     *
     */
    CTraceFlags::CTraceFlags() :
        m_Flags(TFlags_Windows),
        m_WideCharSize( sizeof(wchar_t) ),
        m_Reserved(0)
    {
        if ( sizeof(void*) == 4 )
            m_Flags |= TFlags_32Bits;
        else if ( sizeof(void*) == 8 )
            m_Flags |= TFlags_64Bits;
    }


    /**
     *
     */
    CTraceFlags::CTraceFlags(const CTraceFlags& flags) :
        m_Flags(flags.m_Flags),
        m_WideCharSize(flags.m_WideCharSize),
        m_Reserved(0)
    {
    }


    /**
     *
     */
    CTraceFlags::CTraceFlags(const CTraceFlags& flags, const Nyx::UInt16& extra_flags) :
        m_Flags(flags.m_Flags | extra_flags),
        m_WideCharSize(flags.m_WideCharSize),
        m_Reserved(0)
    {
    }


    /**
     *
     */
    CTraceFlags::~CTraceFlags()
    {
    }


    /**
     *
     */
    const CTraceFlags& CTraceFlags::operator = (const CTraceFlags& flags)
    {
        if ( this != &flags )
        {
            m_Flags = flags.m_Flags;
            m_WideCharSize = flags.m_WideCharSize;
            m_Reserved = flags.m_Reserved;
        }

        return *this;
    }
}
