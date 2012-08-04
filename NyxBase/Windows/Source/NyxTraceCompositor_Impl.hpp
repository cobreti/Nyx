#ifndef _NYXTRACECOMPOSITOR_IMPL_HPP_
#define _NYXTRACECOMPOSITOR_IMPL_HPP_

#include "NyxTraceCompositor.hpp"
#include "NyxTraceOutput.hpp"
#include "NyxObject_Impl.hpp"
#include "NyxRef.hpp"
#include "NyxMutex.hpp"
#include "NyxTraceCompositorBuffer.hpp"


namespace NyxWin32
{
	class CTraceCompositor_Impl : public Nyx::CObject_Impl<Nyx::CTraceCompositor>
	{
	public:
		CTraceCompositor_Impl(Nyx::ETraceCompositorCharSet charset, bool bUseAsDefault);
		CTraceCompositor_Impl( Nyx::CMutex* pMutex, Nyx::CTraceCompositorBuffer* pBuffer );
		virtual ~CTraceCompositor_Impl();
		
		virtual void Begin(const Nyx::TraceFilter& filter);
		virtual void End();
		virtual void Write(const Nyx::CTraceFeed& feed);
		virtual CTraceCompositor* Clone();
		virtual void SetOutput(Nyx::CTraceOutput* pOutput);
		virtual void OverrideThreadId(const unsigned int& id, const unsigned int& mid);

		virtual void Write( const wchar_t& c );

	protected:

		/**
		 *
		 */
		class XDummyTraceOutput : public Nyx::CTraceOutput
		{
		public:
			XDummyTraceOutput() {}
			virtual ~XDummyTraceOutput() {}

			virtual void Retain() const {}
			virtual void Release() const {}

			virtual void Write( const Nyx::CTraceHeader& header, const wchar_t* wszText ) {}
			virtual void Write( const Nyx::CTraceHeader& header, const char* szText ) {}
		};

		/**
		 *
		 */
		class XDummyMutex : public Nyx::CObject_Impl<Nyx::CMutex>
		{
		public:
			XDummyMutex() {}
			virtual ~XDummyMutex() {}

			virtual void Lock() {}
			virtual bool AttemptLock() { return true; }
			virtual void Unlock() {}
		};

	protected:

		Nyx::CTraceOutputRef				m_refOutput;
		Nyx::CMutexRef						m_refMutex;
		Nyx::CTraceHeader					m_TraceHeader;

		Nyx::CTraceCompositorBuffer*		m_pCompositorBuffer;

        bool                                m_bUseAsDefault;

		static XDummyTraceOutput	s_DummyTraceOutput;
	};
}


#endif // _NYXTRACECOMPOSITOR_IMPL_HPP_

