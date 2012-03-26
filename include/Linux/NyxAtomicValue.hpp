#ifndef _NYXATOMICVALUE_HPP_
#define _NYXATOMICVALUE_HPP_

#include <sys/syscall.h>

namespace Nyx
{
	class CAtomicValue
	{
	public:
		CAtomicValue() : m_Value(0) {}
		~CAtomicValue() {}
		
		const long operator ++ ()
		{
            return __sync_fetch_and_add( &m_Value, 1 ) + 1;
		}
		
		const long operator -- ()
		{
            return __sync_fetch_and_sub(&m_Value, 1) - 1;
		}
		
		const long Value() const { return m_Value; }
	
	private:
		long		m_Value;
	};
}


#endif // _NYXATOMICVALUE_HPP_

