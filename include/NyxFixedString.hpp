#ifndef _NYXFIXEDSTRING_HPP_
#define _NYXFIXEDSTRING_HPP_

#include <stdio.h>
#include <memory.h>

namespace Nyx
{
	template <class TYPE, size_t StringSize>
	class TFixedString
	{
	public:
		TFixedString()
		{
			::memset(m_Buffer, 0, StringSize * sizeof(TYPE));
			m_pEndPtr = m_Buffer;
		}

		~TFixedString() {}

		void Clear()
		{
			m_pEndPtr = m_Buffer;
			*m_pEndPtr = 0;
		}

		size_t Size()								{ return StringSize; }
		size_t Length() const						{ return (m_pEndPtr - (&m_Buffer[0])); }
		void SetLength(const size_t& Size)			{ m_pEndPtr = m_Buffer + Size; }

		operator TYPE* ()							{ return m_Buffer; }
		operator const TYPE* () const				{ return m_Buffer; }

		template <class T>
		TFixedString& operator += (const T* pSrc)
		{
			while ( pSrc != NULL && *pSrc != 0 )
			{
				*m_pEndPtr = *pSrc;
				++ pSrc;
				++ m_pEndPtr;
			}

			*m_pEndPtr = 0;

			return *this;
		}

	protected:

		TYPE		m_Buffer[StringSize];
		TYPE*		m_pEndPtr;
	};
};


#endif // _NYXFIXEDSTRING_HPP_
