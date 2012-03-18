#ifndef _NYXTRACETIMEREFERENCE_H_
#define _NYXTRACETIMEREFERENCE_H_

#include "NyxLocalTime.hpp"
#include "NyxFixedString.hpp"

namespace Nyx
{
    /**
     *
     */
    class CTraceTimeReference
    {
	public:

		/**
		 *	\typedef		tick count
		 */
		typedef		TFixedString<char, 30>			TTickCount;

        /**
         *  \typedef        time string
         */
        typedef     TFixedString<char, 12>          TTimeString;

    public:
        CTraceTimeReference();
        ~CTraceTimeReference();

        const CLocalTime& Time() const          { return m_Time; }
        const TTimeString& TimeString() const   { return m_TimeString; }
        const TTickCount& TickCount() const     { return m_TickCount; }

    protected:

        CLocalTime      m_Time;
        TTickCount      m_TickCount;
        TTimeString     m_TimeString;

    };
}


#endif // _NYXTRACETIMEREFERENCE_H_
