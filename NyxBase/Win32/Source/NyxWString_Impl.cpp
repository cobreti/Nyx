#include "NyxWString.hpp"
#include "NyxBodyBlock.hpp"
#include "NyxAString.hpp"
#include "NyxAssert.hpp"

namespace Nyx
{
	/**
	 *
	 */
	CWString::CWString() :
	CMFString()
	{
		m_Flags.fWideChar = 1;
		m_Flags.fDynAllocated = 1;
		m_Flags.fMutable = 1;
	}
	
	
	/**
	 *
	 */
	CWString::CWString(const wchar_t* wszValue) :
	CMFString(wszValue)
	{
	}


	/**
	 *
	 */
	CWString::CWString(const CMFString& rString) :
	CMFString()
	{
		m_Flags.fDynAllocated = 1;
		m_Flags.fMutable = 1;
		HandleErrorOnCond( !rString.IsWideString(), "invalid string format" );
		Set(rString);
	}
		
	
	/**
	 *
	 */
	const wchar_t& CWString::operator [] (size_t index) const
	{
		NyxAssert( index < BufferLen(), "invalid index position" );
		return m_Buffer.pConstWChar[index];
	}
	
	
	/**
	 *
	 */
	wchar_t& CWString::operator [] (size_t index)
	{
		NyxAssert( index < BufferLen(), "invalid index position" );
		return m_Buffer.pWChar[index];
	}
	
	
	/**
	 *
	 */
	CMFTmpString CWString::operator + (const CMFString& str) const
	{
		CMFTmpString	wstr;
		
		Add(str, wstr);
		
		return wstr;
	}
	
	
	/**
	 *
	 */
	CMFTmpString CWString::operator + (const wchar_t* wszValue) const
	{
		CMFTmpString	wstr;
		
		Add(wszValue, wstr);
		
		return wstr;
	}

	
	/**
	 *
	 */
	const CWString& CWString::operator = (const CMFString& str)
	{
		NyxAssert( str.IsWideString(), "invalid string format" );
		Set(str);
		return *this;
	}
	
	
	/**
	 *
	 */
	const CWString& CWString::operator = (const CMFTmpString& str)
	{
		NyxAssert( str.IsWideString(), "invalid string format" );
		CMFString::operator = (str);
		return *this;
	}
	
	
	/**
	 *
	 */
	const CWString& CWString::operator = (const CAString& str)
	{
		FromCharToWideChar(str.m_Buffer.pConstChar);
		return *this;
	}

	/**
	 *
	 */
	const CWString& CWString::operator = (const wchar_t* wszText)
	{
		CMFString::operator = (wszText);
		return *this;
	}


	/**
	 *
	 */
	const CWString& CWString::operator = (const char* szText)
	{
		FromCharToWideChar(szText);
		return *this;
	}


    /**
     *
     */
    size_t CWString::length() const
    {
        return wcslen(m_Buffer.pConstWChar);
    }

	/**
	 *
	 */
	bool CWString::operator == (const CWString& str) const
	{
		return wcscmp(m_Buffer.pConstWChar, str.m_Buffer.pConstWChar) == 0;
	}


	/**
	 *
	 */
	bool CWString::operator != (const CWString& str) const
	{
		return wcscmp(m_Buffer.pConstWChar, str.m_Buffer.pConstWChar) != 0;
	}


	/**
	 *
	 */
	bool CWString::operator < (const CWString& str) const
	{
		return wcscmp(m_Buffer.pConstWChar, str.m_Buffer.pConstWChar) < 0;
	}

    
    /**
     *
     */
    bool CWString::operator > (const CWString& str) const
    {
        return wcscmp(m_Buffer.pConstWChar, str.m_Buffer.pConstWChar) > 0;
    }
}

