#ifndef _NYXREFCOUNT_IMPL_HPP_
#define _NYXREFCOUNT_IMPL_HPP_


//#include <windows.h>
#include <NyxAtomicValue.hpp>

namespace Nyx
{
	/**
	 *	\brief		Dummy base class for CRefCount_Impl
	 *
	 *	Allow the use of CRefCount_Impl to add ref count even when having no base class
	 *
	 */
	class CRefCount_Impl_DummyBase
	{
	public:
		CRefCount_Impl_DummyBase() {}
		~CRefCount_Impl_DummyBase() {}
	};


	/**
	 *	\brief		Implement refcount mechanism
	 */
	template <class BASE = CRefCount_Impl_DummyBase>
	class CRefCount_Impl : public BASE
	{
	public:
		CRefCount_Impl() :
		BASE()/*,
		m_lRefCount(0L)*/
		{
		}
		
		virtual ~CRefCount_Impl()
		{
		}
		

		void Retain() const
		{
			++ m_lRefCount;
			//::InterlockedIncrement(&m_lRefCount);
		}
		
		void Release() const
		{
			if ( -- m_lRefCount == 0 /*0 == ::InterlockedDecrement(&m_lRefCount)*/ )
			{
				delete this;
			}
		}
		
	private:
	
		//long		m_lRefCount;
		mutable CAtomicValue		m_lRefCount;
		
	};
};


#endif // _NYXREFCOUNT_IMPL_HPP_
