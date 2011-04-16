#ifndef _NYXATOMICVALUE_HPP_
#define _NYXATOMICVALUE_HPP_


#include <carbon/carbon.h>


namespace Nyx
{
	class CAtomicValue
	{
	public:
		CAtomicValue() : m_Value(0) {}
		~CAtomicValue() {}
		
		const SInt32 operator ++ ()
		{
			return IncrementAtomic(&m_Value) + 1;
		}
		
		const SInt32 operator -- ()
		{
			return DecrementAtomic(&m_Value) - 1;
		}
		
		const SInt32 Value() const { return m_Value; }
	
	private:
		SInt32		m_Value;
	};
}


#endif // _NYXATOMICVALUE_HPP_

