#ifndef _NYXOPAQUELIST_IMPL_HPP_
#define _NYXOPAQUELIST_IMPL_HPP_

#include "NyxOpaqueList.hpp"
#include "NyxRefCount_Impl.hpp"

#include <list>

namespace Nyx
{
	class COpaqueList_Impl : public Nyx::CRefCount_Impl<Nyx::COpaqueList>
	{
	public: // public methods
		COpaqueList_Impl();
		virtual ~COpaqueList_Impl();
		
	public:	// COpaqueList methods
		
		virtual OpaqueListIterator AllocIterator();
		virtual OpaqueListIterator AllocIterator() const;
		virtual void ReleaseIterator( OpaqueListIterator& IteratorHandle ) const;
		virtual void InsertTail( COpaqueDataBucket* pBucket );
		virtual COpaqueDataBucketRef Get( OpaqueListIterator IteratorHandle );
		virtual COpaqueDataBucketRef Get( OpaqueListIterator IteratorHandle ) const;
		virtual size_t Size() const;
		virtual bool GetHeadPos( OpaqueListIterator IteratorHandle );
		virtual bool GetHeadPos( OpaqueListIterator IteratorHandle ) const;
		virtual bool GetTailPos( OpaqueListIterator IteratorHandle );
		virtual bool GetTailPos( OpaqueListIterator IteratorHandle ) const;
		virtual void Clear();
		virtual bool IsValid( OpaqueListIterator IteratorHandle ) const;
		virtual bool IsHead( OpaqueListIterator IteratorHandle );
		virtual bool IsHead( OpaqueListIterator IteratorHandle ) const;
		virtual bool IsTail( OpaqueListIterator IteratorHandle );
		virtual bool IsTail( OpaqueListIterator IteratorHandle ) const;
		virtual bool IncrementIterator( OpaqueListIterator IteratorHandle );
		virtual bool IncrementIterator( OpaqueListIterator IteratorHandle ) const;
		virtual bool DecrementIterator( OpaqueListIterator IteratorHandle );
		virtual bool DecrementIterator( OpaqueListIterator IteratorHandle ) const;
		virtual bool AreIteratorEqual( OpaqueListIterator hIterator1, OpaqueListIterator hIterator2 ) const;
		virtual void CopyIterator( OpaqueListIterator hDst, OpaqueListIterator hSrc ) const;

	protected: // protected types
	
		/**
		 *
		 */
		typedef		std::list<Nyx::COpaqueDataBucketRef>		BucketsList;
		
		
		/**
		 *
		 */
		enum EIteratorType
		{
			eIT_Unknown,
			eIT_ConstIterator,
			eIT_Iterator
		};
		
		/**
		 *
		 */
		class XIteratorData
		{
		public:
			XIteratorData() : m_Type(eIT_Unknown) {}
			~XIteratorData() {}
			
			const EIteratorType&	Type() const		{ return m_Type; }

			void Set( BucketsList::const_iterator* pIter )
			{
				m_pIterator = pIter;
				m_Type = eIT_ConstIterator;
			}
			
			void Set( BucketsList::iterator* pIter )
			{
				m_pIterator = pIter;
				m_Type = eIT_Iterator;
			}
			
			BucketsList::const_iterator* ConstIteratorPtr() const
			{
				return (BucketsList::const_iterator*)m_pIterator;
			}

			BucketsList::iterator* IteratorPtr() const
			{
				return (BucketsList::iterator*)m_pIterator;
			}
			
			bool Valid() const		{ return m_Type != eIT_Unknown && m_pIterator != NULL; }
						
		protected:	// protected members
		
			EIteratorType		m_Type;
			void*				m_pIterator;
			
		private:
		
			XIteratorData(const XIteratorData&);
			const XIteratorData& operator = (const XIteratorData&);
		};
		

	protected:	// protected methods
	
		XIteratorData* HandleToIteratorData( OpaqueListIterator IteratorHandle ) const;
		OpaqueListIterator IteratorDataToHandle( XIteratorData* pIteratorData ) const;
		
	protected:	// protected members
	
		BucketsList		m_Items;
	};
}


#endif // _NYXOPAQUELIST_IMPL_HPP_
