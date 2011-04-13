#ifndef _NYXTHREAD_HPP_
#define _NYXTHREAD_HPP_

#include "NyxThreadProc.hpp"
#include "NyxObject_Impl.hpp"
#include "NyxRef.hpp"

DECLARE_NYXOBJECTREF(CThread)

namespace Nyx
{

	/**
	 *
	 */
	class CThread : public Nyx::CObject
	{
	public:
		static CThreadRef Alloc();
		
	public:
	
		virtual NyxResult Start(Nyx::CThreadProc* pTProc) = 0;
		virtual void Stop() = 0;
		virtual bool IsRunning() const = 0;
		virtual void SetThreadUserData(void* pData) = 0;
		virtual void* GetThreadUserData() = 0;
	};



	/**
	 *
	 */
	template <class C>
	class CThreadDelegate : public Nyx::CObject_Impl<Nyx::CThreadProc>
	{
	public:
	
		typedef void (C::*PFCTProc) ();
	
	public:
		CThreadDelegate(C* pThis, PFCTProc pfctRunProc, PFCTProc pfctStopProc) :
		m_refThis(pThis),
		m_pRunProc(pfctRunProc),
		m_pStopProc(pfctStopProc)
		{
		}		

		virtual ~CThreadDelegate()
		{
		}
		
		virtual void Run()
		{
			if ( (NULL != m_pRunProc) && (m_refThis.Valid()) )
			{
				(m_refThis->*m_pRunProc)();
			}
		}
		
		virtual void Stop()
		{
			if ( (NULL != m_pStopProc) && (m_refThis.Valid()) )
			{
				(m_refThis->*m_pStopProc)();
			}
		}
		
	
	private:

		Nyx::CRef<C>	m_refThis;
		PFCTProc		m_pRunProc;
		PFCTProc		m_pStopProc;
	};
	

	/**
	 *
	 */
	template <class C>
	class CThreadDelegateNoRef : public Nyx::CObject_Impl<Nyx::CThreadProc>
	{
	public:
	
		typedef void (C::*PFCTProc) ();
	
	public:
		CThreadDelegateNoRef(C* pThis, PFCTProc pfctRunProc, PFCTProc pfctStopProc) :
		m_pThis(pThis),
		m_pRunProc(pfctRunProc),
		m_pStopProc(pfctStopProc)
		{
		}		

		virtual ~CThreadDelegateNoRef()
		{
		}
		
		virtual void Run()
		{
			if ( (NULL != m_pRunProc) && (m_pThis != NULL) )
			{
				(m_pThis->*m_pRunProc)();
			}
		}
		
		virtual void Stop()
		{
			if ( (NULL != m_pStopProc) && (m_pThis != NULL) )
			{
				(m_pThis->*m_pStopProc)();
			}
		}
		
	
	private:

		C*				m_pThis;
		PFCTProc		m_pRunProc;
		PFCTProc		m_pStopProc;
	};
};


#endif // _NYXTHREAD_HPP_
