#ifndef _NYXBUFFER_HPP_
#define _NYXBUFFER_HPP_

#include "NyxTypes.hpp"
#include <NyxTraces.hpp>

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
		TBuffer() : m_pBuffer(NULL), m_Size(0), m_DataSize(0), m_pNextReadPos(NULL), m_pNextWritePos(NULL) {}
		
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
			
			m_pNextReadPos = NULL;
			m_pNextWritePos = NULL;
			m_DataSize = 0;
			m_pBuffer = (TYPE*)::malloc(BufferSize * sizeof(TYPE));

			if ( NULL == m_pBuffer )
				res = Nyx::kNyxRes_Failure;
			else
			{
				m_Size = BufferSize;
				m_pNextWritePos = m_pBuffer;
				m_pNextReadPos = m_pBuffer;
			}
			
			return res;
		}

		/**
		 * \brief		Clears the buffer content
		 */
		void Clear()
		{
			m_pNextReadPos = m_pBuffer;
			m_pNextWritePos = m_pBuffer;
			m_DataSize = 0;
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

			Nyx::NyxResult		res = Nyx::kNyxRes_Success;
			Nyx::NyxSize		ReadOffset = (m_pNextReadPos - m_pBuffer) / sizeof(TYPE);
			Nyx::NyxSize		WriteOffset = (m_pNextWritePos - m_pBuffer) / sizeof(TYPE);
					
			m_pNextReadPos = NULL;
			m_pNextWritePos = NULL;
			m_pBuffer = (TYPE*)::realloc(m_pBuffer, NewBufferSize*sizeof(TYPE));

			if ( NULL == m_pBuffer )
				res = Nyx::kNyxRes_Failure;
			else
			{
				m_Size = NewBufferSize;
				m_pNextReadPos = m_pBuffer + ReadOffset;;
				m_pNextWritePos = m_pBuffer + WriteOffset;
			}
			
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
		const Nyx::NyxSize TotalSize() const
        {
            return m_Size * Nyx::NyxSize(sizeof(TYPE));
        }
		
		/**
		 *	\brief		Returns the data size
		 */
		const Nyx::NyxSize& DataSize() const		{ return m_DataSize; }
		
		/**
		 *
		 */
		const Nyx::NyxSize FreeSize() const         { return m_Size-m_DataSize; }
		
		/**
		 *	\brief		Adds the given size to data size
		 */
		void addDataSize( const Nyx::NyxSize& size ) 
		{ 
			m_DataSize += size;
			m_pNextWritePos += size;
		}
		
		/**
		 *	\brief		Adjust buffer for a write and returns the write position
		 */
		TYPE* getWritePos()
		{
			return m_pNextWritePos; //m_pBuffer + m_DataSize;
		}
        
        TYPE* getReadPos()
        {
            return m_pNextReadPos;
        }
		
		
		/**
		 *
		 */
		Nyx::NyxSize ReadData( void* pBuffer, const Nyx::NyxSize& size )
		{
			Nyx::NyxSize		ReadSize = (size >= m_DataSize) ? m_DataSize : size;
			
			if ( pBuffer != NULL )
				memcpy(pBuffer, m_pNextReadPos, ReadSize);

			m_DataSize -= ReadSize;
			m_pNextWritePos -= ReadSize;
            memmove(m_pBuffer, m_pBuffer+ReadSize, m_DataSize);
			return ReadSize;
		}


		/**
		 *
		 */
		Nyx::NyxSize WriteData( const void* pBuffer, const Nyx::NyxSize& size )
		{
			if ( !(size < FreeSize()) )
				return 0;

			memcpy( m_pNextWritePos, pBuffer, size );
			m_pNextWritePos += size;
			m_DataSize += size;

			return size;
		}


		/**
		 *
		 */
		Nyx::NyxSize WriteDataResize( const void* pBuffer, const Nyx::NyxSize& size, const Nyx::NyxSize& IncrementSize = 1024 )
		{
			if ( !(size < FreeSize()) )
				Resize( Size() + IncrementSize );

			return WriteData(pBuffer, size);
		}

	protected:
	
		TYPE*			m_pBuffer;
		Nyx::NyxSize	m_Size;
		Nyx::NyxSize	m_DataSize;
		TYPE*			m_pNextReadPos;
		TYPE*			m_pNextWritePos;
        TYPE*           m_pLastPos;
	};
}


#endif // _NYXBUFFER_HPP_


