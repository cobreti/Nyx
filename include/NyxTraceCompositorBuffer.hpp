#ifndef _NYXTRACECOMPOSITORBUFFER_HPP_
#define _NYXTRACECOMPOSITORBUFFER_HPP_

#include "NyxTraceOutput.hpp"


namespace Nyx
{
	class CTraceFeed;
	class CTraceOutput;
}


namespace Nyx
{
	class CTraceCompositorBuffer
	{
	public: // public functions
        virtual void Release() = 0;
        
		virtual void Begin() = 0;
		virtual void Write(const wchar_t& c) = 0;
		virtual void Write(const char& c) = 0;
		virtual void Write(const wchar_t* wszText) = 0;
		virtual void Write(const char* szText) = 0;
		virtual void End( const Nyx::CTraceHeader& header, Nyx::CTraceOutput* pTraceOutput ) = 0;
		virtual CTraceCompositorBuffer* Clone() const = 0;
        
    protected:
        
        virtual ~CTraceCompositorBuffer() {}
	};
}



#endif // _NYXTRACECOMPOSITORBUFFER_HPP_
