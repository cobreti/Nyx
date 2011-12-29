#include "NyxMsgQueue_Impl.hpp"
#include "NyxLock.hpp"

size_t NyxLinux::CMsgBlock::s_BlocksCount = 0;

/**
 *
 */
Nyx::CMsgQueue* Nyx::CMsgQueue::Alloc()
{
	NyxLinux::CMsgQueue_Impl* pMsgQueue = new NyxLinux::CMsgQueue_Impl();
	if ( NULL != pMsgQueue )
	{
		pMsgQueue->Init();
	}
	
	return pMsgQueue;
}


/**
 *
 */
NyxLinux::CMsgQueue_Impl::CMsgQueue_Impl() :
	m_pHead(NULL),
	m_pTail(NULL),
	m_pFreeBlocks(NULL),
	m_pHandler(NULL)
{
}


/**
 *
 */
NyxLinux::CMsgQueue_Impl::~CMsgQueue_Impl()
{
	Destroy();
}


/**
 *
 */
void NyxLinux::CMsgQueue_Impl::Init()
{
	m_refMutexBlocksAccess = Nyx::CMutex::Alloc();
}


/**
 *
 */
void NyxLinux::CMsgQueue_Impl::Destroy()
{
	ClearAllBlocks();
	m_refMutexBlocksAccess = NULL;
}


/**
 *
 */
void NyxLinux::CMsgQueue_Impl::Push( Nyx::CMsg* const pMsg )
{
	Nyx::TLock<Nyx::CMutex>		BlocksLock(m_refMutexBlocksAccess, true);

	//m_refMutexBlocksAccess->Lock();

	NyxLinux::CMsgBlock*			pBlock = GetFreeBlock();

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
Nyx::CMsg* NyxLinux::CMsgQueue_Impl::Pop()
{
	Nyx::TLock<Nyx::CMutex>		BlocksLock(m_refMutexBlocksAccess, true);
	
	//m_refMutexBlocksAccess->Lock();
	
	NyxLinux::CMsgBlock*			pBlock = m_pHead;
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
void NyxLinux::CMsgQueue_Impl::SetHandler( Nyx::IMsgQueueEventHandler* pHandler )
{
	m_pHandler = pHandler;
}


/**
 *
 */
NyxLinux::CMsgBlock* NyxLinux::CMsgQueue_Impl::GetFreeBlock()
{
	NyxLinux::CMsgBlock*		pBlock = m_pFreeBlocks;
	
	if ( NULL == pBlock )
	{
		pBlock = new NyxLinux::CMsgBlock();
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
void NyxLinux::CMsgQueue_Impl::ReleaseBlock( CMsgBlock* pBlock )
{
	pBlock->Link() = m_pFreeBlocks;
	m_pFreeBlocks = pBlock;
}


/**
 *
 */
void NyxLinux::CMsgQueue_Impl::ClearAllBlocks()
{
	Nyx::TLock<Nyx::CMutex>		BlocksLock(m_refMutexBlocksAccess, true);
	NyxLinux::CMsgBlock*			pBlock = m_pHead;
	NyxLinux::CMsgBlock*			pTempBlock = NULL;
	
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





