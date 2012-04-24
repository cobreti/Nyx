#ifndef __NYXACTIVEOBJECT_HPP_
#define __NYXACTIVEOBJECT_HPP_

#include "NyxObject.hpp"
#include "NyxMsgHandlers.hpp"
#include "NyxMsgBucket.hpp"

DECLARE_NYXOBJECTREF(CActiveObject)

namespace Nyx
{
	class CMsgHandlers;

	class CActiveObject : public Nyx::CObject
	{
	public:
		static CActiveObject* Alloc();
		
	public:
	
		virtual void Start() = 0;
		virtual void Stop() = 0;
		virtual CMsgHandlers& Handlers() = 0;
		virtual const CMsgHandlers& Handlers() const = 0;
		virtual void Post( Nyx::CMsgBucket& msg ) = 0;
		virtual void Send( const Nyx::CMsg& msg ) = 0;
	};
}



#endif // __NYXACTIVEOBJECT_HPP_


