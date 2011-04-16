#include "NyxMsgHandlers_Impl.hpp"


/**
 *
 */
Nyx::CMsgHandlers* Nyx::CMsgHandlers::Alloc()
{
	return new NyxOSX::CMsgHandlers_Impl();
}


/**
 *
 */
NyxOSX::CMsgHandlers_Impl::CMsgHandlers_Impl()
{
}


/**
 *
 */
NyxOSX::CMsgHandlers_Impl::~CMsgHandlers_Impl()
{
}


/**
 *
 */
Nyx::NyxResult NyxOSX::CMsgHandlers_Impl::Add( const Nyx::MsgIdentifier& MsgId, Nyx::CMsgHandler* pHandler )
{
	Nyx::NyxResult		res = Nyx::kNyxRes_Success;
	
	m_Handlers.insert( std::make_pair(MsgId, pHandler) );
	
	return res;
}


/**
 *
 */
Nyx::CMsgHandlerRef NyxOSX::CMsgHandlers_Impl::Get( const Nyx::MsgIdentifier& MsgId )
{	
	return m_Handlers[MsgId];
}


/**
 *
 */
Nyx::NyxResult NyxOSX::CMsgHandlers_Impl::Remove( const Nyx::MsgIdentifier& MsgId )
{
	Nyx::NyxResult		res = Nyx::kNyxRes_Success;
	
	m_Handlers.erase(MsgId);
	
	return res;
}

