#ifndef _NYXLOCALTIME_HPP_
#define _NYXLOCALTIME_HPP_

#include "NyxTypes.hpp"

namespace Nyx
{
    class CAString;

    /**
     *
     */
    class CLocalTime
    {
    public:
        
        static const CLocalTime Get();
        
    public:
        CLocalTime();
        CLocalTime(const CLocalTime& ltime);
        CLocalTime( const UInt8& hours,
                    const UInt8& minutes,
                    const UInt8& seconds );
        ~CLocalTime();
        
        const UInt8& Seconds() const        { return m_Sec; }
        const UInt8& Minutes() const        { return m_Min; }
        const UInt8& Hours() const          { return m_Hours; }
        
        bool Valid() const                  { return m_ValidityFlag != 0; }
        
        const CLocalTime& operator = (const CLocalTime& ltime);

        NyxResult GetString( CAString& str ) const;
        
    protected:
        
        time_t ToSeconds() const;
        void FromSeconds( const time_t& secs );
        
    protected:
        
        UInt8       m_Sec;
        UInt8       m_Min;
        UInt8       m_Hours;
        UInt8       m_ValidityFlag;
    };
}



#endif // _NYXLOCALTIME_HPP_
