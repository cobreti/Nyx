#ifndef _NYXTRACEFEED_HPP_
#define _NYXTRACEFEED_HPP_

#include "NyxTypes.hpp"
#include "NyxRef.hpp"

#include <stdio.h>

namespace Nyx
{
	/**
	 *	\brief		Base trace feed object
	 */
	class CTraceFeed
	{
	public:

		enum ECharFormat
		{
			eCF_Ansi,
			eCF_WideChar
		};

	public:
		virtual const wchar_t* GetWideCharText() const = 0;
		virtual const char* GetAnsiText() const = 0;
		virtual ECharFormat CharFormat() const = 0;
	};
	
	
	/**
	 *
	 */
	class CAnsiTraceFeed : public CTraceFeed
	{
	public:
		CAnsiTraceFeed(const char* szBuffer) : m_szBuffer(szBuffer) {}
		virtual ~CAnsiTraceFeed() {}
		
		virtual const wchar_t* GetWideCharText() const { return NULL; }
		virtual const char* GetAnsiText() const { return m_szBuffer; }
		virtual ECharFormat CharFormat() const { return eCF_Ansi; }
		
	protected:
		
		const char*		m_szBuffer;
	};
	
	
	/**
	 *
	 */
	class CWideCharTraceFeed : public CTraceFeed
	{
	public:
		CWideCharTraceFeed(const wchar_t* wszBuffer) : m_wszBuffer(wszBuffer) {}
		~CWideCharTraceFeed() {}
				
		virtual const wchar_t* GetWideCharText() const { return m_wszBuffer; }
		virtual const char* GetAnsiText() const { return NULL; }
		virtual ECharFormat CharFormat() const { return eCF_WideChar; }
		
	protected:
		
		const wchar_t*		m_wszBuffer;
	};
}

#endif // _NYXTRACEFEED_HPP_
