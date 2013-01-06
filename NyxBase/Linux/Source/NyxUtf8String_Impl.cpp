#include "NyxUtf8String.hpp"

#include <string.h>

namespace Nyx
{
	/**
	 *
	 */
	CUtf8String::CUtf8String() :
	CMFString()
	{
		m_Flags.fChar = 1;
		m_Flags.fDynAllocated = 1;
		m_Flags.fMutable = 1;
		m_Format = kSF_UTF8;
	}


	/**
	 *
	 */
	CUtf8String::CUtf8String(size_t size) :
	CMFString(size, kSF_UTF8)
	{

	}


	/**
	 *
	 */
	CUtf8String::CUtf8String(const char* szValue) :
	CMFString(szValue)
	{

	}


	/**
	 *
	 */
	const CUtf8String& CUtf8String::operator = (const char* szText)
	{
		Set(szText, kSF_UTF8);
		return *this;
	}


	/**
	 *
	 */
	size_t CUtf8String::size() const
	{
		return strlen(m_Buffer.pConstChar);
	}
}

