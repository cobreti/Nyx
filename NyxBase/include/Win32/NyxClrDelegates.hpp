#ifndef _NYXCLRDELEGATES_HPP_
#define _NYXCLRDELEGATES_HPP_

#include <NyxTraceStream.hpp>
#include <NyxDelegateBase.hpp>
#include <msclr/gcroot.h>
#include <msclr/auto_gcroot.h>

using namespace msclr;

namespace Nyx
{
	template <class T, typename P = void*>
	ref class CClrDelegateJoint
	{
		delegate void ThreadChangeDelegate( CClrDelegateJoint<T, P>^ param );

	public:
		CClrDelegateJoint( T^ pDelegate ) :
			m_pDelegate(pDelegate),
			m_pRefForm(nullptr),
			m_pRefCtrl(nullptr),
			m_pParam(NULL)
		{
			m_dwThreadId = ::GetCurrentThreadId();
			m_pThreadChangeFct = gcnew ThreadChangeDelegate(this, &CClrDelegateJoint<T, P>::ThreadDelegateFct);
		}

		CClrDelegateJoint( T^ pDelegate, System::Windows::Forms::Form^ pRefForm ) :
			m_pDelegate(pDelegate),
			m_pRefForm(pRefForm),
			m_pRefCtrl(nullptr),
			m_pParam(NULL)
		{
			m_dwThreadId = ::GetCurrentThreadId();
			m_pThreadChangeFct = gcnew ThreadChangeDelegate(this, &CClrDelegateJoint<T, P>::ThreadDelegateFct);
		}

		CClrDelegateJoint( T^ pDelegate, System::Windows::Forms::Control^ pRefCtrl ) :
			m_pDelegate(pDelegate),
			m_pRefForm(nullptr),
			m_pRefCtrl(pRefCtrl),
			m_pParam(NULL)
		{
			m_dwThreadId = ::GetCurrentThreadId();
			m_pThreadChangeFct = gcnew ThreadChangeDelegate(this, &CClrDelegateJoint<T, P>::ThreadDelegateFct);
		}

		~CClrDelegateJoint()
		{
		}

		void Invoke(P param)
		{
			if ( m_pRefForm && m_dwThreadId != ::GetCurrentThreadId() )
			{
				array<Object^>^	ParamArray = { this };
				m_pParam = &param;
				m_pRefForm->Invoke( m_pThreadChangeFct, ParamArray);
			}
			else if ( m_pRefCtrl && m_dwThreadId != ::GetCurrentThreadId() )
			{
				array<Object^>^	ParamArray = { this };
				m_pParam = &param;
				m_pRefCtrl->Invoke( m_pThreadChangeFct, ParamArray);
			}
			else
				m_pDelegate->Invoke(param);
		}

	protected:

		void ThreadDelegateFct( CClrDelegateJoint<T, P>^ param )
		{
			m_pDelegate->Invoke(*m_pParam);
		}

	protected:
		T^									m_pDelegate;
		System::Windows::Forms::Form^		m_pRefForm;
		System::Windows::Forms::Control^	m_pRefCtrl;
		ThreadChangeDelegate^				m_pThreadChangeFct;
		DWORD								m_dwThreadId;
		P*									m_pParam;
	};


	/**
	 *	\brief		C++ to C++/CLI delegate
	 *
	 *	Restriction : at least one parameter must be present in delegate, default = void*
	 *
	 */
	template <class T, typename P = void*>
	class CClrDelegate : public Nyx::CDelegateBase<P>
	{
	public:
		CClrDelegate( T^ pDelegate )
		{
			m_pDelegateJoint = gcnew CClrDelegateJoint<T, P>(pDelegate);
		}

		CClrDelegate( T^ pDelegate, System::Windows::Forms::Form^ pRefForm )
		{
			m_pDelegateJoint = gcnew CClrDelegateJoint<T, P>(pDelegate, pRefForm);
		 }

		CClrDelegate( T^ pDelegate, System::Windows::Forms::Control^ pRefCtrl )
		{
			m_pDelegateJoint = gcnew CClrDelegateJoint<T, P>(pDelegate, pRefCtrl);
		}

		virtual ~CClrDelegate()
		{
		}

		virtual void Invoke(P param = NULL)
		{
			m_pDelegateJoint->Invoke(param);
		}

	protected:

		auto_gcroot<CClrDelegateJoint<T, P>^>			m_pDelegateJoint;
	};


}

#endif // _NYXCLRDELEGATES_HPP_
