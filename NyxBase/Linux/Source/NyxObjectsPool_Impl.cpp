#include "NyxObjectsPool_Impl.hpp"


/**
 *
 */
Nyx::CObjectsPoolRef Nyx::CObjectsPool::Alloc(size_t BlockSize)
{
    return new NyxLinux::CObjectsPool_Impl(BlockSize);
}


namespace NyxLinux
{
    enum
    {
        kPointerSize = sizeof(char*)
    };


    /**
     *
     */
    CObjectsPool_Impl::CObjectsPool_Impl(size_t BlockSize) :
    m_BlockSize(BlockSize),
    m_pFreeObjects(NULL)
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
        void*                   pMemBlock = NULL;

        if ( m_pFreeObjects != NULL )
        {
            ObjectBlock*       pFreeObj = m_pFreeObjects;
            m_pFreeObjects = pFreeObj->pNextBlock;
            pFreeObj->pNextBlock = NULL;

            pMemBlock = pFreeObj;
        }
        else
            pMemBlock = m_refMemoryPool->AllocMem(size + kPointerSize);

        return ((char*)pMemBlock) + kPointerSize;
    }


    /**
     *
     */
    void CObjectsPool_Impl::FreeMem(void* pBlock)
    {
        Nyx::TMutexLock         lock(m_refMutex, true);

        ObjectBlock*        pObjBlock = (ObjectBlock*)(((char*)pBlock) - kPointerSize);

        pObjBlock->pNextBlock = m_pFreeObjects;
        m_pFreeObjects = pObjBlock;
    }

    /**
     *
     */
    void CObjectsPool_Impl::Clear()
    {
    }

}

