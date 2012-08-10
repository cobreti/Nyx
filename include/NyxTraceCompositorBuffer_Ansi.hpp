#ifndef _NYXTRACECOMPOSITORBUFFER_ANSI_HPP_
#define _NYXTRACECOMPOSITORBUFFER_ANSI_HPP_

#include "NyxTraceCompositorBuffer.hpp"


namespace Nyx
{
	class CTraceCompositorBuffer_Ansi : public Nyx::CTraceCompositorBuffer
	{
	public: // public functions
		CTraceCompositorBuffer_Ansi();
		virtual ~CTraceCompositorBuffer_Ansi();

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

		char*					m_pBuffer;
		char*					m_pCurPos;
		char*					m_pStartBufferPos;
	};
}

#endif // _NYXTRACECOMPOSITORBUFFER_ANSI_HPP_
