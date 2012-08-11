#include "NyxTraceCompositor_Impl.hpp"
#include "NyxTraceFeed.hpp"
#include "NyxModule.hpp"
#include "NyxTraceCompositorBuffer_WideChar.hpp"
#include "NyxTraceCompositorBuffer_Ansi.hpp"

#include <windows.h>
#include <wchar.h>
#include <stdio.h>


NyxWin32::CTraceCompositor_Impl::XDummyTraceOutput NyxWin32::CTraceCompositor_Impl::s_DummyTraceOutput;


/**
 *
 */
Nyx::CTraceCompositorRef Nyx::CTraceCompositor::Alloc(ETraceCompositorCharSet charset, bool bUseAsDefault)
{
	return new NyxWin32::CTraceCompositor_Impl(charset, bUseAsDefault);
}


/**
 *
 */
NyxWin32::CTraceCompositor_Impl::CTraceCompositor_Impl(Nyx::ETraceCompositorCharSet charset, bool bUseAsDefault) :
m_pCompositorBuffer(NULL),
m_bUseAsDefault(bUseAsDefault)
{
	//size_t		Size = 0;

	switch (charset)
	{
		case Nyx::eTCCS_WideChar:
			m_pCompositorBuffer = new Nyx::CTraceCompositorBuffer_WideChar();
			break;
		case Nyx::eTCCS_Ansi:
			m_pCompositorBuffer = new Nyx::CTraceCompositorBuffer_Ansi();
			break;
	};

    m_TraceHeader.ThreadId().Format( "%08X", GetCurrentThreadId() );
	//Size = sprintf_s( m_TraceHeader.ThreadId().GetBuffer(), m_TraceHeader.ThreadId().Size(), "%08X", GetCurrentThreadId());
	//m_TraceHeader.ThreadId().SetLength(Size);

	m_refOutput = &s_DummyTraceOutput;
	m_refMutex = Nyx::CMutex::Alloc();

    if ( m_bUseAsDefault )
	    Nyx::CModule::GetDefault()->Traces().SetThreadDefault(this);
}


/**
 *
 */
NyxWin32::CTraceCompositor_Impl::CTraceCompositor_Impl( Nyx::CMutex* pMutex, Nyx::CTraceCompositorBuffer* pBuffer ) :
m_pCompositorBuffer(pBuffer),
m_bUseAsDefault(true)
{
	//size_t		Size = 0;

    m_TraceHeader.ThreadId().Format( "%08X", GetCurrentThreadId() );
	//Size = sprintf_s( m_TraceHeader.ThreadId().GetBuffer(), m_TraceHeader.ThreadId().Size(), "%08X", GetCurrentThreadId());
	//m_TraceHeader.ThreadId().SetLength(Size);

	m_refOutput = &s_DummyTraceOutput;
	m_refMutex = pMutex;

	Nyx::CModule::GetDefault()->Traces().SetThreadDefault(this);
}


/**
 *
 */
NyxWin32::CTraceCompositor_Impl::~CTraceCompositor_Impl()
{
    if ( m_bUseAsDefault )
	    Nyx::CModule::GetDefault()->Traces().RemoveThreadDefault();

	m_pCompositorBuffer->Release();
}


/**
 *
 */
void NyxWin32::CTraceCompositor_Impl::Begin(const Nyx::TraceFilter& filter)
{
	//size_t		Size = 0;
	m_refMutex->Lock();
    m_TraceHeader.TickCount().Format( "%lu.0", GetTickCount() );
	//Size = sprintf_s( m_TraceHeader.TickCount().GetBuffer(), m_TraceHeader.TickCount().Size(), "%lu.0", GetTickCount() );
	//m_TraceHeader.TickCount().SetLength(Size);
	m_pCompositorBuffer->Begin();
}


/**
 *
 */
void NyxWin32::CTraceCompositor_Impl::End()
{
	m_pCompositorBuffer->End(m_TraceHeader, m_refOutput);
	m_refMutex->Unlock();
}


/**
 *
 */
void NyxWin32::CTraceCompositor_Impl::Write(const Nyx::CTraceFeed& feed)
{
	switch (feed.CharFormat())
	{
		case Nyx::CTraceFeed::eCF_Ansi:
			m_pCompositorBuffer->Write(feed.GetAnsiText());
			break;
		case Nyx::CTraceFeed::eCF_WideChar:
			m_pCompositorBuffer->Write(feed.GetWideCharText());
			break;
	};
}


/**
 *
 */
Nyx::CTraceCompositor* NyxWin32::CTraceCompositor_Impl::Clone()
{
	Nyx::CTraceCompositor* pTraceCompositor = new NyxWin32::CTraceCompositor_Impl( new XDummyMutex(), m_pCompositorBuffer->Clone() );
	pTraceCompositor->SetOutput(m_refOutput);
	return pTraceCompositor;
}


/**
 *
 */
void NyxWin32::CTraceCompositor_Impl::SetOutput(Nyx::CTraceOutput* pOutput)
{
	if ( NULL == pOutput )
		m_refOutput = &s_DummyTraceOutput;
	else
		m_refOutput = pOutput;
}


/**
 *
 */
void NyxWin32::CTraceCompositor_Impl::OverrideThreadId(const unsigned int& id, const unsigned int& mid)
{
	if ( mid == 0 )
		m_TraceHeader.ThreadId().Format( "%08X", id );
	else
		m_TraceHeader.ThreadId().Format( "%08X-%08X", id, mid );
}


/**
 *
 */
void NyxWin32::CTraceCompositor_Impl::Write(const wchar_t& c)
{
	m_pCompositorBuffer->Write(c);
}
