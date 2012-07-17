#include "NyxMemoryPool_Impl.hpp"


/**
 *
 */
Nyx::CMemoryPoolRef Nyx::CMemoryPool::Alloc(size_t BlockSize)
{
	return new NyxOSX::CMemoryPool_Impl(BlockSize);
}


namespace NyxOSX
{
    enum
    {
        kAlignment = sizeof(char*)
    };

	/**
	 *
	 */
	CMemoryBlock::CMemoryBlock(	size_t BlockSize,
							   CMemoryBlock* pLink ) :
	m_pLink(pLink),
	m_Size(0),
	m_pBuffer(NULL),
	m_pNextAllocPos(NULL),
	m_SizeLeft(0)
	{
		m_pBuffer = malloc(BlockSize);
		m_Size = BlockSize;
		m_pNextAllocPos = (unsigned char*)m_pBuffer;
		m_SizeLeft = m_Size;
	}
	
	
	/**
	 *
	 */
	CMemoryBlock::~CMemoryBlock()
	{
		free(m_pBuffer);
	}
	
	
	/**
	 *
	 */
	void* CMemoryBlock::GetMemBlock(size_t size)
	{
		void*	pBuffer = NULL;
		
		if ( size <= m_SizeLeft )
		{
			pBuffer = m_pNextAllocPos;
			m_pNextAllocPos += size;
			m_SizeLeft -= size;
		}
		
		return pBuffer;
	}
	
	
	/**
	 *
	 */
	CMemoryPool_Impl::CMemoryPool_Impl(size_t BlockSize) :
	m_BlockSize(BlockSize)
	{
		m_pTopBlock = new CMemoryBlock(m_BlockSize);
		
		m_refMutex = Nyx::CMutex::Alloc();
	}
	
	
	/**
	 *
	 */
	CMemoryPool_Impl::~CMemoryPool_Impl()
	{
        FreeAllBlocks();
	}


	/**
	 *
	 */
	void* CMemoryPool_Impl::AllocMem(size_t size)
	{
		Nyx::TLock<Nyx::CMutex>		Lock(m_refMutex, true);
		
		if ( (size & (kAlignment-1)) != 0 )
			size = ((size >> kAlignment) + 1) << kAlignment;
		
		char*		pPtr = (char*)m_pTopBlock->GetMemBlock(size);
		
		if ( pPtr == NULL )
		{
			m_pTopBlock = new CMemoryBlock(m_BlockSize, m_pTopBlock);
			pPtr = (char*)m_pTopBlock->GetMemBlock(size);
		}
		
		return pPtr;
	}
	
	
	/**
	 *
	 */
	void CMemoryPool_Impl::FreeMem(void* pBlock)
	{
	}
    
    
    /**
     *
     */
    void CMemoryPool_Impl::Clear()
    {
        FreeAllBlocks();
        m_pTopBlock = new CMemoryBlock(m_BlockSize);
    }
    
    
    /**
     *
     */
    void CMemoryPool_Impl::FreeAllBlocks()
    {
		Nyx::TLock<Nyx::CMutex>		Lock(m_refMutex, true);

		CMemoryBlock*		pBlock = NULL;
		
		while ( m_pTopBlock )
		{
			pBlock = m_pTopBlock;
			m_pTopBlock = m_pTopBlock->Link();
			delete pBlock;
		}        
    }
}
