#include "NyxMsgQueue_Impl.hpp"
#include "NyxLock.hpp"

size_t NyxWin32::CMsgBlock::s_BlocksCount = 0;

/**
 *
 */
Nyx::CMsgQueue* Nyx::CMsgQueue::Alloc()
{
	NyxWin32::CMsgQueue_Impl* pMsgQueue = new NyxWin32::CMsgQueue_Impl();
	if ( NULL != pMsgQueue )
	{
		pMsgQueue->Init();
	}
	
	return pMsgQueue;
}


/**
 *
 */
NyxWin32::CMsgQueue_Impl::CMsgQueue_Impl() :
	m_pHead(NULL),
	m_pTail(NULL),
	m_pFreeBlocks(NULL),
	m_pHandler(NULL)
{
}


/**
 *
 */
NyxWin32::CMsgQueue_Impl::~CMsgQueue_Impl()
{
	Destroy();
}


/**
 *
 */
void NyxWin32::CMsgQueue_Impl::Init()
{
	m_refMutexBlocksAccess = Nyx::CMutex::Alloc();
}


/**
 *
 */
void NyxWin32::CMsgQueue_Impl::Destroy()
{
	ClearAllBlocks();
	m_refMutexBlocksAccess = NULL;
}


/**
 *
 */
void NyxWin32::CMsgQueue_Impl::Push( Nyx::CMsg* const pMsg )
{
	Nyx::TLock<Nyx::CMutex>		BlocksLock(m_refMutexBlocksAccess, true);

	//m_refMutexBlocksAccess->Lock();

	NyxWin32::CMsgBlock*			pBlock = GetFreeBlock();

	pBlock->Msg() = pMsg;

	if ( NULL == m_pTail )
	{
		m_pHead = pBlock;		
	}
	else
	{
		m_pTail->Link() = pBlock;
	}

	if ( NULL != m_pHandler )
	{
		m_pHandler->OnMessageReceived();
	}
	
	m_pTail = pBlock;

	//m_refMutexBlocksAccess->Unlock();
}


/**
 *
 */
Nyx::CMsg* NyxWin32::CMsgQueue_Impl::Pop()
{
	Nyx::TLock<Nyx::CMutex>		BlocksLock(m_refMutexBlocksAccess, true);
	
	//m_refMutexBlocksAccess->Lock();
	
	NyxWin32::CMsgBlock*			pBlock = m_pHead;
	Nyx::CMsg*					pMsg = NULL;
	
	if ( NULL == pBlock )
		return NULL;
	
	m_pHead = pBlock->Link();
	if ( NULL == m_pHead )
	{
		m_pTail = NULL;
	}

	pMsg = pBlock->Msg();
	ReleaseBlock(pBlock);

	//m_refMutexBlocksAccess->Unlock();

	return pMsg;
}


/**
 *
 */
void NyxWin32::CMsgQueue_Impl::SetHandler( Nyx::IMsgQueueEventHandler* pHandler )
{
	m_pHandler = pHandler;
}


/**
 *
 */
NyxWin32::CMsgBlock* NyxWin32::CMsgQueue_Impl::GetFreeBlock()
{
	NyxWin32::CMsgBlock*		pBlock = m_pFreeBlocks;
	
	if ( NULL == pBlock )
	{
		pBlock = new NyxWin32::CMsgBlock();
	}
	else
	{
		m_pFreeBlocks = pBlock->Link();
		pBlock->Link() = NULL;
	}
	
	return pBlock;
}


/**
 *
 */
void NyxWin32::CMsgQueue_Impl::ReleaseBlock( CMsgBlock* pBlock )
{
	pBlock->Link() = m_pFreeBlocks;
	m_pFreeBlocks = pBlock;
}


/**
 *
 */
void NyxWin32::CMsgQueue_Impl::ClearAllBlocks()
{
	Nyx::TLock<Nyx::CMutex>		BlocksLock(m_refMutexBlocksAccess, true);
	NyxWin32::CMsgBlock*			pBlock = m_pHead;
	NyxWin32::CMsgBlock*			pTempBlock = NULL;
	
	while ( NULL != pBlock )
	{
		pTempBlock = pBlock;
		pBlock = pBlock->Link();
		
		delete pTempBlock;
	}
	
	pBlock = m_pFreeBlocks;
	while ( NULL != pBlock )
	{
		pTempBlock = pBlock;
		pBlock = pBlock->Link();
		
		delete pTempBlock;
	}
	
	m_pHead = NULL;
	m_pTail = NULL;
	m_pFreeBlocks = NULL;
}





