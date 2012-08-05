#ifndef _NYXTRACESYSTEM_IMPL_HPP_
#define _NYXTRACESYSTEM_IMPL_HPP_

#include "NyxTraceCompositor.hpp"
#include "NyxTraceOutput.hpp"
#include "NyxObject_Impl.hpp"
#include "NyxTraceHeader.hpp"
#include "NyxLock.hpp"
#include "NyxMutex.hpp"
#include "NyxTraceCompositorBuffer.hpp"

namespace NyxOSX
{
	class CTraceCompositor_Impl : public Nyx::CObject_Impl<Nyx::CTraceCompositor>
	{
	public:
		CTraceCompositor_Impl(Nyx::ETraceCompositorCharSet charset, bool bUseAsDefault = true);
		CTraceCompositor_Impl( Nyx::CMutex* pMutex, Nyx::CTraceCompositorBuffer* pBuffer, bool bUseAsDefault = true );
		virtual ~CTraceCompositor_Impl();
		
		virtual void Begin(const Nyx::TraceFilter& filter);
		virtual void End();
		virtual void Write(const Nyx::CTraceFeed& feed);
		virtual CTraceCompositor* Clone();
		virtual void SetOutput( Nyx::CTraceOutput* pOutput );
        virtual void OverrideThreadId(const unsigned int& id, const unsigned int& mid);
		
		virtual void Write( const wchar_t& c );
		
		bool UsedAsDefault() const	{ return m_bUseAsDefault; }
		
	protected: // protected types
	
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
		
	protected: // protected members

		Nyx::CTraceHeader					m_TraceHeader;
		Nyx::CMutexRef						m_refMutex;
		Nyx::CTraceOutputRef				m_refOutput;
		Nyx::CTraceCompositorBuffer*		m_pCompositorBuffer;
		bool								m_bUseAsDefault;
		
		static XDummyTraceOutput			s_DummyTraceOutput;
	};
}


#endif // _NYXTRACE_IMPL_HPP_

