#ifndef _NYXTIME_HPP_
#define _NYXTIME_HPP_

#include <time.h>

#if defined(GetCurrentTime)
    #undef GetCurrentTime
#endif

namespace Nyx
{
	class CTime
	{
        friend class CLocalTime;
        
	public:

		static const CTime GetCurrentTime();

	public:
		CTime();
		CTime(const CTime& time);
		CTime(const int& secs, const int& mins = 0, const int& hours = 0);
		~CTime();

		const CTime& operator = (const CTime& time);

		bool operator == (const CTime& time) const;
		bool operator != (const CTime& time) const;
		bool operator < (const CTime& time) const;
		bool operator <= (const CTime& time) const;
		bool operator > (const CTime& time) const;
		bool operator >= (const CTime& time) const;

		const CTime operator - (const CTime& time) const;
		const CTime operator + (const CTime& time) const;

		bool Valid() const		{ return m_bValid; }

		void Clear();

	private:

		time_t		m_Time;
		bool		m_bValid;
	};
}


#endif // _NYXTIME_HPP_

