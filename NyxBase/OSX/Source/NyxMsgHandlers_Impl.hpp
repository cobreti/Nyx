#ifndef _NYXMSGHANDLERS_IMPL_HPP_
#define _NYXMSGHANDLERS_IMPL_HPP_

#include "NyxMsgHandlers.hpp"
#include "NyxMsgHandler.hpp"
#include "NyxRef.hpp"
#include "NyxObject_Impl.hpp"

#include <map>

DECLARE_NYXOBJECTREF(CMsgHandler)

namespace NyxOSX
{
	class CMsgHandlers_Impl : public Nyx::CObject_Impl<Nyx::CMsgHandlers>
	{
	public:
		CMsgHandlers_Impl();
		virtual ~CMsgHandlers_Impl();
		
	public: // CMsgHandlers methods

		virtual Nyx::NyxResult Add( const Nyx::MsgIdentifier& MsgId, Nyx::CMsgHandler* pHandler );
		virtual Nyx::CMsgHandlerRef Get( const Nyx::MsgIdentifier& MsgId );
		virtual Nyx::NyxResult Remove( const Nyx::MsgIdentifier& MsgId );
		
	protected: // protected types
	
		typedef std::map<Nyx::MsgIdentifier, Nyx::CMsgHandlerRef>		THandlersTable;
		
	protected: // protected members
	
		THandlersTable		m_Handlers;

	};
}

#endif // _NYXMSGHANDLERS_IMPL_HPP_

