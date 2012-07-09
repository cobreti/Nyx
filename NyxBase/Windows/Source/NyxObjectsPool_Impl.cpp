#include "NyxObjectsPool_Impl.hpp"
#include "NyxDbg.hpp"

/**
 *
 */
Nyx::CObjectsPoolRef Nyx::CObjectsPool::Alloc(size_t BlockSize)
{
    return new NyxWin32::CObjectsPool_Impl(BlockSize);
}


namespace NyxWin32
{
    //enum
    //{
    //    kPointerSize = sizeof(char*)
    //};


    /**
     *
     */
    CObjectsPool_Impl::CObjectsPool_Impl(size_t BlockSize) :
    m_BlockSize(BlockSize)
    //m_pFreeObjects(NULL)
    {
        m_refMemoryPool = Nyx::CMemoryPool::Alloc(BlockSize);
        m_refMutex = Nyx::CMutex::Alloc();
    }


    /**
     *
     */
    CObjectsPool_Impl::~CObjectsPool_Impl()
    {
    }

    
    /**
     *
     */
    void* CObjectsPool_Impl::AllocMem(size_t size)
    {
        Nyx::TMutexLock         lock(m_refMutex, true);
        ObjectBlock*            pMemBlock = NULL;

        //if ( m_pFreeObjects != NULL )
		if ( m_FreeBlocksTable.count(size) > 0 )
        {
            //ObjectBlock*		pFreeObj = m_pFreeObjects;
			ObjectBlock*		pFreeObj = m_FreeBlocksTable[size];
			//m_pFreeObjects = pFreeObj->Header.pNextBlock;

			if ( pFreeObj->Header.pNextBlock )
				m_FreeBlocksTable[size] = pFreeObj->Header.pNextBlock;
			else
				m_FreeBlocksTable.erase(size);

			pFreeObj->Header.pNextBlock = NULL;

			NYXASSERT( pFreeObj->Header.BlockSize >= size, "block too small" );

            //m_pFreeObjects = pFreeObj->pNextBlock;
            //pFreeObj->pNextBlock = NULL;

            pMemBlock = pFreeObj;
        }
        else
		{
            pMemBlock = (ObjectBlock*)m_refMemoryPool->AllocMem(size + sizeof(ObjectBlock::TBlockHeader));
			pMemBlock->Header.pNextBlock = NULL;
			pMemBlock->Header.BlockSize = size;
		}

        return pMemBlock->data;
    }


    /**
     *
     */
    void CObjectsPool_Impl::FreeMem(void* pBlock)
    {
        Nyx::TMutexLock         lock(m_refMutex, true);

        ObjectBlock*        pObjBlock = (ObjectBlock*)(((char*)pBlock) - sizeof(ObjectBlock::TBlockHeader));
		size_t				BlockSize = pObjBlock->Header.BlockSize;

		if ( m_FreeBlocksTable.count(BlockSize) > 0 )
			pObjBlock->Header.pNextBlock = m_FreeBlocksTable[BlockSize];

        //pObjBlock->Header.pNextBlock = m_pFreeObjects;
        //m_pFreeObjects = pObjBlock;

		m_FreeBlocksTable[BlockSize] = pObjBlock;
    }


	/**
	 *
	 */
	void CObjectsPool_Impl::Clear()
	{
	}

}

