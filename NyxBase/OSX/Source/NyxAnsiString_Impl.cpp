#include "NyxAnsiString_Impl.hpp"


/**
 *
 */
Nyx::CAnsiStringRef Nyx::CAnsiString::Alloc()
{
	return new NyxOSX::CAnsiString_Impl();
}


/**
 *
 */
Nyx::CAnsiStringRef Nyx::CAnsiString::Alloc(const char* szText)
{
	return new NyxOSX::CAnsiString_Impl(szText);
}


/**
 *
 */
NyxOSX::CAnsiString_Impl::CAnsiString_Impl()
{
}


/**
 *
 */
NyxOSX::CAnsiString_Impl::CAnsiString_Impl(const char* szText) :
m_String(szText)
{
}


/**
 *
 */
NyxOSX::CAnsiString_Impl::~CAnsiString_Impl()
{
}


/**
 *
 */
const char* NyxOSX::CAnsiString_Impl::c_str() const
{
	return m_String.c_str();
}


/**
 *
 */
void NyxOSX::CAnsiString_Impl::Set(const char* szText)
{
	m_String = szText;
}


/**
 *
 */
void NyxOSX::CAnsiString_Impl::Set(const Nyx::CAnsiString* pString)
{
	m_String = GetImpl(pString)->m_String;
}


void NyxOSX::CAnsiString_Impl::Set( const wchar_t* wszText )
{
	m_String = "";
	
	if ( wszText == NULL )
		return;
	
	size_t				len = wcslen(wszText);
	char*				pBuffer = (char*)malloc(len+1);
	char*				pDst = pBuffer;
	const wchar_t*		pSrc = wszText;
	
	while (len > 0)
	{
		*pDst = (*pSrc && 0xFF);
		++ pDst;
		++ pSrc;
		-- len;
	}
	
	*pDst = '\0';
	
	m_String = pBuffer;
	free(pBuffer);
}


/**
 *
 */
void NyxOSX::CAnsiString_Impl::Append(const char* szText)
{
	m_String += szText;
}


/**
 *
 */
bool NyxOSX::CAnsiString_Impl::IsEqualTo(const char* szText) const
{
	return (m_String == szText);
}


/**
 *
 */
bool NyxOSX::CAnsiString_Impl::IsEqualTo(const Nyx::CAnsiString* pString) const
{
	return (m_String == GetImpl(pString)->m_String);
}


/**
 *
 */
bool NyxOSX::CAnsiString_Impl::IsGreaterThan(const char* szText) const
{
	return (m_String > szText);
}


/**
 *
 */
bool NyxOSX::CAnsiString_Impl::IsGreaterThan(const Nyx::CAnsiString* pString) const
{
	return (m_String > GetImpl(pString)->m_String);
}


/**
 *
 */
bool NyxOSX::CAnsiString_Impl::IsGreaterOrEqualThan(const char* szText) const
{
	return (m_String >= szText);
}


/**
 *
 */
bool NyxOSX::CAnsiString_Impl::IsGreaterOrEqualThan(const Nyx::CAnsiString* pString) const
{
	return (m_String >= GetImpl(pString)->m_String);
}


/**
 *
 */
bool NyxOSX::CAnsiString_Impl::IsLowerThan(const char* szText) const
{
	return (m_String < szText);
}


/**
 *
 */
bool NyxOSX::CAnsiString_Impl::IsLowerThan(const Nyx::CAnsiString* pString) const
{
	return (m_String < GetImpl(pString)->m_String);
}


/**
 *
 */
bool NyxOSX::CAnsiString_Impl::IsLowerOrEqualThan(const char* szText) const
{
	return (m_String <= szText);
}


/**
 *
 */
bool NyxOSX::CAnsiString_Impl::IsLowerOrEqualThan(const Nyx::CAnsiString* pString) const
{
	return (m_String <= GetImpl(pString)->m_String);
}

