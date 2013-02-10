#include "NyxActiveObject_Impl.hpp"
#include "NyxMsg.hpp"
#include "NyxLock.hpp"

#include "NyxTraces.hpp"

#include <sys/syscall.h>

/**
 *
 */
Nyx::CActiveObject* Nyx::CActiveObject::Alloc()
{
	return new NyxLinux::CActiveObject_Impl();
}


/**
 *
 */
NyxLinux::CActiveObject_Impl::CActiveObject_Impl() :
m_MsgCount(0),
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
NyxLinux::CActiveObject_Impl::~CActiveObject_Impl()
{
	if ( m_bRunning )
	{
		m_refThread->Stop();
	}

	Nyx::CTraceStream(0x00) << Nyx::CTF_Text(L"CActiveObject_Impl::~CActiveObject_Impl");
}


/**
 *
 */
void NyxLinux::CActiveObject_Impl::Start()
{	
	if ( !m_refThread.Valid() )
	{
		m_bRunning = true;
		m_refThread = Nyx::CThread::Alloc();
		
		m_refThread->Start( new NyxLinux::CActiveObjectThreadProc(*this) );
		
		/*m_refThread->Start( new Nyx::CThreadDelegate<NyxLinux::CActiveObject_Impl>(this,
								&NyxLinux::CActiveObject_Impl::RunningLoop,
								&NyxLinux::CActiveObject_Impl::StopThreadCallback ) );*/
	}
}


/**
 *
 */
void NyxLinux::CActiveObject_Impl::Stop()
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
Nyx::CMsgHandlers& NyxLinux::CActiveObject_Impl::Handlers()
{
	return *(Nyx::CMsgHandlers*)m_refHandlers;
}


/**
 *
 */
const Nyx::CMsgHandlers& NyxLinux::CActiveObject_Impl::Handlers() const
{
	return *(const Nyx::CMsgHandlers*)m_refHandlers;
}


/**
 *
 */
void NyxLinux::CActiveObject_Impl::Post( Nyx::CMsgBucket& msg )
{
	m_refMsgQueue->Push(msg.m_pMsg);
	msg.m_pMsg = NULL;
}


/**
 *
 */
void NyxLinux::CActiveObject_Impl::Send( const Nyx::CMsg& msg )
{
	Nyx::TLock<Nyx::CMutex>		lock(m_refMutexSendMsg, true);
	
	__sync_fetch_and_add(&m_MsgCount, 1);
	m_pSentMsg = const_cast<Nyx::CMsg*>(&msg);
	m_refPostMsgInEvent->Signal(0);

	while ( m_pSentMsg == const_cast<Nyx::CMsg*>(&msg) )
		m_refSentMsgHandled->WaitSignaled(10);
}


/**
 *
 */
void NyxLinux::CActiveObject_Impl::OnMessageReceived()
{
	__sync_fetch_and_add(&m_MsgCount, 1);
	m_refPostMsgInEvent->Signal(0);
}


/**
 *
 */
void NyxLinux::CActiveObject_Impl::RunningLoop()
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
				__sync_fetch_and_sub(&m_MsgCount, 1);
			}

			refMsgHandler = m_refHandlers->Get(pMsg->Id());
			if ( refMsgHandler.Valid() )
			{
				refMsgHandler->HandleMessage(*pMsg);
			}
			
			delete pMsg;
			pMsg = NULL;
			__sync_fetch_and_sub(&m_MsgCount, 1);
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
			__sync_fetch_and_sub(&m_MsgCount, 1);
		}

		
		if ( m_bRunning && (0 == __sync_fetch_and_and((Nyx::UInt32*)&m_MsgCount, 0xFFFFFFFF)) )
		{
			m_refPostMsgInEvent->WaitSignaled();
		}
	}
	while ( m_bRunning );
}


/**
 *
 */
void NyxLinux::CActiveObject_Impl::StopThreadCallback()
{
	m_bRunning = false;
	m_refPostMsgInEvent->Signal(0);
}


/**
 *
 *	CActiveObjectThreadProc methods
 *
 */


/**
 *
 */ 
NyxLinux::CActiveObjectThreadProc::CActiveObjectThreadProc( NyxLinux::CActiveObject_Impl& rActiveObject ) :
	m_rActiveObject(rActiveObject)
{
}


/**
 *
 */
NyxLinux::CActiveObjectThreadProc::~CActiveObjectThreadProc()
{
}


/**
 *
 */
void NyxLinux::CActiveObjectThreadProc::Run()
{
	m_rActiveObject.RunningLoop();
}


/**
 *
 */
void NyxLinux::CActiveObjectThreadProc::Stop()
{
	m_rActiveObject.StopThreadCallback();
}

