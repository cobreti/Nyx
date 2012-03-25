#include "NyxTraceTimeReference.hpp"
#include "NyxAString.hpp"

#include <sys/time.h>

namespace Nyx
{
    /**
     *
     */
    CTraceTimeReference::CTraceTimeReference()
    {
        Nyx::CAString   time_str;

        m_Time = Nyx::CLocalTime::Get();
        m_Time.GetString(time_str);
        m_TimeString += time_str.c_str();

        timeval t;
        gettimeofday(&t, NULL);
        m_TickCount.Format("%012i.%06i", (int)t.tv_sec, (int)t.tv_usec );
	    //size_t		Size = 0;
	    //Size = sprintf_s( m_TickCount.GetBuffer(), m_TickCount.Size(), "%lu.0", GetTickCount() );
	    //m_TickCount.SetLength(Size);
    }


    /**
     *
     */
    CTraceTimeReference::~CTraceTimeReference()
    {
    }
}
