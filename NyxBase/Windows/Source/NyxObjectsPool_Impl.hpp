#ifndef _NYXOBJECTSPOOL_IMPL_HPP_
#define _NYXOBJECTSPOOL_IMPL_HPP_


#include "NyxObjectsPool.hpp"
#include "NyxRefCount_Impl.hpp"
#include "NyxMutex.hpp"
#include "NyxLock.hpp"
#include "NyxMemoryPool.hpp"

#include <map>

namespace NyxWin32
{
    /**
     *
     */
    class CObjectsPool_Impl : public Nyx::CRefCount_Impl<Nyx::CObjectsPool>
    {
    public:
        CObjectsPool_Impl(size_t BlockSize);
        virtual ~CObjectsPool_Impl();

        virtual void* AllocMem(size_t size);
        virtual void FreeMem(void* pBlock);
		virtual void Clear();

    protected:

        struct ObjectBlock
        {
			struct TBlockHeader
			{
				ObjectBlock*		pNextBlock;
				size_t				BlockSize;
			} Header;

			char			data[1];
        };

	protected:

		typedef		std::map<size_t, ObjectBlock*>		FreeBlocksTable;

    protected:

        size_t                      m_BlockSize;

        Nyx::CMutexRef              m_refMutex;
        Nyx::CMemoryPoolRef         m_refMemoryPool;
        //ObjectBlock*                m_pFreeObjects;
		FreeBlocksTable				m_FreeBlocksTable;
    };
}




#endif // _NYXOBJECTSPOOL_IMPL_HPP_
