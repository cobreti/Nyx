#ifndef _NYXMEMORYPOOL_IMPL_HPP_
#define _NYXMEMORYPOOL_IMPL_HPP_

#include "NyxMemoryPool.hpp"
#include "NyxRefCount_Impl.hpp"
#include "NyxMutex.hpp"
#include "NyxLock.hpp"

namespace NyxLinux
{
	/**
	 *
	 */
	class CMemoryBlock
	{
	public:
		CMemoryBlock(size_t BlockSize, CMemoryBlock* pLink = NULL);
		~CMemoryBlock();
		
		void* GetMemBlock(size_t size);
		
		CMemoryBlock* Link() const	{ return m_pLink; }
		
	protected:
		
		CMemoryBlock*		m_pLink;
		size_t				m_Size;
		void*				m_pBuffer;
		unsigned char*		m_pNextAllocPos;
		size_t				m_SizeLeft;
	};
	
	
	/**
	 *
	 */
	class CMemoryPool_Impl : public Nyx::CRefCount_Impl<Nyx::CMemoryPool>
	{
	public:
		CMemoryPool_Impl(size_t BlockSize);
		virtual ~CMemoryPool_Impl();
		
		virtual void* AllocMem(size_t size);
		virtual void FreeMem(void* pBlock);
		virtual void Clear();

	protected:
		
		void FreeAllBlocks();

	protected:

		size_t				m_BlockSize;
		CMemoryBlock*		m_pTopBlock;
		Nyx::CMutexRef		m_refMutex;
	};
};


#endif // _NYXMEMORYPOOL_IMPL_HPP_
