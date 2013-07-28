#include <string.h>
#include <wchar.h>
#include <stdlib.h>
#include <iconv.h>
//#include <stdio.h>

#include "NyxMFString.hpp"
#include "NyxBodyBlock.hpp"
#include "NyxAString.hpp"
#include "NyxWString.hpp"
#include "NyxAssert.hpp"

namespace Nyx
{
	enum
	{
		kWCharShift = sizeof(wchar_t) / 2
	};
	
	
	/**
	 *
	 */
	TStringFlags::TStringFlags() :
	fChar(0),
	fWideChar(0),
	fFixedSize(0),
	fDynAllocated(0),
	fMutable(0)
	{
	}
	
	
	/**
	 *
	 */
	void TStringFlags::Clear()
	{
		memset(this, 0, sizeof(TStringFlags));
	}
	
	
	/**
	 *
	 */
	CMFString::CMFString() :
	m_BufferSize(0)
	{
		m_Buffer.pData = NULL;
		m_Format = kSF_Unknown;
	}
	
	
	/**
	 *
	 */
	CMFString::CMFString(const char* szValue, EStringsFormat format /*= kSF_Ansi*/ ) :
	m_BufferSize(0)
	{
		m_Buffer.pData = NULL;
		m_Flags.fDynAllocated = 1;
		m_Flags.fChar = 1;
		m_Flags.fMutable = 1;
		m_Format = format;
		
		Set(szValue);
	}
	
	
	/**
	 *
	 */
	CMFString::CMFString(const wchar_t* wszValue) :
	m_BufferSize(0)
	{
		m_Buffer.pData = NULL;
		m_Flags.fDynAllocated = 1;
		m_Flags.fWideChar = 1;
		m_Flags.fMutable = 1;
		m_Format = kSF_Wide;
		
		Set(wszValue);
	}
	
	
	/**
	 *
	 */
	CMFString::CMFString(const CMFStringRef& refValue) :
	m_BufferSize(0)
	{
		m_Buffer.pData = NULL;
		m_Format = kSF_Unknown;
//		m_Flags.fMutable = 1;

		if ( refValue.m_Flags.fChar )
		{
			m_Flags.fChar = 1;
			m_Buffer.pConstChar = refValue.m_Buffer.pConstChar;
			m_BufferSize = LenToSize(strlen(m_Buffer.pChar) + 1, sizeof(char));
			m_Format = kSF_Ansi;
		}
		else if ( refValue.m_Flags.fWideChar )
		{
			m_Flags.fWideChar = 1;
			m_Buffer.pConstWChar = refValue.m_Buffer.pConstWChar;
			m_BufferSize = LenToSize(wcslen(m_Buffer.pWChar) + 1, sizeof(wchar_t));
			m_Format = kSF_Wide;
		}
	};
	
	
	/**
	 *
	 */
	CMFString::CMFString(const CMFString& str) :
	m_BufferSize(0)
	{
		m_Buffer.pData = NULL;
		m_Flags.fDynAllocated = 1;
		m_Flags.fMutable = 1;
		Set(str);		
	}

	
	/**
	 *
	 */
	CMFString::CMFString(size_t size, EStringsFormat format) :
	m_BufferSize(0)
	{
		m_Buffer.pData = NULL;
		m_Flags.fDynAllocated = 1;
		m_Flags.fFixedSize = 1;
		m_Flags.fMutable = 1;
		m_Format = kSF_Unknown;
		
		switch (format)
		{
		case kSF_Ansi:
			{
				m_Flags.fChar = 1;
				m_Format = format;
				Resize( LenToSize(size, sizeof(char)) );
			}
			break;
		case kSF_Wide:
			{
				m_Flags.fWideChar = 1;
				m_Format = format;
				Resize( LenToSize(size+1, sizeof(wchar_t)) );
			}
			break;
		};
	}
	
	
	/**
	 *
	 */
	CMFString::~CMFString()
	{
		ReleaseBuffer();
	}
	
	
	/**
	 *
	 */
	const CMFString& CMFString::operator = (const char* szValue)
	{
		Set(szValue);
		return *this;
	}
	
	
	/**
	 *
	 */
	const CMFString& CMFString::operator = (const wchar_t* wszValue)
	{
		Set(wszValue);
		return *this;
	}
	
	
	/**
	 *
	 */
	const CMFString& CMFString::operator = (const CMFString& str)
	{
		Set(str);
		return *this;
	}
	
	
	/**
	 *
	 */
	const CMFString& CMFString::operator = (const CMFTmpString& str)
	{
		CMFTmpString&		tmpStr = const_cast<CMFTmpString&>(str);
		
		ReleaseBuffer();
		
		m_Flags = tmpStr.m_Flags;
		m_Buffer.pData = tmpStr.m_Buffer.pData;
		m_BufferSize = tmpStr.m_BufferSize;
		m_Format = tmpStr.m_Format;
		
		tmpStr.m_BufferSize = 0;
		tmpStr.m_Buffer.pData = NULL;
		tmpStr.m_Flags.Clear();
		tmpStr.m_Format = kSF_Unknown;
		
		return *this;
	}

	
	/**
	 *
	 */
	const CMFString& CMFString::operator += (const char* szValue)
	{
		Append(szValue);
		return *this;
	}
	
	
	/**
	 *
	 */
	const CMFString& CMFString::operator += (const wchar_t* wszValue)
	{
		Append(wszValue);
		return *this;
	}
	
	
	/**
	 *
	 */
	const CMFString& CMFString::operator += (const CMFString& str)
	{
		Append(str);
		return *this;
	}
	
	
	/**
	 *
	 */
	CMFTmpString CMFString::operator + (const CMFString& str) const
	{
		CMFTmpString	resultStr;
		
		Add(str, resultStr);
		
		return resultStr;
	}
	
	
	/**
	 *
	 */
	CMFTmpString CMFString::operator + (const char* szValue) const
	{
		CMFTmpString	resultStr;
		
		Add(szValue, resultStr);
		
		return resultStr;
	}
	
	
	/**
	 *
	 */
	CMFTmpString CMFString::operator + (const wchar_t* wszValue) const
	{
		CMFTmpString	resultStr;
		
		Add(wszValue, resultStr);
		
		return resultStr;
	}
	
	
	/**
	 *
	 */
	const CAString& CMFString::AString() const
	{
		return static_cast<const CAString&>(*this);
	}
	
	
	/**
	 *
	 */
	CAString& CMFString::AString()
	{
		return static_cast<CAString&>(*this);
	}
	
	
	/**
	 *
	 */
	const CWString& CMFString::WString() const
	{
		return static_cast<const CWString&>(*this);
	}
	
	
	/**
	 *
	 */
	CWString& CMFString::WString()
	{
		return static_cast<CWString&>(*this);
	}
	
	
	/**
	 *
	 */
	void CMFString::Reserve( size_t NumberOfCharacters )
	{
		NyxAssert( !m_Flags.fFixedSize, "cannot modify fixed size string" );
		NyxAssert( m_Flags.fDynAllocated, "cannot modify non-dynamic allocation strings" );
		
		size_t	newSize = 0;
		
		if ( m_Flags.fChar )
			newSize = LenToSize(NumberOfCharacters, sizeof(char));
		else if ( m_Flags.fWideChar )
			newSize = LenToSize(NumberOfCharacters, sizeof(wchar_t));
		
		if ( newSize > m_BufferSize )
			Resize(newSize);
	}
	
	
	/**
	 *
	 */
	size_t CMFString::Size() const
	{
		return BufferLen();
	}
	
	
	/**
	 *
	 */
	void CMFString::ReleaseBuffer()
	{
		if ( m_Flags.fDynAllocated && NULL != m_Buffer.pChar )
			free(m_Buffer.pChar);
		
		m_Buffer.pChar = NULL;
		m_BufferSize = 0;
		m_Flags.Clear();
	}
	
	
	/**
	 *
	 */
	void CMFString::Resize( size_t newsize )
	{
		NyxAssert( m_Flags.fDynAllocated, "String content hasn't been dynamically allocated" );
				
		m_Buffer.pData = realloc(m_Buffer.pData, newsize);
		HandleErrorOnCond(NULL == m_Buffer.pData, "failure to allocate string");
		
		m_BufferSize = newsize;
	}
	
	
	/**
	 *
	 */
	void CMFString::Set(const char* szValue, EStringsFormat format /*= kF_Ansi*/ )
	{
        if ( szValue == NULL )
        {
            ReleaseBuffer();
            return;
        }

        size_t	newsize = LenToSize(strlen(szValue) + 1, sizeof(char));
		
		if ( newsize > m_BufferSize && CanResize() )
			Resize( newsize );
		
		m_Flags.fChar = 1;
		m_Flags.fWideChar = 0;
		m_Format = format;
		strncpy(m_Buffer.pChar, szValue, BufferLen());
	}


	/**
	 *
	 */
	void CMFString::Set(const wchar_t* wszValue)
	{
		size_t	newsize = LenToSize(wcslen(wszValue) + 1, sizeof(wchar_t));
		
		if ( newsize > m_BufferSize && CanResize() )
			Resize( newsize );

		m_Flags.fWideChar = 1;
		m_Flags.fChar = 0;
		m_Format = kSF_Wide;
		wcsncpy(m_Buffer.pWChar, wszValue, BufferLen());
	}
	
	
	/**
	 *
	 */
	void CMFString::Set( const CMFString& str )
	{
		if ( str.m_Flags.fChar )
			Set(str.m_Buffer.pConstChar);
		else if ( str.m_Flags.fWideChar )
			Set(str.m_Buffer.pConstWChar);
	}
	
	
	/**
	 *
	 */
	void CMFString::Append( const char* szValue )
	{
		HandleErrorOnCond(!m_Flags.fChar, "Invalid string format");
		
		size_t	newsize = LenToSize(m_BufferSize + strlen(szValue), sizeof(char));
		
		if ( newsize > m_BufferSize && CanResize() )
			Resize(newsize);
		
		strncat(m_Buffer.pChar, szValue, BufferLen());
	}
	
	
	/**
	 *
	 */
	void CMFString::Append( const wchar_t* wszValue )
	{
		HandleErrorOnCond(!m_Flags.fWideChar, "Invalid string format");
		
		size_t newsize = LenToSize(m_BufferSize + wcslen(wszValue), sizeof(wchar_t));
		
		if ( newsize > m_BufferSize && CanResize() )
			Resize(newsize);
		
		wcscat(m_Buffer.pWChar, wszValue/*, BufferLen()*/);
	}
	
	
	/**
	 *
	 */
	void CMFString::Append( const CMFString& str )
	{
		if ( str.m_Flags.fChar )
			Append(str.m_Buffer.pConstChar);
		else if ( str.m_Flags.fWideChar )
			Append(str.m_Buffer.pConstWChar );
	}
	
	
	/**
	 *
	 */
	void CMFString::Add( const CMFString& str, CMFString& resultStr ) const
	{						
		if ( str.IsAnsiString() )
			Add( str.m_Buffer.pConstChar, str.m_BufferSize, resultStr );
		else
			Add( str.m_Buffer.pConstWChar, str.m_BufferSize, resultStr );
	}
	
	
	/**
	 *
	 */
	void CMFString::Add( const char* szValue, CMFString& resultStr ) const
	{
		Add( szValue, LenToSize(strlen(szValue), sizeof(char)), resultStr );
	}
	
	
	/**
	 *
	 */
	void CMFString::Add( const wchar_t* wszValue, CMFString& resultStr ) const
	{
		Add( wszValue, LenToSize(wcslen(wszValue), sizeof(wchar_t)), resultStr );
	}
	
	
	/**
	 *
	 */
	void CMFString::Add( const char* szValue, size_t sizeInBytes, CMFString& resultStr ) const
	{
		HandleErrorOnCond( !IsAnsiString(), "cannot add string of different format" );
		
		resultStr.m_Flags.fChar = 1;
		resultStr.m_Flags.fDynAllocated = 1;
		resultStr.Resize( sizeInBytes + m_BufferSize );		
		strncpy( resultStr.m_Buffer.pChar, m_Buffer.pConstChar, resultStr.BufferLen() );
		strncat( resultStr.m_Buffer.pChar, szValue, resultStr.BufferLen() );
	}
	
	
	/**
	 *
	 */
	void CMFString::Add( const wchar_t* wszValue, size_t sizeInBytes, CMFString& resultStr ) const
	{
		HandleErrorOnCond( !IsWideString(), "cannot add string of different format" );
		
		resultStr.m_Flags.fDynAllocated = 1;
		resultStr.m_Flags.fWideChar = 1;
		resultStr.Resize( sizeInBytes + m_BufferSize );
		wcsncpy( resultStr.m_Buffer.pWChar, m_Buffer.pConstWChar, resultStr.BufferLen() );
		wcsncat( resultStr.m_Buffer.pWChar, wszValue, resultStr.BufferLen() );
	}
	
	
	/**
	 *
	 */
	void CMFString::FromCharToWideChar( const char* szString )
	{
		NyxAssert( NULL != szString, "invalid ansi string : null pointer" );
		NyxAssert( m_Flags.fWideChar, "destination string isn't wide char" );

		size_t		len = strlen(szString);
		size_t		size = LenToSize( len+1, sizeof(wchar_t) );

		if ( size > m_BufferSize && CanResize() )
			Resize(size);

		wchar_t*		pDst = m_Buffer.pWChar;
		const char*		pSrc = szString;

		while ( *pSrc != '\0' )
		{
			*pDst = *pSrc;
			++pDst;
			++pSrc;
		}

		*pDst = '\0';
	}


	void CMFString::FromCharToWideChar( const char* szString, char* encoding )
	{
		NyxAssert( NULL != szString, "invalid ansi string : null pointer" );
		NyxAssert( m_Flags.fWideChar, "destination string isn't wide char" );
		
		size_t		len = strlen(szString);
		size_t		size = LenToSize( len+1, sizeof(wchar_t) );
		
		iconv_t		hConv = iconv_open("WCHAR_T", encoding);

		if ( size > m_BufferSize && CanResize() )
			Resize(size);
		
		size_t		ret = 0;
		size_t		outBytes = 0;
		char*		ptr = m_Buffer.pChar;
		
		::memset(m_Buffer.pWChar, 0, m_BufferSize);
		outBytes = m_BufferSize - sizeof(wchar_t);
		ret = iconv(hConv, (char**)&szString, &len, &ptr, &outBytes);
		
		iconv_close(hConv);
	}


	/**
	 *
	 */
	void CMFString::FromWideCharToChar( const wchar_t* wszString )
	{
		NyxAssert( NULL != wszString, "invalid wide string : null pointer" );
		NyxAssert( m_Flags.fChar, "destination string isn't ansi" );
		
		size_t		len = wcslen(wszString);
		size_t		size = len + 1;
		
		if ( size > m_BufferSize && CanResize() )
			Resize(size);
		
		const wchar_t*		pSrc = wszString;
		char*				pDst = m_Buffer.pChar;
		
		while ( *pSrc != L'\0' )
		{
			*pDst = *pSrc & 0xFF;
			++ pDst;
			++ pSrc;
		}
		
		*pDst = L'\0';
	}
	
	
	/**
	 *
	 */
	size_t CMFString::BufferLen() const
	{
		if ( m_Flags.fChar )
			return m_BufferSize;
		else if ( m_Flags.fWideChar )
			return m_BufferSize >> kWCharShift;
		
		return 0;
	}
	
	
	/**
	 *
	 */
	CMFStringRef::CMFStringRef(const char* szValue)
	{
		m_Buffer.pConstChar = szValue;
		m_Flags.fChar = 1;
	}
	
	
	/**
	 *
	 */
	CMFStringRef::CMFStringRef(const wchar_t* wszValue)
	{
		m_Buffer.pConstWChar = wszValue;
		m_Flags.fWideChar = 1;
	}
}


