#include "NyxAString.hpp"
#include "NyxBodyBlock.hpp"
#include "NyxWString.hpp"
#include "NyxAssert.hpp"

#include <string.h>

namespace Nyx
{
	/**
	 *
	 */
	CAString::CAString() :
	CMFString()
	{
		m_Flags.fAnsi = 1;
		m_Flags.fDynAllocated = 1;
		m_Flags.fMutable = 1;
	}
	
	/**
	 *
	 */
	CAString::CAString(const char* szValue) :
	CMFString(szValue)
	{
	}
	
	
	/**
	 *
	 */
	CAString::CAString(const CMFString& rString) :
	CMFString()
	{
		m_Flags.fDynAllocated = 1;
		m_Flags.fMutable = 1;
		HandleErrorOnCond( !rString.IsAnsiString(), "invalid string format" );
		Set(rString);
	}
	
	
	/**
	 *
	 */
	const char& CAString::operator [] (size_t index) const
	{
		NyxAssert( index < BufferLen(), "invalid index position" );
		return m_Buffer.pConstChar[index];
	}


	/**
	 *
	 */
	char& CAString::operator [] (size_t index)
	{
		NyxAssert( index < BufferLen(), "invalid index position" );
		return m_Buffer.pChar[index];
	}
	
	
	/**
	 *
	 */
	CMFTmpString CAString::operator + (const CMFString& str) const
	{
		CMFTmpString	resultStr;
		
		Add(str, resultStr);
		
		return resultStr;		
	}


	/**
	 *
	 */
	CMFTmpString CAString::operator + (const char* szValue) const
	{
		CMFTmpString		resultStr;
		
		Add(szValue, resultStr);
		
		return resultStr;
	}
	
	
	/**
	 *
	 */
	const CAString& CAString::operator = (const CMFString& str)
	{
		NyxAssert( str.IsAnsiString(), "invalid string format" );
		Set(str);
		return *this;
	}
	
	
	/**
	 *
	 */
	const CAString& CAString::operator = (const CMFTmpString& str)
	{
		NyxAssert( str.IsAnsiString(), "invalid string format" );
		CMFString::operator = (str);
		return *this;
	}
	
	
	/**
	 *
	 */
	const CAString& CAString::operator = (const CWString& str)
	{
		FromWideCharToChar(str.m_Buffer.pConstWChar);
		return *this;
	}
	
	
	/**
	 *
	 */
	const CAString& CAString::operator = (const char* szText)
	{
		Set(szText);
		return *this;
	}
	
	
	/**
	 *
	 */
	const CAString& CAString::operator = (const wchar_t* wszText)
	{
		FromWideCharToChar(wszText);
		return *this;
	}
	
	
	/**
	 *
	 */
	bool CAString::operator < (const CAString& str) const
	{
		return strcmp(m_Buffer.pConstChar, str.m_Buffer.pConstChar) < 0;
	}
    
    
    /**
     *
     */
    size_t CAString::length() const
    {
        return strlen(m_Buffer.pConstChar);
    }
}

