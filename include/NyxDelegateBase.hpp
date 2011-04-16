#ifndef _NYXDELEGATEBASE_HPP_
#define _NYXDELEGATEBASE_HPP_

#include "NyxRefCount_Impl.hpp"

namespace Nyx
{
	/**
	 *
	 */
	template <typename PTYPE = void*>
	class CDelegateBase : public Nyx::CRefCount_Impl<>
	{
	protected:

		typedef		PTYPE		ParamType;

	public:
		CDelegateBase() {}
		virtual ~CDelegateBase() {}

		virtual void Invoke(PTYPE param = NULL) {}
	};
}


#endif // _NYXDELEGATEBASE_HPP_
