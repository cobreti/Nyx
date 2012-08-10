#ifndef _NYXTRACECOMPOSITORBUFFER_WIDECHAR_HPP_
#define _NYXTRACECOMPOSITORBUFFER_WIDECHAR_HPP_

#include "NyxTraceCompositorBuffer.hpp"


namespace Nyx
{
	class CTraceCompositorBuffer_WideChar : public Nyx::CTraceCompositorBuffer
	{
	public: // public functions
		CTraceCompositorBuffer_WideChar();
		virtual ~CTraceCompositorBuffer_WideChar();

        virtual void Release();
		virtual void Begin();
		virtual void Write(const wchar_t& c);
		virtual void Write(const char& c);
		virtual void Write(const wchar_t* wszText);
		virtual void Write(const char* szText);
		virtual void End( const Nyx::CTraceHeader& header, Nyx::CTraceOutput* pTraceOutput );
		virtual CTraceCompositorBuffer* Clone() const;

	protected: // protected members

		enum
		{
			kBufferSize = 4096
		};

		wchar_t*					m_pBuffer;
		wchar_t*					m_pCurPos;
		wchar_t*					m_pStartBufferPos;
	};
}

#endif // _NYXTRACECOMPOSITORBUFFER_WIDECHAR_HPP_
