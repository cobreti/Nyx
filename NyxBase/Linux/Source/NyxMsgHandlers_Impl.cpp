#include "NyxMsgHandlers_Impl.hpp"


/**
 *
 */
Nyx::CMsgHandlers* Nyx::CMsgHandlers::Alloc()
{
	return new NyxLinux::CMsgHandlers_Impl();
}


/**
 *
 */
NyxLinux::CMsgHandlers_Impl::CMsgHandlers_Impl()
{
}


/**
 *
 */
NyxLinux::CMsgHandlers_Impl::~CMsgHandlers_Impl()
{
}


/**
 *
 */
Nyx::NyxResult NyxLinux::CMsgHandlers_Impl::Add( const Nyx::MsgIdentifier& MsgId, Nyx::CMsgHandler* pHandler )
{
	Nyx::NyxResult		res = Nyx::kNyxRes_Success;
	
	m_Handlers.insert( std::make_pair(MsgId, pHandler) );
	
	return res;
}


/**
 *
 */
Nyx::CMsgHandlerRef NyxLinux::CMsgHandlers_Impl::Get( const Nyx::MsgIdentifier& MsgId )
{	
	return m_Handlers[MsgId];
}


/**
 *
 */
Nyx::NyxResult NyxLinux::CMsgHandlers_Impl::Remove( const Nyx::MsgIdentifier& MsgId )
{
	Nyx::NyxResult		res = Nyx::kNyxRes_Success;
	
	m_Handlers.erase(MsgId);
	
	return res;
}

