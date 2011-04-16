#ifndef _NYXMSGHANDLERS_HPP_
#define _NYXMSGHANDLERS_HPP_

#include "NyxObject.hpp"
#include "NyxMsgHandler.hpp"
#include "NyxRef.hpp"

DECLARE_NYXOBJECTREF(CMsgHandler)

namespace Nyx
{
	class CMsgHandler;
	
	class CMsgHandlers : public Nyx::CObject
	{
	public:
	
		static CMsgHandlers* Alloc();
		
	public:

		virtual Nyx::NyxResult Add( const Nyx::MsgIdentifier& MsgId, Nyx::CMsgHandler* pHandler ) = 0;
		virtual Nyx::CMsgHandlerRef Get( const Nyx::MsgIdentifier& MsgId ) = 0;
		virtual Nyx::NyxResult Remove( const Nyx::MsgIdentifier& MsgId ) = 0;
	};
}


#endif // _NYXMSGHANDLERS_HPP_

