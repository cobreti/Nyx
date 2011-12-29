#ifndef _NYXMSGQUEUE_IMPL_HPP_
#define _NYXMSGQUEUE_IMPL_HPP_

#include "NyxMsgQueue.hpp"
#include "NyxObject_Impl.hpp"
#include "NyxRef.hpp"
#include "NyxMutex.hpp"

DECLARE_NYXOBJECTREF(CMutex);

namespace NyxLinux
{
	class CMsgBlock;

	/**
	 *
	 */
	class CMsgQueue_Impl : public Nyx::CObject_Impl<Nyx::CMsgQueue>
	{
	public:
		CMsgQueue_Impl();
		virtual ~CMsgQueue_Impl();
		
		virtual void Init();
		virtual void Destroy();
		
	public:
	
		virtual void Push( Nyx::CMsg* const pMsg );
		virtual Nyx::CMsg* Pop();
		virtual void SetHandler( Nyx::IMsgQueueEventHandler* pHandler );
		
	protected:
	
		CMsgBlock* GetFreeBlock();
		void ReleaseBlock( CMsgBlock* pBlock );
		void ClearAllBlocks();

	protected:
	
		CMsgBlock*						m_pHead;
		CMsgBlock*						m_pTail;
		CMsgBlock*						m_pFreeBlocks;
		Nyx::CMutexRef					m_refMutexBlocksAccess;
		Nyx::IMsgQueueEventHandler*		m_pHandler;
	};


	/**
	 *
	 */
	class CMsgBlock
	{
		static size_t		s_BlocksCount;
	public:
		CMsgBlock() : m_pMsg(NULL), m_pLink(NULL) { ++ s_BlocksCount; }
		virtual ~CMsgBlock() { -- s_BlocksCount; }
		
		Nyx::CMsg* Msg() const { return m_pMsg; }
		Nyx::CMsg*& Msg() { return m_pMsg; }
		
		CMsgBlock* Link() const { return m_pLink; }
		CMsgBlock*& Link() { return m_pLink; }
		
	protected:
		Nyx::CMsg*		m_pMsg;
		CMsgBlock*		m_pLink;
	};
}



#endif // _NYXMSGQUEUE_IMPL_HPP_
