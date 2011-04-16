#include "NyxMsgQueue_Impl.hpp"
#include "NyxLock.hpp"

size_t NyxOSX::CMsgBlock::s_BlocksCount = 0;

/**
 *
 */
Nyx::CMsgQueue* Nyx::CMsgQueue::Alloc()
{
	NyxOSX::CMsgQueue_Impl* pMsgQueue = new NyxOSX::CMsgQueue_Impl();
	if ( NULL != pMsgQueue )
	{
		pMsgQueue->Init();
	}
	
	return pMsgQueue;
}


/**
 *
 */
NyxOSX::CMsgQueue_Impl::CMsgQueue_Impl() :
	m_pHead(NULL),
	m_pTail(NULL),
	m_pFreeBlocks(NULL),
	m_pHandler(NULL)
{
}


/**
 *
 */
NyxOSX::CMsgQueue_Impl::~CMsgQueue_Impl()
{
	Destroy();
}


/**
 *
 */
void NyxOSX::CMsgQueue_Impl::Init()
{
	m_refMutexBlocksAccess = Nyx::CMutex::Alloc();
}


/**
 *
 */
void NyxOSX::CMsgQueue_Impl::Destroy()
{
	ClearAllBlocks();
	m_refMutexBlocksAccess = NULL;
}


/**
 *
 */
void NyxOSX::CMsgQueue_Impl::Push( Nyx::CMsg* const pMsg )
{
	Nyx::TLock<Nyx::CMutex>		BlocksLock(m_refMutexBlocksAccess, true);

	//m_refMutexBlocksAccess->Lock();

	NyxOSX::CMsgBlock*			pBlock = GetFreeBlock();

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
Nyx::CMsg* NyxOSX::CMsgQueue_Impl::Pop()
{
	Nyx::TLock<Nyx::CMutex>		BlocksLock(m_refMutexBlocksAccess, true);
	
	//m_refMutexBlocksAccess->Lock();
	
	NyxOSX::CMsgBlock*			pBlock = m_pHead;
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
void NyxOSX::CMsgQueue_Impl::SetHandler( Nyx::IMsgQueueEventHandler* pHandler )
{
	m_pHandler = pHandler;
}


/**
 *
 */
NyxOSX::CMsgBlock* NyxOSX::CMsgQueue_Impl::GetFreeBlock()
{
	NyxOSX::CMsgBlock*		pBlock = m_pFreeBlocks;
	
	if ( NULL == pBlock )
	{
		pBlock = new NyxOSX::CMsgBlock();
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
void NyxOSX::CMsgQueue_Impl::ReleaseBlock( CMsgBlock* pBlock )
{
	pBlock->Link() = m_pFreeBlocks;
	m_pFreeBlocks = pBlock;
}


/**
 *
 */
void NyxOSX::CMsgQueue_Impl::ClearAllBlocks()
{
	Nyx::TLock<Nyx::CMutex>		BlocksLock(m_refMutexBlocksAccess, true);
	NyxOSX::CMsgBlock*			pBlock = m_pHead;
	NyxOSX::CMsgBlock*			pTempBlock = NULL;
	
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





