#ifndef _NYXACTIVEOBJECT_IMPL_HPP_
#define _NYXACTIVEOBJECT_IMPL_HPP_


#include "NyxObject_Impl.hpp"
#include "NyxActiveObject.hpp"
#include "NyxMsgQueue.hpp"
#include "NyxMsgHandlers.hpp"
#include "NyxThread.hpp"
#include "NyxEvent.hpp"
#include "NyxMutex.hpp"
#include "NyxRef.hpp"


DECLARE_NYXOBJECTREF(CMsgQueue);
DECLARE_NYXOBJECTREF(CThread);
DECLARE_NYXOBJECTREF(CEvent);
DECLARE_NYXOBJECTREF(CMutex);
DECLARE_NYXOBJECTREF(CMsgHandlers);


namespace NyxLinux
{
	/**
	 *	\brief		Active object implementation
	 */
	class CActiveObject_Impl : public Nyx::CObject_Impl<Nyx::CActiveObject>,
								public Nyx::IMsgQueueEventHandler
	{
		friend class CActiveObjectThreadProc;
	
	public:
		CActiveObject_Impl();
		virtual ~CActiveObject_Impl();
		
	public:	// CActiveObject methods

		virtual void Start();
		virtual void Stop();
		virtual Nyx::CMsgHandlers& Handlers();
		virtual const Nyx::CMsgHandlers& Handlers() const;
		virtual void Post( Nyx::CMsgBucket& msg );
		virtual void Send( const Nyx::CMsg& msg );
		
	public: // IMsgQueueEventHandler methods
	
		virtual void OnMessageReceived();
		
	protected: // protected methods
	
		virtual void RunningLoop();
		virtual void StopThreadCallback();
		
	protected: // protected members
	
		long					m_MsgCount;
		Nyx::CMsgQueueRef		m_refMsgQueue;
		Nyx::CThreadRef			m_refThread;
		Nyx::CEventRef			m_refPostMsgInEvent;
		Nyx::CEventRef			m_refSentMsgHandled;
		Nyx::CMutexRef			m_refMutexSendMsg;
		Nyx::CMsgHandlersRef	m_refHandlers;
		bool					m_bRunning;
		Nyx::CMsg*				m_pSentMsg;
	};
	
	
	/**
	 *	\brief		Active object thread proc
	 */
	class CActiveObjectThreadProc : public Nyx::CObject_Impl<Nyx::CThreadProc>
	{
	public:	// public methods
		CActiveObjectThreadProc( NyxLinux::CActiveObject_Impl& rActiveObject );
		virtual ~CActiveObjectThreadProc();
		
		virtual void Run();
		virtual void Stop();		
	
	protected: // protected members
	
		NyxLinux::CActiveObject_Impl&		m_rActiveObject;
	};
}



#endif // _NYXACTIVEOBJECT_IMPL_HPP_


