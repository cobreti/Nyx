#include "NyxTraceCompositorBuffer_Ansi.hpp"
#include "NyxTraceFeed.hpp"
#include "NyxTraceHeader.hpp"

/**
 *
 */
Nyx::CTraceCompositorBuffer_Ansi::CTraceCompositorBuffer_Ansi() :
m_pBuffer(NULL),
m_pCurPos(NULL),
m_pStartBufferPos(NULL)
{
	m_pBuffer = new char[kBufferSize];
	m_pCurPos = m_pBuffer;
	m_pStartBufferPos = m_pBuffer;
}


/**
 *
 */
Nyx::CTraceCompositorBuffer_Ansi::~CTraceCompositorBuffer_Ansi()
{
	delete[] m_pBuffer;
}


/**
 *
 */
void Nyx::CTraceCompositorBuffer_Ansi::Release()
{
    delete this;
}

/**
 *
 */
void Nyx::CTraceCompositorBuffer_Ansi::Begin()
{
	m_pCurPos = m_pStartBufferPos;
}


/**
 *
 */
void Nyx::CTraceCompositorBuffer_Ansi::Write(const wchar_t* wszText)
{
	for (const wchar_t* p = wszText; *p != 0; ++p, ++m_pCurPos)
		*m_pCurPos = (*p) & 0xFF;
}


/**
 *
 */
void Nyx::CTraceCompositorBuffer_Ansi::Write(const char* szText)
{
	for (const char* p = szText; *p != 0; ++p, ++m_pCurPos)
		*m_pCurPos = *p;
}


/**
 *
 */
void Nyx::CTraceCompositorBuffer_Ansi::Write(const wchar_t& c)
{
	*m_pCurPos = c & 0xFF;
	++ m_pCurPos;
}

/**
 *
 */
void Nyx::CTraceCompositorBuffer_Ansi::Write(const char& c)
{
	*m_pCurPos = c;
	++ m_pCurPos;
}


/**
 *
 */
void Nyx::CTraceCompositorBuffer_Ansi::End(const Nyx::CTraceHeader& header, Nyx::CTraceOutput* pTraceOutput )
{
	*m_pCurPos = '\0';
	pTraceOutput->Write(header, m_pBuffer);
}


/**
 *
 */
Nyx::CTraceCompositorBuffer* Nyx::CTraceCompositorBuffer_Ansi::Clone() const
{
	return new CTraceCompositorBuffer_Ansi();
}

