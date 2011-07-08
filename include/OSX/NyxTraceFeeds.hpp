#ifndef _NYXTRACEFEEDS_HPP_
#define _NYXTRACEFEEDS_HPP_

#include "NyxTraceFeed.hpp"

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
	 *	\brief		Ansi string trace feed
	 */
	class CTF_AnsiText : public CAnsiTraceFeed
	{
	public:
		CTF_AnsiText(const char* szText) : CAnsiTraceFeed(szText) {}		
		~CTF_AnsiText() {}
	};
	
	
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
		
//		virtual const wchar_t* GetWideCharText() const { return NULL; }
//		virtual const char* GetAnsiText() const { return m_szBuffer; }
//		virtual ECharFormat CharFormat() const { return eCF_Ansi; }
		
	private: // private members
		
		enum { kBufferSize = 10 };
		
		char		m_szBuffer[kBufferSize];
	};
	
	
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
		
//		virtual const wchar_t* GetWideCharText() const { return NULL; }
//		virtual const char* GetAnsiText() const { return m_szBuffer; }
//		virtual ECharFormat CharFormat() const { return eCF_Ansi; }
	
	private: // private members
	
		enum { kBufferSize = 20 };
		
		char		m_szBuffer[kBufferSize];
	};


	/**
	 *
	 */
	class CTF_Float : public CAnsiTraceFeed
	{
	public:
		CTF_Float(const double& value) : CAnsiTraceFeed(m_szBuffer)
		{
			sprintf( m_szBuffer, "%f", value);
		}
		
//		virtual const wchar_t* GetWideCharText() const { return NULL; }
//		virtual const char* GetAnsiText() const { return m_szBuffer; }
//		virtual ECharFormat CharFormat() const { return eCF_Ansi; }
		
	private: // private members
		
		enum { kBufferSize = 20 };
		
		char		m_szBuffer[kBufferSize];
	};


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
		
//		virtual const wchar_t* GetWideCharText() const { return NULL; }
//		virtual const char* GetAnsiText() const { return m_szBuffer; }
//		virtual ECharFormat CharFormat() const { return eCF_Ansi; }
	
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
		
//		virtual const wchar_t* GetWideCharText() const { return NULL; }
//		virtual const char* GetAnsiText() const { return m_szBuffer; }
//		virtual ECharFormat CharFormat() const { return eCF_Ansi; }
		
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
			sprintf(m_szBuffer, " [%012i%06i] ", (int)t.tv_sec, (int)t.tv_usec );
		}
		
//		virtual const wchar_t* GetWideCharText() const { return NULL; }
//		virtual const char* GetAnsiText() const { return m_szBuffer; }
//		virtual ECharFormat CharFormat() const { return eCF_Ansi; }

	private: // private members
		
		enum { kBufferSize = 30 };
		
		char		m_szBuffer[kBufferSize];
	};
}

#endif // _NYXTRACEFEEDS_HPP_

