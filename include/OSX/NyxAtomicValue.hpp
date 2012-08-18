#ifndef _NYXATOMICVALUE_HPP_
#define _NYXATOMICVALUE_HPP_

#include <libkern/OSAtomic.h>


namespace Nyx
{
	class CAtomicValue
	{
	public:
		CAtomicValue() : m_Value(0) {}
		~CAtomicValue() {}
		
		const int32_t operator ++ ()
		{
            return OSAtomicIncrement32(&m_Value);
		}
		
		const int32_t operator -- ()
		{
            return OSAtomicDecrement32(&m_Value);
		}
		
		const int32_t Value() const { return m_Value; }
	
	private:
        int32_t     m_Value;
	};
}


#endif // _NYXATOMICVALUE_HPP_

