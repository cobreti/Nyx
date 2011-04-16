#ifndef _NYXOBJECT_HPP_
#define _NYXOBJECT_HPP_

#include "NyxDefs.hpp"
#include "NyxTypes.hpp"

namespace Nyx
{
	class CObject
	{
	public:
	
		/**
		 *	\brief		Retain the object
		 */
		virtual void Retain() const = 0;
		
		
		/**
		 *	\brief		Releases the object
		 */
		virtual void Release() const = 0;
		
		
	protected:
	
		CObject() {};
		virtual ~CObject() {};
		
	};
};


#endif // _NYXOBJECT_HPP_
