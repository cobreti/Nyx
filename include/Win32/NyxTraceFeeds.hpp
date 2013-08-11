#ifndef _NYXTRACEFEEDS_HPP_
#define _NYXTRACEFEEDS_HPP_

#define NOMINMAX

#include <Windows.h>
#include <mmsystem.h>

#include "NyxTraceFeed.hpp"
#include "NyxTraceStream.hpp"

#pragma warning (disable:4996)

namespace Nyx
{
	class CTF_WText;
	class CTF_Int;
	class CTF_Float;
	class CTF_ThreadId;
	class CTF_TickCount;
	class CTF_Double;


	/**
	 *	\brief		Wide string trace feed
	 */
	class CTF_Text : public CTraceFeed
	{
	public:
		CTF_Text(const wchar_t* wszText) : m_wszText(wszText) { }
		~CTF_Text() { }
		
		virtual const wchar_t* GetWideCharText() const { return m_wszText; }
		virtual const char* GetAnsiText() const { return NULL; }
		virtual ECharFormat CharFormat() const { return eCF_WideChar; }
		
	protected:
		 const wchar_t*		m_wszText;
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
	 *
	 */
	class CTF_AnsiText : public CTraceFeed
	{
	public:
		CTF_AnsiText(const char* szText) : m_szText(szText) {}		
		~CTF_AnsiText() {}

		virtual const wchar_t* GetWideCharText() const { return NULL; }
		virtual const char* GetAnsiText() const { return m_szText; }
		virtual ECharFormat CharFormat() const { return eCF_Ansi; }
	
	protected:
		const char*		m_szText;	
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
	class CTF_Int : public CTraceFeed
	{
	public:
		CTF_Int(int nValue)
		{
			//swprintf_s( m_wszBuffer, kBufferSize, L"%i", nValue);
			sprintf_s( m_szBuffer, kBufferSize, "%i", nValue);
		}

		virtual const wchar_t* GetWideCharText() const { return NULL; }
		virtual const char* GetAnsiText() const { return m_szBuffer; }
		virtual ECharFormat CharFormat() const { return eCF_Ansi; }
		
	private: // private members
		
		enum { kBufferSize = 20 };
		
		char		m_szBuffer[kBufferSize];
		//wchar_t		m_wszBuffer[kBufferSize];
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
    inline CTraceStream& operator << ( CTraceStream& stream, const Nyx::NyxSize& value )
    {
        stream << CTF_Int( static_cast<const int&>(value) );
        return stream;
    }

    
    /**
	 *
	 */
	class CTF_Double : public CTraceFeed
	{
	public:
		CTF_Double(const double& fValue)
		{
			sprintf_s(m_szBuffer, kBufferSize, "%f", fValue);
		}
		
		virtual const wchar_t* GetWideCharText() const { return NULL; }
		virtual const char* GetAnsiText() const { return m_szBuffer; }
		virtual ECharFormat CharFormat() const { return eCF_Ansi; }
	
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
	class CTF_Float : public CTraceFeed
	{
	public:
		CTF_Float(const float& value)
		{
			//swprintf_s( m_wszBuffer, kBufferSize, L"%f", value);
			sprintf_s( m_szBuffer, kBufferSize, "%f", value);
		}
		
		virtual const wchar_t* GetWideCharText() const { return NULL; }
		virtual const char* GetAnsiText() const { return m_szBuffer; }
		virtual ECharFormat CharFormat() const { return eCF_Ansi; }

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
	class CTF_Hex : public CTraceFeed
	{
	public:
		CTF_Hex(const long& nValue)
		{
			//swprintf(m_wszBuffer, kBufferSize, L"%x", nValue);
			sprintf_s(m_szBuffer, kBufferSize, "%x", nValue);
		}
		
		virtual const wchar_t* GetWideCharText() const { return NULL; }
		virtual const char* GetAnsiText() const { return m_szBuffer; }
		virtual ECharFormat CharFormat() const { return eCF_Ansi; }

	private: // private members
		
		enum { kBufferSize = 20 };
		
		char		m_szBuffer[kBufferSize];
	};


    /**
     *	\brief		pointer value trace feed
     */
    class CTF_Ptr : public CTraceFeed
    {
    public:
        CTF_Ptr(void* pPtr)
        {
            //swprintf(m_wszBuffer, kBufferSize, L"%x", nValue);
            sprintf_s(m_szBuffer, kBufferSize, "%Xh", pPtr);
        }

        virtual const wchar_t* GetWideCharText() const { return NULL; }
        virtual const char* GetAnsiText() const { return m_szBuffer; }
        virtual ECharFormat CharFormat() const { return eCF_Ansi; }

    private: // private members

        enum { kBufferSize = 20 };

        char		m_szBuffer[kBufferSize];
    };



	/**
	 *	\brief	Current thread id trace feed
	 */
	class CTF_ThreadId : public CTraceFeed
	{
	public:	// public methods
		CTF_ThreadId()
		{
			//swprintf(m_wszBuffer, (size_t)kBufferSize, L" [%08X] ", GetCurrentThreadId()); 
			sprintf_s(m_szBuffer, kBufferSize, " [%08X] ", GetCurrentThreadId()); 
		}
		
		virtual const wchar_t* GetWideCharText() const { return NULL; }
		virtual const char* GetAnsiText() const { return m_szBuffer; }
		virtual ECharFormat CharFormat() const { return eCF_Ansi; }
		
	private: // private members
	
		enum { kBufferSize = 16 };
		
		char		m_szBuffer[kBufferSize];
	};
	
	/**
	 *	\brief	current tick count trace feed
	 */
	class CTF_TickCount : public CTraceFeed
	{
	public: // public methods
		CTF_TickCount()
		{
			//swprintf(m_wszBuffer, (size_t)kBufferSize, L" [%i] ", GetTickCount() );
			sprintf_s(m_szBuffer, kBufferSize, " [%i] ", timeGetTime() );
		}

		virtual const wchar_t* GetWideCharText() const { return NULL; }
		virtual const char* GetAnsiText() const { return m_szBuffer; }
		virtual ECharFormat CharFormat() const { return eCF_Ansi; }

	private: // private members
		
		enum { kBufferSize = 30 };
		
		char		m_szBuffer[kBufferSize];
	};
}

#endif // _NYXTRACEFEEDS_HPP_

