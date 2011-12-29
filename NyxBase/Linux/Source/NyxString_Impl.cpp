#include "NyxString_Impl.hpp"



/**
 *
 */
Nyx::CStringRef Nyx::CString::Alloc()
{
	return new NyxOSX::CString_Impl();
}


/**
 *
 */
Nyx::CStringRef Nyx::CString::Alloc(const wchar_t* const wszText)
{
	return new NyxOSX::CString_Impl(wszText);
}


/**
 *
 */
NyxOSX::CString_Impl::CString_Impl()
{
}


/**
 *
 */
NyxOSX::CString_Impl::CString_Impl(const wchar_t* const wszText) :
m_string(wszText)
{
}


/**
 *
 */
NyxOSX::CString_Impl::~CString_Impl()
{
}


/**
 *
 */
const wchar_t* NyxOSX::CString_Impl::c_str() const
{
	return m_string.c_str();
}


/**
 *
 */
void NyxOSX::CString_Impl::Set(const wchar_t* const wszText)
{
	m_string = wszText;
}


/**
 *
 */
void NyxOSX::CString_Impl::Set(const Nyx::CString* pString)
{
	m_string = GetImpl(pString)->m_string;
}


/**
 *
 */
void NyxOSX::CString_Impl::Set(const char* const szText)
{
	m_string = L"";

	if ( NULL == szText )
		return;
		
	size_t		len = strlen(szText);
	wchar_t*	pBuffer = (wchar_t*)malloc( (len+1)*sizeof(wchar_t) );
	wchar_t*	pDst = pBuffer;
	const char*	pSrc = szText;
	
	while ( len > 0 )
	{
		*pDst = *pSrc;
		++ pDst;
		++ pSrc;
		-- len;
	}
	
	*pDst = L'\0';
	m_string = pBuffer;
	
	free(pBuffer);
}


/**
 *
 */
bool NyxOSX::CString_Impl::IsEqualTo(const wchar_t* wszText) const
{
	return m_string == wszText;
}


/**
 *
 */
bool NyxOSX::CString_Impl::IsEqualTo(const Nyx::CString* pString) const
{
	return m_string == GetImpl(pString)->m_string;
}


/**
 *
 */
bool NyxOSX::CString_Impl::IsGreaterThan(const wchar_t* wszText) const
{
	return m_string > wszText;
}


/**
 *
 */
bool NyxOSX::CString_Impl::IsGreaterThan(const Nyx::CString* pString) const
{
	return m_string > GetImpl(pString)->m_string;
}


/**
 *
 */
bool NyxOSX::CString_Impl::IsGreaterOrEqualThan(const wchar_t* wszText) const
{
	return m_string >= wszText;
}


/**
 *
 */
bool NyxOSX::CString_Impl::IsGreaterOrEqualThan(const Nyx::CString* pString) const
{
	return m_string >= GetImpl(pString)->m_string;
}


/**
 *
 */
bool NyxOSX::CString_Impl::IsLowerThan(const wchar_t* wszText) const
{
	return m_string < wszText;
}


/**
 *
 */
bool NyxOSX::CString_Impl::IsLowerThan(const Nyx::CString* pString) const
{
	return m_string < GetImpl(pString)->m_string;
}


/**
 *
 */
bool NyxOSX::CString_Impl::IsLowerOrEqualThan(const wchar_t* wszText) const
{
	return m_string <= wszText;
}


/**
 *
 */
bool NyxOSX::CString_Impl::IsLowerOrEqualThan(const Nyx::CString* pString) const
{
	return m_string <= GetImpl(pString)->m_string;
}


