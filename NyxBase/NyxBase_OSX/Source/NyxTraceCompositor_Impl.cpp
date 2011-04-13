#include "NyxTraceCompositor_Impl.hpp"
#include "NyxTraceFeed.hpp"
#include "NyxModule.hpp"
#include "NyxTraceCompositorBuffer_WideChar.hpp"
#include "NyxTraceCompositorBuffer_Ansi.hpp"

#include <wchar.h>
#include <pthread.h>
#include <sys/time.h>


NyxOSX::CTraceCompositor_Impl::XDummyTraceOutput NyxOSX::CTraceCompositor_Impl::s_DummyTraceOutput;

/**
 *
 */
Nyx::CTraceCompositorRef Nyx::CTraceCompositor::Alloc(ETraceCompositorCharSet charset)
{
	return new NyxOSX::CTraceCompositor_Impl(charset);
}


/**
 *
 */
NyxOSX::CTraceCompositor_Impl::CTraceCompositor_Impl(Nyx::ETraceCompositorCharSet charset) : m_pCompositorBuffer(NULL)
{
	size_t		Size = 0;

	
	switch (charset)
	{
		case Nyx::eTCCS_WideChar:
			m_pCompositorBuffer = new Nyx::CTraceCompositorBuffer_WideChar();
			break;
		case Nyx::eTCCS_Ansi:
			m_pCompositorBuffer = new Nyx::CTraceCompositorBuffer_Ansi();
			break;
	};

//	m_pBuffer = new wchar_t[kBufferSize];
//	m_pStartBufferPos = m_pCurPos = m_pBuffer;
	
	Size = sprintf( m_TraceHeader.ThreadId(), "%08lX", (unsigned long)(void*)pthread_self());
	m_TraceHeader.ThreadId().SetLength(Size);
	
	//m_pStartBufferPos = m_pBuffer + swprintf(m_pBuffer, kBufferSize, L" [%8X] ", (void*)pthread_self());
	
	m_refOutput = &s_DummyTraceOutput;
	m_refMutex = Nyx::CMutex::Alloc();
	
	Nyx::CModule::GetDefault()->Traces().SetThreadDefault(this);
}


/**
 *
 */
NyxOSX::CTraceCompositor_Impl::CTraceCompositor_Impl( Nyx::CMutex* pMutex, Nyx::CTraceCompositorBuffer* pBuffer ) :
m_pCompositorBuffer(pBuffer)
{
	size_t		Size = 0;

//	m_pBuffer = new wchar_t[kBufferSize];
//	m_pStartBufferPos = m_pCurPos = m_pBuffer;
	
	Size = sprintf( m_TraceHeader.ThreadId(), "%08lX", (unsigned long)(void*)pthread_self());
	m_TraceHeader.ThreadId().SetLength(Size);
	
	//m_pStartBufferPos = m_pBuffer + swprintf(m_pBuffer, kBufferSize, L" [%8X] ", (void*)pthread_self());
	
	m_refOutput = &s_DummyTraceOutput;
	m_refMutex = pMutex;
	
	Nyx::CModule::GetDefault()->Traces().SetThreadDefault(this);
}


/**
 *
 */
NyxOSX::CTraceCompositor_Impl::~CTraceCompositor_Impl()
{
	Nyx::CModule::GetDefault()->Traces().RemoveThreadDefault();
	
	delete m_pCompositorBuffer;
}


/**
 *
 */
void NyxOSX::CTraceCompositor_Impl::Begin(const Nyx::TraceFilter& filter)
{	
	size_t		Size = 0;
	timeval		t;
	
	m_refMutex->Lock();
	
	gettimeofday(&t, NULL);
	Size = sprintf( m_TraceHeader.TickCount(), "%lu%lu", (unsigned long)t.tv_sec, (unsigned long)t.tv_usec);
	m_TraceHeader.TickCount().SetLength(Size);

	m_pCompositorBuffer->Begin();
	
//	m_pCurPos = m_pStartBufferPos;
}


/**
 *
 */
void NyxOSX::CTraceCompositor_Impl::End()
{
	m_pCompositorBuffer->End(m_TraceHeader, m_refOutput);
	m_refMutex->Unlock();
}


/**
 *
 */
void NyxOSX::CTraceCompositor_Impl::Write(const Nyx::CTraceFeed& feed)
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
Nyx::CTraceCompositor* NyxOSX::CTraceCompositor_Impl::Clone()
{
	Nyx::CTraceCompositor*		pTraceCompositor = new NyxOSX::CTraceCompositor_Impl( new XDummyMutex(), m_pCompositorBuffer->Clone() );
	
	pTraceCompositor->SetOutput(m_refOutput);
	
	return pTraceCompositor;
}


/**
 *
 */
void NyxOSX::CTraceCompositor_Impl::SetOutput( Nyx::CTraceOutput* pOutput )
{
	m_refOutput = pOutput;
}


/**
 *
 */
void NyxOSX::CTraceCompositor_Impl::Write(const wchar_t& c)
{
	m_pCompositorBuffer->Write(c);
}

