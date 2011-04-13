#include "NyxOpaqueList_Impl.hpp"


/**
 *
 */
Nyx::COpaqueListRef Nyx::COpaqueList::Alloc()
{
	return new Nyx::COpaqueList_Impl();
}


/**
 *
 */
Nyx::COpaqueList_Impl::COpaqueList_Impl()
{
}


/**
 *
 */
Nyx::COpaqueList_Impl::~COpaqueList_Impl()
{
}


/**
 *
 */
Nyx::OpaqueListIterator Nyx::COpaqueList_Impl::AllocIterator()
{
	XIteratorData*		pIteratorData = new XIteratorData();
	
	pIteratorData->Set( new BucketsList::iterator() );
	*pIteratorData->IteratorPtr() = m_Items.begin();
	
	return IteratorDataToHandle(pIteratorData);
}


/**
 *
 */
Nyx::OpaqueListIterator Nyx::COpaqueList_Impl::AllocIterator() const
{
	XIteratorData*		pIteratorData = new XIteratorData();
	
	pIteratorData->Set( new BucketsList::const_iterator() );
	*pIteratorData->ConstIteratorPtr() = m_Items.begin();
	
	return IteratorDataToHandle(pIteratorData);
}


/**
 *
 */
void Nyx::COpaqueList_Impl::ReleaseIterator( Nyx::OpaqueListIterator& IteratorHandle ) const
{
	if ( NULL == IteratorHandle )
		return;

	XIteratorData*		pIteratorData = HandleToIteratorData(IteratorHandle);
	
	if ( pIteratorData )
	{
		switch (pIteratorData->Type())
		{
			case eIT_ConstIterator:
				{
					BucketsList::const_iterator*	pIter = pIteratorData->ConstIteratorPtr();
					delete pIter;
				}
				break;
			
			case eIT_Iterator:
				{
					BucketsList::iterator*	pIter = pIteratorData->IteratorPtr();
					delete pIter;
				}
				break;
		};
		
		delete pIteratorData;
	}
	
	IteratorHandle = NULL;
}


/**
 *
 */
void Nyx::COpaqueList_Impl::InsertTail( Nyx::COpaqueDataBucket* pBucket )
{
	m_Items.push_back(pBucket);
}


/**
 *
 */
Nyx::COpaqueDataBucketRef Nyx::COpaqueList_Impl::Get( Nyx::OpaqueListIterator IteratorHandle )
{
	if ( IteratorHandle == NULL )
		return NULL;
		
	XIteratorData*	pIteratorData = HandleToIteratorData(IteratorHandle);
	
	switch ( pIteratorData->Type() )
	{
		case eIT_ConstIterator:
			{
				BucketsList::const_iterator* pIter = pIteratorData->ConstIteratorPtr();
				return *(*pIter);
			}
			break;

		case eIT_Iterator:
			{
				BucketsList::iterator* pIter = pIteratorData->IteratorPtr();
				return *(*pIter);
			}
			break;
	};
	
	return NULL;
}


/**
 *
 */
Nyx::COpaqueDataBucketRef Nyx::COpaqueList_Impl::Get( Nyx::OpaqueListIterator IteratorHandle ) const
{
	if ( IteratorHandle == NULL )
		return NULL;
		
	XIteratorData*	pIteratorData = HandleToIteratorData(IteratorHandle);
	
	switch ( pIteratorData->Type() )
	{
		case eIT_ConstIterator:
			{
				BucketsList::const_iterator& Iter = *pIteratorData->ConstIteratorPtr();
				return *Iter;
			}
			break;

		case eIT_Iterator:
			{
				BucketsList::iterator& Iter = *pIteratorData->IteratorPtr();
				return *Iter;
			}
			break;
	};
	
	return NULL;
}


/**
 *
 */
size_t Nyx::COpaqueList_Impl::Size() const
{
	return m_Items.size();
}


/**
 *
 */
bool Nyx::COpaqueList_Impl::GetHeadPos( Nyx::OpaqueListIterator IteratorHandle )
{
	if ( m_Items.empty() )
		return false;
		
	if ( IteratorHandle == NULL )
		return false;
		
	XIteratorData*		pIteratorData = HandleToIteratorData(IteratorHandle);
	
	switch (pIteratorData->Type())
	{
		case eIT_ConstIterator:
			{
				BucketsList::const_iterator&	Iter = *pIteratorData->ConstIteratorPtr();
				Iter = m_Items.begin();
			}
			break;

		case eIT_Iterator:
			{
				BucketsList::iterator&	Iter = *pIteratorData->IteratorPtr();
				Iter = m_Items.begin();
			}
			break;
	};
		
	return true;
}


/**
 *
 */
bool Nyx::COpaqueList_Impl::GetHeadPos( Nyx::OpaqueListIterator IteratorHandle ) const
{
	if ( m_Items.empty() )
		return false;
		
	if ( IteratorHandle == NULL )
		return false;
		
	XIteratorData*		pIteratorData = HandleToIteratorData(IteratorHandle);
	
	switch (pIteratorData->Type())
	{
		case eIT_ConstIterator:
			{
				BucketsList::const_iterator&	Iter = *pIteratorData->ConstIteratorPtr();
				Iter = m_Items.begin();
			}
			break;
		
		case eIT_Iterator:
			return false;
			break;
	};
		
	return true;
}


/**
 *
 */
bool Nyx::COpaqueList_Impl::GetTailPos( Nyx::OpaqueListIterator IteratorHandle )
{
	if ( m_Items.empty() )
		return false;
		
	if ( IteratorHandle == NULL )
		return false;
		
	XIteratorData*		pIteratorData = HandleToIteratorData(IteratorHandle);
	
	switch (pIteratorData->Type())
	{
		case eIT_ConstIterator:
			{
				BucketsList::const_iterator&	Iter = *pIteratorData->ConstIteratorPtr();
				Iter = m_Items.end();
			}
			break;

		case eIT_Iterator:
			{
				BucketsList::iterator&	Iter = *pIteratorData->IteratorPtr();
				Iter = m_Items.end();
			}
			break;
	};
		
	return true;
}


/**
 *
 */
bool Nyx::COpaqueList_Impl::GetTailPos( Nyx::OpaqueListIterator IteratorHandle ) const
{
	if ( m_Items.empty() )
		return false;
		
	if ( IteratorHandle == NULL )
		return false;
		
	XIteratorData*		pIteratorData = HandleToIteratorData(IteratorHandle);
	
	switch (pIteratorData->Type())
	{
		case eIT_ConstIterator:
			{
				BucketsList::const_iterator&	Iter = *pIteratorData->ConstIteratorPtr();
				Iter = m_Items.end();
			}
			break;
		
		case eIT_Iterator:
			return false;
			break;
	};
		
	return true;
}


/**
 *
 */
void Nyx::COpaqueList_Impl::Clear()
{
	m_Items.clear();
}


/**
 *
 */
bool Nyx::COpaqueList_Impl::IsValid( OpaqueListIterator IteratorHandle ) const
{
	if ( IteratorHandle == NULL )
		return false;

	XIteratorData*	pIteratorData = HandleToIteratorData(IteratorHandle);
	
	switch (pIteratorData->Type())
	{
		case eIT_ConstIterator:
			{
				BucketsList::const_iterator&		Iter = *pIteratorData->ConstIteratorPtr();
				return Iter != m_Items.end();
			}
			break;
		case eIT_Iterator:
			{
				BucketsList::iterator&		Iter = *pIteratorData->IteratorPtr();
				return Iter != m_Items.end();
			}
			break;
	};
	
	return false;
}


/**
 *
 */
bool Nyx::COpaqueList_Impl::IsHead( OpaqueListIterator IteratorHandle )
{
	if ( IteratorHandle == NULL )
		return false;
		
	XIteratorData*	pIteratorData = HandleToIteratorData(IteratorHandle);
	
	switch (pIteratorData->Type())
	{
		case eIT_ConstIterator:
			{
				BucketsList::const_iterator&	Iter = *pIteratorData->ConstIteratorPtr();
				return Iter == m_Items.begin();
			}
			break;
		case eIT_Iterator:
			{
				BucketsList::iterator&	Iter = *pIteratorData->IteratorPtr();
				return Iter == m_Items.begin();
			}
			break;
	};
		
	return false;
}


/**
 *
 */
bool Nyx::COpaqueList_Impl::IsHead( OpaqueListIterator IteratorHandle ) const
{
	if ( IteratorHandle == NULL )
		return false;
		
	XIteratorData*	pIteratorData = HandleToIteratorData(IteratorHandle);
	
	switch (pIteratorData->Type())
	{
		case eIT_ConstIterator:
			{
				BucketsList::const_iterator&	Iter = *pIteratorData->ConstIteratorPtr();
				return Iter == m_Items.begin();
			}
			break;
	};
		
	return false;
}


/**
 *
 */
bool Nyx::COpaqueList_Impl::IsTail( OpaqueListIterator IteratorHandle )
{
	if ( IteratorHandle == NULL )
		return false;
		
	XIteratorData*	pIteratorData = HandleToIteratorData(IteratorHandle);
	
	switch (pIteratorData->Type())
	{
		case eIT_ConstIterator:
			{
				BucketsList::const_iterator&	Iter = *pIteratorData->ConstIteratorPtr();
				return Iter == m_Items.end();
			}
			break;
		case eIT_Iterator:
			{
				BucketsList::iterator&	Iter = *pIteratorData->IteratorPtr();
				return Iter == m_Items.end();
			}
			break;
	};
		
	return false;
}


/**
 *
 */
bool Nyx::COpaqueList_Impl::IsTail( OpaqueListIterator IteratorHandle ) const
{
	if ( IteratorHandle == NULL )
		return false;
		
	XIteratorData*	pIteratorData = HandleToIteratorData(IteratorHandle);
	
	switch (pIteratorData->Type())
	{
		case eIT_ConstIterator:
			{
				BucketsList::const_iterator&	Iter = *pIteratorData->ConstIteratorPtr();
				return Iter == m_Items.end();
			}
			break;
	};
		
	return false;
}


/**
 *
 */
bool Nyx::COpaqueList_Impl::IncrementIterator( OpaqueListIterator IteratorHandle )
{
	if ( NULL == IteratorHandle )
		return false;
		
	XIteratorData*	pIteratorData = HandleToIteratorData(IteratorHandle);
	
	switch (pIteratorData->Type())
	{
		case eIT_ConstIterator:
			{
				BucketsList::const_iterator&		Iter = *pIteratorData->ConstIteratorPtr();
				++ Iter;
				return true;
			}
			break;
		case eIT_Iterator:
			{
				BucketsList::iterator&		Iter = *pIteratorData->IteratorPtr();
				++ Iter;
				return true;
			}
			break;
	};

	return false;
}


/**
 *
 */
bool Nyx::COpaqueList_Impl::IncrementIterator( OpaqueListIterator IteratorHandle ) const
{
	if ( NULL == IteratorHandle )
		return false;
		
	XIteratorData*	pIteratorData = HandleToIteratorData(IteratorHandle);
	
	switch (pIteratorData->Type())
	{
		case eIT_ConstIterator:
			{
				BucketsList::const_iterator&		Iter = *pIteratorData->ConstIteratorPtr();
				++ Iter;
				return true;
			}
			break;
	};

	return false;
}


/**
 *
 */
bool Nyx::COpaqueList_Impl::DecrementIterator( OpaqueListIterator IteratorHandle )
{
	if ( NULL == IteratorHandle )
		return false;
		
	XIteratorData*	pIteratorData = HandleToIteratorData(IteratorHandle);
	
	switch (pIteratorData->Type())
	{
		case eIT_ConstIterator:
			{
				BucketsList::const_iterator&		Iter = *pIteratorData->ConstIteratorPtr();
				-- Iter;
				return true;
			}
			break;
		case eIT_Iterator:
			{
				BucketsList::iterator&		Iter = *pIteratorData->IteratorPtr();
				-- Iter;
				return true;
			}
			break;
	};

	return false;
}


/**
 *
 */
bool Nyx::COpaqueList_Impl::DecrementIterator( OpaqueListIterator IteratorHandle ) const
{
	if ( NULL == IteratorHandle )
		return false;
		
	XIteratorData*	pIteratorData = HandleToIteratorData(IteratorHandle);
	
	switch (pIteratorData->Type())
	{
		case eIT_ConstIterator:
			{
				BucketsList::const_iterator&		Iter = *pIteratorData->ConstIteratorPtr();
				-- Iter;
				return true;
			}
			break;
	};

	return false;
}


/**
 *
 */
bool Nyx::COpaqueList_Impl::AreIteratorEqual( OpaqueListIterator hIterator1, OpaqueListIterator hIterator2 ) const
{
	if ( hIterator1 == NULL || hIterator2 == NULL )
		return false;
		
	XIteratorData*	pIteratorData1 = HandleToIteratorData(hIterator1);
	XIteratorData*	pIteratorData2 = HandleToIteratorData(hIterator2);
	
	if ( pIteratorData1->Type() != pIteratorData2->Type() )
		return false;
		
	switch ( pIteratorData1->Type() )
	{
		case eIT_ConstIterator:
			{
				BucketsList::const_iterator&		Iter1 = *pIteratorData1->ConstIteratorPtr();
				BucketsList::const_iterator&		Iter2 = *pIteratorData2->ConstIteratorPtr();
				
				return (Iter1 == Iter2);
			}
			break;
		case eIT_Iterator:
			{
				BucketsList::iterator&		Iter1 = *pIteratorData1->IteratorPtr();
				BucketsList::iterator&		Iter2 = *pIteratorData2->IteratorPtr();
				
				return (Iter1 == Iter2);
			}
			break;
	};

	return false;
}


/**
 *
 */
void Nyx::COpaqueList_Impl::CopyIterator( OpaqueListIterator hDst, OpaqueListIterator hSrc ) const
{
	if ( hDst == NULL || hSrc == NULL )
		return;
		
	XIteratorData*	pDestData = HandleToIteratorData(hDst);
	XIteratorData*	pSrcData = HandleToIteratorData(hSrc);
	
	if ( pDestData->Type() != pSrcData->Type() )
		return;
		
	switch ( pSrcData->Type() )
	{
		case eIT_ConstIterator:
			{
				BucketsList::const_iterator&		DestIter = *pDestData->ConstIteratorPtr();
				BucketsList::const_iterator&		SrcIter = *pSrcData->ConstIteratorPtr();
	
				DestIter = SrcIter;			
			}
			break;
		case eIT_Iterator:
			{
				BucketsList::iterator&		DestIter = *pDestData->IteratorPtr();
				BucketsList::iterator&		SrcIter = *pSrcData->IteratorPtr();
	
				DestIter = SrcIter;			
			}
			break;
	};
}


/**
 *
 */ 
Nyx::COpaqueList_Impl::XIteratorData* Nyx::COpaqueList_Impl::HandleToIteratorData( Nyx::OpaqueListIterator IteratorHandle ) const
{
	return reinterpret_cast<XIteratorData*>(IteratorHandle);
}


/**
 *
 */
Nyx::OpaqueListIterator Nyx::COpaqueList_Impl::IteratorDataToHandle( Nyx::COpaqueList_Impl::XIteratorData* pIteratorData ) const
{
	return reinterpret_cast<OpaqueListIterator>(pIteratorData);
}


