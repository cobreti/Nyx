#ifndef _NYXATOMICVALUE_HPP_
#define _NYXATOMICVALUE_HPP_

#define NOMINMAX

#include <Windows.h>

namespace Nyx
{
	/**
	 *
	 *	\brief		Atomic value object used for atomic increment/decrement operations
	 *
	 */
	class CAtomicValue
	{
	public:
		CAtomicValue() : m_lValue(0) {}
		~CAtomicValue()	{}

		const long operator -- ()
		{
			return ::InterlockedDecrement(&m_lValue);
		}

		const long operator ++ ()
		{
			return ::InterlockedIncrement(&m_lValue);
		}

		const long Value() { return m_lValue; }

	private:
		long			m_lValue;
	};
};


#endif // _NYXATOMICVALUE_HPP_
