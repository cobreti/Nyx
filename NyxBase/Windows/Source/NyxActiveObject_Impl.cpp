#include "NyxActiveObject_Impl.hpp"
#include "NyxMsg.hpp"
#include "NyxLock.hpp"

#include "NyxTraces.hpp"

#pragma unmanaged

/**
 *
 */
Nyx::CActiveObject* Nyx::CActiveObject::Alloc()
{
	return new NyxWin32::CActiveObject_Impl();
}


/**
 *
 */
NyxWin32::CActiveObject_Impl::CActiveObject_Impl() :
m_bRunning(false),
m_pSentMsg(NULL)
{
	m_refPostMsgInEvent = Nyx::CEvent::Alloc();
	m_refSentMsgHandled = Nyx::CEvent::Alloc();
	m_refMutexSendMsg = Nyx::CMutex::Alloc();
	m_refMsgQueue = Nyx::CMsgQueue::Alloc();
	m_refHandlers = Nyx::CMsgHandlers::Alloc();
	
	m_refMsgQueue->SetHandler( static_cast<Nyx::IMsgQueueEventHandler*>(this) );
}


/**
 *
 */
NyxWin32::CActiveObject_Impl::~CActiveObject_Impl()
{
	Nyx::CTraceStream(0x00) << Nyx::CTF_Text(L"CActiveObject_Impl::~CActiveObject_Impl");
}


/**
 *
 */
void NyxWin32::CActiveObject_Impl::Start()
{	
	if ( !m_refThread.Valid() )
	{
		m_bRunning = true;
		m_refThread = Nyx::CThread::Alloc();
		
		m_refThread->Start( new Nyx::CThreadDelegate<NyxWin32::CActiveObject_Impl>(this,
								&NyxWin32::CActiveObject_Impl::RunningLoop,
								&NyxWin32::CActiveObject_Impl::StopThreadCallback ) );
	}
}


/**
 *
 */
void NyxWin32::CActiveObject_Impl::Stop()
{
	if ( m_refThread.Valid() )
	{
		m_refThread->Stop();
		m_refThread = NULL;
	}
}


/**
 *
 */
Nyx::CMsgHandlers& NyxWin32::CActiveObject_Impl::Handlers()
{
	return *(Nyx::CMsgHandlers*)m_refHandlers;
}


/**
 *
 */
const Nyx::CMsgHandlers& NyxWin32::CActiveObject_Impl::Handlers() const
{
	return *(const Nyx::CMsgHandlers*)m_refHandlers;
}


/**
 *
 */
void NyxWin32::CActiveObject_Impl::Post( Nyx::CMsgBucket& msg )
{
	m_refMsgQueue->Push(msg.m_pMsg);
	msg.m_pMsg = NULL;
}


/**
 *
 */
void NyxWin32::CActiveObject_Impl::Send( const Nyx::CMsg& msg )
{
	Nyx::TLock<Nyx::CMutex>		lock(m_refMutexSendMsg, true);
	
	//IncrementAtomic(&m_MsgCount);
	m_pSentMsg = const_cast<Nyx::CMsg*>(&msg);
	m_refPostMsgInEvent->Signal(0);
	m_refSentMsgHandled->WaitSignaled();
}


/**
 *
 */
void NyxWin32::CActiveObject_Impl::OnMessageReceived()
{
	//IncrementAtomic(&m_MsgCount);
	m_refPostMsgInEvent->Signal(0);
}


/**
 *
 */
void NyxWin32::CActiveObject_Impl::RunningLoop()
{
	Nyx::CMsg*				pMsg = NULL;
	Nyx::CMsgHandlerRef		refMsgHandler;
	
	do
	{
		while ( m_bRunning && (NULL != (pMsg = m_refMsgQueue->Pop())) )
		{
			if ( NULL != m_pSentMsg )
			{
				refMsgHandler = m_refHandlers->Get(m_pSentMsg->Id());
				if ( refMsgHandler.Valid() )
				{
					refMsgHandler->HandleMessage(*m_pSentMsg);
				}
				
				m_pSentMsg = NULL;
				m_refSentMsgHandled->Signal(0);
				//DecrementAtomic(&m_MsgCount);
			}

			refMsgHandler = m_refHandlers->Get(pMsg->Id());
			if ( refMsgHandler.Valid() )
			{
				refMsgHandler->HandleMessage(*pMsg);
			}
			
			delete pMsg;
			pMsg = NULL;
			//DecrementAtomic(&m_MsgCount);
		}		

		if ( NULL != m_pSentMsg )
		{
			refMsgHandler = m_refHandlers->Get(m_pSentMsg->Id());
			if ( refMsgHandler.Valid() )
			{
				refMsgHandler->HandleMessage(*m_pSentMsg);
			}
			
			m_pSentMsg = NULL;
			m_refSentMsgHandled->Signal(0);
			//DecrementAtomic(&m_MsgCount);
		}

		
		if ( m_bRunning /*&& (0 == BitAndAtomic(0xFFFFFFFF, (UInt32*)&m_MsgCount))*/ )
		{
			m_refPostMsgInEvent->WaitSignaled();
		}
	}
	while ( m_bRunning );
}


/**
 *
 */
void NyxWin32::CActiveObject_Impl::StopThreadCallback()
{
	m_bRunning = false;
	m_refPostMsgInEvent->Signal(0);
}

