#include "NyxLocalTime.hpp"
#include "NyxAString.hpp"

#include <sys/time.h>
#include <time.h>


namespace Nyx
{
    /**
     *
     */
    const CLocalTime CLocalTime::Get()
    {
        CLocalTime  ltime;
        
		timeval				tp;
		if ( 0 == gettimeofday(&tp, NULL) )
		{
            tm* timeinfo = localtime( &tp.tv_sec );
            
            ltime.m_Sec = timeinfo->tm_sec;
            ltime.m_Min = timeinfo->tm_min;
            ltime.m_Hours = timeinfo->tm_hour;
            ltime.m_ValidityFlag = 1;
		}
        
        return ltime;
    }
    
    
    /**
     *
     */
    CLocalTime::CLocalTime() :
    m_Sec(0),
    m_Min(0),
    m_Hours(0),
    m_ValidityFlag(0)
    {        
    }
    
    
    /**
     *
     */
    CLocalTime::CLocalTime(const CLocalTime& ltime) :
    m_Sec(ltime.m_Sec),
    m_Min(ltime.m_Min),
    m_Hours(ltime.m_Hours),
    m_ValidityFlag(ltime.m_ValidityFlag)
    {        
    }
    
    
    /**
     *
     */
    CLocalTime::CLocalTime( const UInt8& hours,
                            const UInt8& minutes,
                            const UInt8& seconds ) :
    m_Sec(seconds),
    m_Min(minutes),
    m_Hours(hours),
    m_ValidityFlag(1)
    {
    }
    
    
    /**
     *
     */
    CLocalTime::~CLocalTime()
    {
    }
    
    
    /**
     *
     */
    const CLocalTime& CLocalTime::operator = (const CLocalTime& ltime)
    {
        if ( this != &ltime )
        {
            m_Sec = ltime.m_Sec;
            m_Min = ltime.m_Min;
            m_Hours = ltime.m_Hours;
            m_ValidityFlag = ltime.m_ValidityFlag;
        }
        
        return *this;
    }
    
    
    /**
     *
     */
    NyxResult CLocalTime::GetString( Nyx::CAString& str ) const
    {
        if ( !Valid() )
            return kNyxRes_Failure;

        str.Reserve(12);
        str.Format("%02d:%02d:%02d", m_Hours, m_Min, m_Sec );

        return kNyxRes_Success;
    }


    /**
     *
     */
    time_t CLocalTime::ToSeconds() const
    {
        return m_Hours*3600 + m_Min*60 + m_Sec;
    }
    
    
    /**
     *
     */
    void CLocalTime::FromSeconds( const time_t& secs )
    {
        time_t      value = secs;
        
        m_Hours = value / 3600;
        value -= m_Hours * 3600;
        
        m_Min = value / 60;
        value -= m_Min * 60;
        
        m_Sec = value;
    }
}

