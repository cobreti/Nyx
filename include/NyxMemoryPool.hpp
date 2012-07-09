#ifndef _NYXMEMORYPOOL_HPP_
#define _NYXMEMORYPOOL_HPP_

#include "NyxObject.hpp"
#include "NyxRef.hpp"


DECLARE_NYXOBJECTREF(CMemoryPool)


namespace Nyx
{
	class CMemoryPool : public Nyx::CObject
	{
	public:
		
		static CMemoryPoolRef Alloc(size_t BlockSize);
		
	public:
		
		virtual void* AllocMem(size_t size) = 0;
		virtual void FreeMem(void* pBlock) = 0;
		virtual void Clear() = 0;
	};
};


#endif // _NYXMEMORYPOOL_HPP_

