#ifndef _NYXOBJECTSPOOL_HPP_
#define _NYXOBJECTSPOOL_HPP_

#include "NyxObject.hpp"
#include "NyxRef.hpp"
#include "NyxMemoryPool.hpp"


DECLARE_NYXOBJECTREF(CObjectsPool)

namespace Nyx
{
    class CObjectsPool : public Nyx::CMemoryPool
    {
    public:

        static CObjectsPoolRef Alloc(size_t BlockSize);

    public:
    };
}



#endif // _NYXOBJECTSPOOL_HPP_
