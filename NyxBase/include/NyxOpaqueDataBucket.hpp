#ifndef _NYXOPAQUEDATABUCKET_HPP_
#define _NYXOPAQUEDATABUCKET_HPP_

#include "NyxRefCount_Impl.hpp"
#include "NyxRef.hpp"

DECLARE_NYXOBJECTREF(COpaqueDataBucket)

namespace Nyx
{
	/**
	 *
	 */
	class COpaqueDataBucket : public Nyx::CRefCount_Impl<>
	{
	public:
		COpaqueDataBucket();
		virtual ~COpaqueDataBucket();
	};
	
	
	/**
	 *
	 */
	template <class T>
	class TOpaqueDataBucket : public COpaqueDataBucket
	{
	public:
		TOpaqueDataBucket(const T& data) : COpaqueDataBucket(), m_Data(data) {}
		virtual ~TOpaqueDataBucket() {}
		
		const T& Data() const		{ return m_Data; }
		T& Data()					{ return m_Data; }
		
	protected:
	
		T		m_Data;
	};
}



#endif // _NYXOPAQUEDATABUCKET_HPP_
