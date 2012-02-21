#include "NyxTime.hpp"
#include "NyxTimeException.hpp"
#include "NyxTraceStream.hpp"

#include <sys/time.h>


namespace Nyx
{
	const CTime CTime::GetCurrentTime()
	{
		CTime retval;

		timeval				tp;
		if ( 0 == gettimeofday(&tp, NULL) )
		{
			retval.m_Time = tp.tv_sec;
			retval.m_bValid = true;
		}

		return retval;
	}


	/**
	 *
	 */
	CTime::CTime() :
	m_Time(0),
	m_bValid(false)
	{
	}


	/**
	 *
	 */
	CTime::CTime(const CTime& time) :
	m_Time(time.m_Time),
	m_bValid(time.m_bValid)
	{
	}


	/**
	 *
	 */
	CTime::CTime(const int& secs, const int& mins, const int& hours) :
	m_Time( hours * 3600 + mins * 60 + secs ),
	m_bValid(true)
	{
	}


	/**
	 *
	 */
	CTime::~CTime()
	{
	}


	/**
	 *
	 */
	const CTime& CTime::operator = (const CTime& time)
	{
		m_Time = time.m_Time;
		m_bValid = time.m_bValid;
		return *this;
	}


	/**
	 *
	 */
	bool CTime::operator == (const CTime& time) const
	{
		if ( !Valid() || !time.Valid() )
			throw Nyx::CTimeException();

		return (m_Time == time.m_Time);
	}


	/**
	 *
	 */
	bool CTime::operator != (const CTime& time) const
	{
		if ( !Valid() || !time.Valid() )
			throw Nyx::CTimeException();

		return (m_Time != time.m_Time);
	}


	/**
	 *
	 */
	bool CTime::operator < (const CTime& time) const
	{
		if ( !Valid() || !time.Valid() )
			throw Nyx::CTimeException();

		return m_Time < time.m_Time;
	}


	/**
	 *
	 */
	bool CTime::operator <= (const CTime& time) const
	{
		if ( !Valid() || !time.Valid() )
			throw Nyx::CTimeException();

		return m_Time <= time.m_Time;
	}


	/**
	 *
	 */
	bool CTime::operator > (const CTime& time) const
	{
		if ( !Valid() || !time.Valid() )
			throw Nyx::CTimeException();

		return m_Time > time.m_Time;
	}


	/**
	 *
	 */
	bool CTime::operator >= (const CTime& time) const
	{
		if ( !Valid() || !time.Valid() )
			throw Nyx::CTimeException();

		return m_Time >= time.m_Time;
	}


	/**
	 *
	 */
	const CTime CTime::operator - (const CTime& time) const
	{
		if ( !Valid() || !time.Valid() )
			throw Nyx::CTimeException();

		CTime	retval(0);

		if ( m_Time > time.m_Time )
			retval.m_Time = m_Time - time.m_Time;

		return retval;
	}


	/**
	 *
	 */
	const CTime CTime::operator + (const CTime& time) const
	{
		if ( !Valid() || !time.Valid() )
			throw Nyx::CTimeException();

		CTime	retval(0);

		retval.m_Time = m_Time + time.m_Time;
		return retval;
	}


	/**
	 *
	 */
	void CTime::Clear()
	{
		m_Time = 0;
		m_bValid = false;
	}
}

