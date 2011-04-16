#ifndef _NYXOBJECT_IMPL_HPP_
#define _NYXOBJECT_IMPL_HPP_

#include "NyxRefCount_Impl.hpp"

namespace Nyx
{
	template <class BASE>
	class CObject_Impl : public Nyx::CRefCount_Impl<BASE>
	{
	public:
		CObject_Impl() : Nyx::CRefCount_Impl<BASE>() {}
		virtual ~CObject_Impl() {}
	};
}



#endif // _NYXOBJECT_IMPL_HPP_
