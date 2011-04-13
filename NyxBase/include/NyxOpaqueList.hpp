#ifndef _NYXOPAQUELIST_HPP_
#define _NYXOPAQUELIST_HPP_

#include "NyxOpaqueDataTypes.hpp"
#include "NyxObject.hpp"
#include "NyxRef.hpp"

DECLARE_NYXOBJECTREF(COpaqueList)

namespace Nyx
{
	typedef		OpaqueDataIterator		OpaqueListIterator;

	class COpaqueList : public Nyx::CObject
	{
	public:
		static COpaqueListRef		Alloc();
	
	public:
	
		virtual OpaqueListIterator AllocIterator() = 0;
		virtual OpaqueListIterator AllocIterator() const = 0;
		virtual void ReleaseIterator( OpaqueListIterator& IteratorHandle ) const = 0;
		virtual void InsertTail( COpaqueDataBucket* pBucket ) = 0;
		virtual COpaqueDataBucketRef Get( OpaqueListIterator IteratorHandle ) = 0;
		virtual COpaqueDataBucketRef Get( OpaqueListIterator IteratorHandle ) const = 0;
		virtual size_t Size() const = 0;
		virtual bool GetHeadPos( OpaqueListIterator IteratorHandle ) = 0;
		virtual bool GetHeadPos( OpaqueListIterator IteratorHandle ) const = 0;
		virtual bool GetTailPos( OpaqueListIterator IteratorHandle ) = 0;
		virtual bool GetTailPos( OpaqueListIterator IteratorHandle ) const = 0;
		virtual void Clear() = 0;
		virtual bool IsValid( OpaqueListIterator IteratorHandle ) const = 0;
		virtual bool IsHead( OpaqueListIterator IteratorHandle ) = 0;
		virtual bool IsHead( OpaqueListIterator IteratorHandle ) const = 0;
		virtual bool IsTail( OpaqueListIterator IteratorHandle ) = 0;
		virtual bool IsTail( OpaqueListIterator IteratorHandle ) const = 0;
		virtual bool IncrementIterator( OpaqueListIterator IteratorHandle ) = 0;
		virtual bool IncrementIterator( OpaqueListIterator IteratorHandle ) const = 0;
		virtual bool DecrementIterator( OpaqueListIterator IteratorHandle ) = 0;
		virtual bool DecrementIterator( OpaqueListIterator IteratorHandle ) const = 0;
		virtual bool AreIteratorEqual( OpaqueListIterator hIterator1, OpaqueListIterator hIterator2 ) const = 0;
		virtual void CopyIterator( OpaqueListIterator hDst, OpaqueListIterator hSrc ) const = 0;
	};
	
		
	/**
	 *
	 */
	template <class TYPE>
	class TOpaqueListRef
	{
		typedef		TOpaqueDataBucket<TYPE>		TypeBucket;
	
	public:
		/**
		 *
		 */
		TOpaqueListRef()
		{
			m_refList = Nyx::COpaqueList::Alloc();
		}
		
		/**
		 *
		 */
		virtual ~TOpaqueListRef()
		{
		}
		
		/**
		 *
		 */
		void InsertTail( const TYPE& data )
		{
			m_refList->InsertTail( new TypeBucket(data) );
		}
		
		/**
		 *
		 */
		TYPE Get( OpaqueListIterator hIterator )
		{
			COpaqueDataBucket*	pBucket = m_refList->Get(hIterator);

			if ( pBucket == NULL )
				return NULL;
				
			TypeBucket*	pDataBucket = (TypeBucket*) pBucket;
			
			return pDataBucket->Data();
		}
		
		/**
		 *
		 */
		TYPE Get( OpaqueListIterator hIterator ) const
		{
			COpaqueDataBucket*	pBucket = m_refList->Get(hIterator);

			if ( pBucket == NULL )
				return NULL;
				
			TypeBucket*	pDataBucket = (TypeBucket*) pBucket;
			
			return pDataBucket->Data();
		}
		
		
		/**
		 *
		 */
		COpaqueList* operator -> () { return m_refList; }
		
		/**
		 *
		 */
		const COpaqueList* operator -> () const { return m_refList; }

	protected:
	
		COpaqueListRef		m_refList;
	};
}


#endif // _NYXOPAQUELIST_HPP_
