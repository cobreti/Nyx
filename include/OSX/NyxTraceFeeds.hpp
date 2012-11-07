#ifndef _NYXTRACEFEEDS_HPP_
#define _NYXTRACEFEEDS_HPP_

#include "NyxTraceFeed.hpp"
#include "NyxTraceStream.hpp"

#include <pthread.h>
#include <sys/time.h>
#include <wchar.h>


namespace Nyx
{
	class CTF_WText;
	class CTF_Int;
	class CTF_ThreadId;
	class CTF_TickCount;
	class CTF_Double;


	/**
	 *	\brief		Wide string trace feed
	 */
	class CTF_Text : public CWideCharTraceFeed
	{
	public:
		CTF_Text(const wchar_t* const wszText) : CWideCharTraceFeed(wszText) { }
		~CTF_Text() { }
	};

    
    /**
     *
     */
    inline CTraceStream& operator << ( CTraceStream& stream, const wchar_t* text )
    {
        stream << CTF_Text(text);
        return stream;
    }
    

	/**
	 *	\brief		Ansi string trace feed
	 */
	class CTF_AnsiText : public CAnsiTraceFeed
	{
	public:
		CTF_AnsiText(const char* szText) : CAnsiTraceFeed(szText) {}		
		~CTF_AnsiText() {}
	};
	
    
    /**
     *
     */
    inline CTraceStream& operator << ( CTraceStream& stream, const char* text )
    {
        stream << CTF_AnsiText(text);
        return stream;
    }
    
	
	/**
	 *	\brief		Integer trace feed
	 */
	class CTF_Int : public CAnsiTraceFeed
	{
	public:
		CTF_Int(const Nyx::Int32& nValue) : CAnsiTraceFeed(m_szBuffer)
		{
			sprintf(m_szBuffer, "%i", nValue);
		}
		
	private: // private members
		
		enum { kBufferSize = 10 };
		
		char		m_szBuffer[kBufferSize];
	};
	
    
    /**
     *
     */
    inline CTraceStream& operator << ( CTraceStream& stream, const Nyx::Int32& value )
    {
        stream << CTF_Int(value);
        return stream;
    }
    
	
    /**
     *
     */
    inline CTraceStream& operator << ( CTraceStream& stream, const Nyx::UInt32& value )
    {
        stream << CTF_Int(value);
        return stream;
    }
    
	
    /**
     *
     */
    inline CTraceStream& operator << ( CTraceStream& stream, const Nyx::NyxSize& value )
    {
        stream << CTF_Int(value);
        return stream;
    }
    
	

	/**
	 *
	 */
	class CTF_Double : public CAnsiTraceFeed
	{
	public:
		CTF_Double(const double& fValue) : CAnsiTraceFeed(m_szBuffer)
		{
			sprintf(m_szBuffer, "%f", fValue);
		}
		
	private: // private members
	
		enum { kBufferSize = 20 };
		
		char		m_szBuffer[kBufferSize];
	};
    
    
    /**
     *
     */
    inline CTraceStream& operator << ( CTraceStream& stream, const double& value )
    {
        stream << CTF_Double(value);
        return stream;
    }


	/**
	 *
	 */
	class CTF_Float : public CAnsiTraceFeed
	{
	public:
		CTF_Float(const float& value) : CAnsiTraceFeed(m_szBuffer)
		{
			sprintf( m_szBuffer, "%f", value);
		}
		
	private: // private members
		
		enum { kBufferSize = 20 };
		
		char		m_szBuffer[kBufferSize];
	};
    
    
    /**
     *
     */
    inline CTraceStream& operator << ( CTraceStream& stream, const float& value)
    {
        stream << CTF_Float(value);
        return stream;
    }


	/**
	 *	\brief		hex value trace feed
	 */
	class CTF_Hex : public CAnsiTraceFeed
	{
	public:
		CTF_Hex(const long& nValue) : CAnsiTraceFeed(m_szBuffer)
		{
			sprintf(m_szBuffer, "%x", (unsigned int)nValue);
		}
		
	private: // private members
		
		enum { kBufferSize = 20 };
		
		char		m_szBuffer[kBufferSize];
	};
	
	
	/**
	 *	\brief		hex value trace feed
	 */
	class CTF_Ptr : public CAnsiTraceFeed
	{
	public:
		CTF_Ptr(void* addr) : CAnsiTraceFeed(m_szBuffer)
		{
			sprintf(m_szBuffer, "%lXh", (unsigned long)addr);
		}
		
	private: // private members
		
		enum { kBufferSize = 20 };
		
		char		m_szBuffer[kBufferSize];
	};
	
	
	/**
	 *	\brief	Current thread id trace feed
	 */
	class CTF_ThreadId : public CAnsiTraceFeed
	{
	public:	// public methods
		CTF_ThreadId() : CAnsiTraceFeed(m_szBuffer)
		{
			sprintf(m_szBuffer, " [%8lX] ", (long unsigned int)(void*)pthread_self()); 
		}
		
	private: // private members
	
		enum { kBufferSize = 16 };
		
		char		m_szBuffer[kBufferSize];
	};
	
	/**
	 *	\brief	current tick count trace feed
	 */
	class CTF_TickCount : public CAnsiTraceFeed
	{
	public: // public methods
		CTF_TickCount() : CAnsiTraceFeed(m_szBuffer)
		{
			timeval t;
			gettimeofday(&t, NULL);
			sprintf(m_szBuffer, " [%012i.%06i] ", (int)t.tv_sec, (int)t.tv_usec );
		}
		
	private: // private members
		
		enum { kBufferSize = 30 };
		
		char		m_szBuffer[kBufferSize];
	};
}

#endif // _NYXTRACEFEEDS_HPP_

