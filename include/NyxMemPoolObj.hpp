#ifndef _NYXMEMPOOLOBJ_HPP_
#define _NYXMEMPOOLOBJ_HPP_

#include "NyxMemoryPool.hpp"

namespace Nyx
{
	class CMemoryPool;
	
	/**
	 *
	 */
	class CMemPoolObjDummyBase
	{
	public:
		CMemPoolObjDummyBase() {}
	};
	
	
	/**
	 *
	 */
	template <class BASETYPE = CMemPoolObjDummyBase>
	class CMemPoolObj : public BASETYPE
	{
	public:
		CMemPoolObj( CMemoryPool* pPool ) : BASETYPE(), m_pMemoryPool(pPool) {}
		virtual ~CMemPoolObj() {}
		
		void* operator new (size_t size, CMemoryPool* pPool)
		{
			return pPool->AllocMem(size);
		}
		
		void operator delete(void* pPtr, CMemoryPool*)
		{
			CMemPoolObj<BASETYPE>*	pObj = static_cast<CMemPoolObj<BASETYPE>*>(pPtr);
			
			pObj->m_pMemoryPool->FreeMem(pPtr);
		}

        void operator delete(void* pPtr)
        {
			CMemPoolObj<BASETYPE>*	pObj = static_cast<CMemPoolObj<BASETYPE>*>(pPtr);
			
			pObj->m_pMemoryPool->FreeMem(pPtr);
        }
		
        CMemoryPool*        MemoryPool() const		{ return m_pMemoryPool; }
		
	private:
		
		CMemoryPool*		m_pMemoryPool;
	};
};


#endif // _NYXMEMPOOLOBJ_HPP_

