#ifndef _NYXFIXEDSTRING_HPP_
#define _NYXFIXEDSTRING_HPP_

#include <stdio.h>
#include <memory.h>
#include <stdarg.h>

#pragma managed(push, off)

namespace Nyx
{
    size_t TFixedString_Format(char* pBuffer, size_t buffer_size, const char* szFormat, va_list vl );

	template <class TYPE, size_t StringSize>
	class TFixedString
	{
	public:
	//	TFixedString()
	//	{
	//		::memset(m_Buffer, 0, StringSize * sizeof(TYPE));
	//		m_pEndPtr = m_Buffer;
	//	}

	//	~TFixedString() {}

	//	void Clear()
	//	{
	//		m_pEndPtr = m_Buffer;
	//		*m_pEndPtr = 0;
	//	}

	//	size_t Size()								{ return StringSize; }
	//	size_t Length() const						{ return (m_pEndPtr - (&m_Buffer[0])); }
	//	void SetLength(const size_t& Size)			{ m_pEndPtr = m_Buffer + Size; }

 //       const TYPE* c_str() const                   { return m_Buffer; }
 //       TYPE* c_str()                               { return m_Buffer; }

 //       TYPE* GetBuffer()                           { return m_Buffer; }

	//	//operator TYPE* ()							{ return m_Buffer; }
	//	//operator const TYPE* () const				{ return m_Buffer; }

	//	template <class T>
	//	TFixedString& operator += (const T* pSrc)
	//	{
	//		while ( pSrc != NULL && *pSrc != 0 )
	//		{
	//			*m_pEndPtr = *pSrc;
	//			++ pSrc;
	//			++ m_pEndPtr;
	//		}

	//		*m_pEndPtr = 0;

	//		return *this;
	//	}

	//protected:

	//	TYPE		m_Buffer[StringSize];
	//	TYPE*		m_pEndPtr;
	};


    /**
     *
     */
    template <size_t StringSize>
    class TFixedString<char, StringSize>
    {
    public:
		TFixedString()
		{
			::memset(m_Buffer, 0, StringSize);
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

        const char* c_str() const                   { return m_Buffer; }
        char* c_str()                               { return m_Buffer; }

        //char* GetBuffer()                           { return m_Buffer; }

		//operator TYPE* ()							{ return m_Buffer; }
		//operator const TYPE* () const				{ return m_Buffer; }

        void Format( const char* szFormat, ... )
        {
            va_list     vl;
            
            va_start(vl, szFormat);
            
            size_t size = TFixedString_Format( m_Buffer, StringSize, szFormat, vl );
            SetLength(size);
            
            va_end(vl);
        }

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

		char		m_Buffer[StringSize];
		char*		m_pEndPtr;
    };


    /**
     *
     */
    template <size_t StringSize>
    class TFixedString<wchar_t, StringSize>
    {
    public:
		TFixedString()
		{
			::memset(m_Buffer, 0, StringSize * sizeof(wchar_t));
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

        const wchar_t* c_str() const                   { return m_Buffer; }
        wchar_t* c_str()                               { return m_Buffer; }

        //wchar_t* GetBuffer()                           { return m_Buffer; }

		//operator TYPE* ()							{ return m_Buffer; }
		//operator const TYPE* () const				{ return m_Buffer; }

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

		wchar_t		m_Buffer[StringSize];
		wchar_t*	m_pEndPtr;
    };
};

#pragma managed(pop)

#endif // _NYXFIXEDSTRING_HPP_
