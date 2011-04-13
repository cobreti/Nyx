#ifndef _NYXBUFFER_HPP_
#define _NYXBUFFER_HPP_

#include "NyxTypes.hpp"

#include <stdlib.h>

namespace Nyx
{
	template <typename TYPE>
	class TBuffer
	{
	public:
	
		/**
		 *	\brief		constructor
		 */
		TBuffer() : m_pBuffer(NULL), m_Size(0) {}
		
		/**
		 *	\brief		destructor
		 */
		~TBuffer()
		{
			Free();
		}
		
		/**
		 *	\brief		Allocates memory for the buffer
		 *	\param		BufferSize : size of the buffer in units
		 *	\return		NyResult value
		 */
		Nyx::NyxResult Alloc(const Nyx::NyxSize& BufferSize)
		{
			Nyx::NyxResult res = Nyx::kNyxRes_Success;
			
			if ( NULL != m_pBuffer )
				Free();
				
			m_pBuffer = (TYPE*)::malloc(BufferSize * sizeof(TYPE));

			if ( NULL == m_pBuffer )
				res = Nyx::kNyxRes_Failure;
			else
				m_Size = BufferSize;
			
			return res;
		}

		/**
		 *	\brief		Resize the buffer
		 *	\param		NewBufferSize	: new size of the buffer in number of elements
		 *	\return		NyxResult
		 *
		 *	If the buffer isn't already allocated, it will be allocated
		 *
		 */
		Nyx::NyxResult Resize(const Nyx::NyxSize& NewBufferSize)
		{
			if ( NewBufferSize < m_Size )	// don't resize if size if smaller
				return Nyx::kNyxRes_Success;

			Nyx::NyxResult res = Nyx::kNyxRes_Success;
					
			m_pBuffer = (TYPE*)::realloc(m_pBuffer, NewBufferSize*sizeof(TYPE));

			if ( NULL == m_pBuffer )
				res = Nyx::kNyxRes_Failure;
			else
				m_Size = NewBufferSize;
			
			return res;
		}

		/**
		 *	\brief		Release the buffer memory
		 */
		void Free()
		{
			if ( NULL != m_pBuffer )
			{
				::free(m_pBuffer);
				m_pBuffer = NULL;
				m_Size = 0;
			}
		}

		/**
		 *	\brief		const buffer pointer operator
		 */
		const TYPE* Buffer() const { return m_pBuffer; }
		
		/**
		 *	\brief		Buffer pointer operator
		 */
		TYPE* Buffer() { return m_pBuffer; }

		/**
		 *
		 */
		template <class T>
		const T* GetBufferAs() const { return reinterpret_cast<const T*>(m_pBuffer); }

		/**
		 *
		 */
		template <class T>
		T* GetBufferAs() { return reinterpret_cast<T*>(m_pBuffer); }

		/**
		 *	\brief		conversion operator to const void*
		 */
		operator const void* ()	const	{ return reinterpret_cast<const void*>(m_pBuffer); }

		/**
		 *	\brief		conversion operator to void*
		 */
		operator void* ()	{ return reinterpret_cast<void*>(m_pBuffer); }

		/**
		 *	\brief		conversion operator to const TYPE*
		 */
		operator const TYPE* ()	const	{ return reinterpret_cast<const TYPE*>(m_pBuffer); }

		/**
		 *	\brief		conversion operator to TYPE*
		 */
		operator TYPE* ()	{ return reinterpret_cast<TYPE*>(m_pBuffer); }

		/**
		 *	\brief		Returns the buffer size in number of units
		 */
		const Nyx::NyxSize& Size() const { return m_Size; }
		
		/**
		 *	\brief		Returns the buffer size in bytes
		 */
		const Nyx::NyxSize& TotalSize() const { return m_Size * sizeof(TYPE); }
			
	protected:
	
		TYPE*			m_pBuffer;
		Nyx::NyxSize	m_Size;
	};
}


#endif // _NYXBUFFER_HPP_


