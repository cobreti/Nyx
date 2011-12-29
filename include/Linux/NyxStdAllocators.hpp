#ifndef _NYXSTDALLOCATORS_HPP_
#define _NYXSTDALLOCATORS_HPP_

#include <NyxObjectsPool.hpp>
#include <list>

namespace Nyx
{
    template<class _Ty, class Pool>
    class StdListAllocator
	{	// Nyx allocator for objects of class _Ty
    protected:
        
        Nyx::CObjectsPoolRef            m_refObjectsPool;
        
    public:
        typedef _Ty value_type;
        typedef value_type  *pointer;
        typedef value_type & reference;
        typedef const value_type  *const_pointer;
        typedef const value_type & const_reference;
        typedef size_t size_type;
        
        
	    template<class _Other>
        struct rebind
        {	// convert an allocator<_Ty> to an allocator <_Other>
            typedef StdListAllocator<_Other, Pool> other;
        };
        
	    pointer address(reference _Val) const
        {	// return address of mutable _Val
		    return (&_Val);
        }
        
	    const_pointer address(const_reference _Val) const
        {	// return address of nonmutable _Val
		    return (&_Val);
        }
        
        StdListAllocator()
        {	// construct default allocator (do nothing)
            //m_refObjectsPool = Nyx::CObjectsPool::Alloc(2048, sizeof(_Ty));
            m_refObjectsPool = Pool::Instance();
        }
        
        StdListAllocator(const StdListAllocator<_Ty, Pool>&)
        {	// construct by copying (do nothing)
            m_refObjectsPool = Pool::Instance();
        }
        
	    template<class _Other>
        StdListAllocator(const StdListAllocator<_Other, Pool>&)
        {	// construct from a related allocator (do nothing)
            m_refObjectsPool = Pool::Instance();
        }
        
	    template<class _Other>
        StdListAllocator<_Ty, Pool>& operator=(const StdListAllocator<_Other, Pool>&)
        {	// assign from a related allocator (do nothing)
            return (*this);
        }
        
	    void deallocate(pointer _Ptr, size_type)
        {	// deallocate object at _Ptr, ignore size
		    //::operator delete(_Ptr);
            m_refObjectsPool->FreeMem(_Ptr);
        }
        
	    pointer allocate(size_type _Count)
        {	// allocate array of _Count elements
		    //return (_Allocate(_Count, (pointer)0));
            NyxAssert( _Count == 1, "invalid count value");
            return (pointer)m_refObjectsPool->AllocMem(sizeof(_Ty));
        }
        
        pointer allocate(size_type _Count, const void *)
        {	// allocate array of _Count elements, ignore hint
		    //return (allocate(_Count));
            NyxAssert( _Count == 1, "invalid cound value");
            return (pointer)m_refObjectsPool->AllocMem(sizeof(_Ty));
        }
        
	    void construct(pointer _Ptr, const _Ty& _Val)
        {	// construct object at _Ptr with value _Val
            std::_Construct(_Ptr, _Val);
        }
        
	    void destroy(pointer _Ptr)
        {	// destroy object at _Ptr
            std::_Destroy(_Ptr);
        }
        
        size_type max_size() const
        {	// estimate maximum array size
            size_type _Count = (size_type)(-1) / sizeof (_Ty);
		    return (0 < _Count ? _Count : 1);
        }
	}; 
}


#endif // _NYXSTDALLOCATORS_HPP_
