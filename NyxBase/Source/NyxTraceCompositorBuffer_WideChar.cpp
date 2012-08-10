#include "NyxTraceCompositorBuffer_WideChar.hpp"
#include "NyxTraceFeed.hpp"
#include "NyxTraceHeader.hpp"

/**
 *
 */
Nyx::CTraceCompositorBuffer_WideChar::CTraceCompositorBuffer_WideChar() :
m_pBuffer(NULL),
m_pCurPos(NULL),
m_pStartBufferPos(NULL)
{
	m_pBuffer = new wchar_t[kBufferSize];
	m_pCurPos = m_pBuffer;
	m_pStartBufferPos = m_pBuffer;
}


/**
 *
 */
Nyx::CTraceCompositorBuffer_WideChar::~CTraceCompositorBuffer_WideChar()
{
	delete[] m_pBuffer;
}


/**
 *
 */
void Nyx::CTraceCompositorBuffer_WideChar::Release()
{
    delete this;
}


/**
 *
 */
void Nyx::CTraceCompositorBuffer_WideChar::Begin()
{
	m_pCurPos = m_pStartBufferPos;
}


/**
 *
 */
void Nyx::CTraceCompositorBuffer_WideChar::Write(const wchar_t* wszText)
{
	for (const wchar_t* p = wszText; *p != 0; ++p, ++m_pCurPos)
		*m_pCurPos = *p;
}


/**
 *
 */
void Nyx::CTraceCompositorBuffer_WideChar::Write(const char* szText)
{
	for (const char* p = szText; *p != 0; ++p, ++m_pCurPos)
		*m_pCurPos = *p;
}


/**
 *
 */
void Nyx::CTraceCompositorBuffer_WideChar::Write(const wchar_t& c)
{
	*m_pCurPos = c;
	++ m_pCurPos;
}

/**
 *
 */
void Nyx::CTraceCompositorBuffer_WideChar::Write(const char& c)
{
	*m_pCurPos = c;
	++ m_pCurPos;
}


/**
 *
 */
void Nyx::CTraceCompositorBuffer_WideChar::End(const Nyx::CTraceHeader& header, Nyx::CTraceOutput* pTraceOutput )
{
	*m_pCurPos = L'\0';
	pTraceOutput->Write(header, m_pBuffer);
}


/**
 *
 */
Nyx::CTraceCompositorBuffer* Nyx::CTraceCompositorBuffer_WideChar::Clone() const
{
	return new CTraceCompositorBuffer_WideChar();
}

