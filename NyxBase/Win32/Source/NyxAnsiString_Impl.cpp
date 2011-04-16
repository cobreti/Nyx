#include "NyxAnsiString_Impl.hpp"
#include "NyxBuffer.hpp"

/**
 *
 */
Nyx::CAnsiStringRef Nyx::CAnsiString::Alloc()
{
	return new NyxWin32::CAnsiString_Impl();
}


/**
 *
 */
Nyx::CAnsiStringRef Nyx::CAnsiString::Alloc(const char* szText)
{
	return new NyxWin32::CAnsiString_Impl(szText);
}


/**
 *
 */
NyxWin32::CAnsiString_Impl::CAnsiString_Impl()
{
}


/**
 *
 */
NyxWin32::CAnsiString_Impl::CAnsiString_Impl(const char* szText) :
m_String(szText)
{
}


/**
 *
 */
NyxWin32::CAnsiString_Impl::~CAnsiString_Impl()
{
}


/**
 *
 */
const char* NyxWin32::CAnsiString_Impl::c_str() const
{
	return m_String.c_str();
}


/**
 *
 */
void NyxWin32::CAnsiString_Impl::Set(const char* szText)
{
	m_String = szText;
}


/**
 *
 */
void NyxWin32::CAnsiString_Impl::Set(const Nyx::CAnsiString* pString)
{
	m_String = GetImpl(pString)->m_String;
}


/**
 *
 */
void NyxWin32::CAnsiString_Impl::Set(const wchar_t* wszText)
{
	int					RequiredSize = 0;
	Nyx::TBuffer<char>	Buffer;
	int					SrcLen = (int)::wcslen(wszText);

	RequiredSize = WideCharToMultiByte(CP_ACP, WC_NO_BEST_FIT_CHARS, wszText, SrcLen, NULL, 0, " ", NULL);

	if ( RequiredSize > 0 )
	{
		Buffer.Alloc(RequiredSize+1);
		WideCharToMultiByte(CP_ACP, WC_NO_BEST_FIT_CHARS, wszText, SrcLen, Buffer, (int)Buffer.Size(), " ", NULL);

		Buffer[RequiredSize] = 0;
		m_String = Buffer;
	}
}


/**
 *
 */
void NyxWin32::CAnsiString_Impl::Append(const char* szText)
{
	m_String += szText;
}



/**
 *
 */
bool NyxWin32::CAnsiString_Impl::IsEqualTo( const char* szText ) const
{
	return (m_String == szText);
}


/**
 *
 */
bool NyxWin32::CAnsiString_Impl::IsEqualTo( const Nyx::CAnsiString* pString) const
{
	return (m_String == GetImpl(pString)->m_String);
}


/**
 *
 */
bool NyxWin32::CAnsiString_Impl::IsGreaterThan(const char* szText) const
{
	return (m_String > szText);
}


/**
 *
 */
bool NyxWin32::CAnsiString_Impl::IsGreaterThan(const Nyx::CAnsiString* pString) const
{
	return (m_String > GetImpl(pString)->m_String);
}


/**
 *
 */
bool NyxWin32::CAnsiString_Impl::IsGreaterOrEqualThan(const char* szText) const
{
	return (m_String >= szText);
}


/**
 *
 */
bool NyxWin32::CAnsiString_Impl::IsGreaterOrEqualThan(const Nyx::CAnsiString* pString) const
{
	return (m_String >= GetImpl(pString)->m_String);
}


/**
 *
 */
bool NyxWin32::CAnsiString_Impl::IsLowerThan(const char* szText) const
{
	return (m_String < szText);
}


/**
 *
 */
bool NyxWin32::CAnsiString_Impl::IsLowerThan(const Nyx::CAnsiString* pString) const
{
	return (m_String < GetImpl(pString)->m_String);
}


/**
 *
 */
bool NyxWin32::CAnsiString_Impl::IsLowerOrEqualThan(const char* szText) const
{
	return (m_String <= szText);
}


/**
 *
 */
bool NyxWin32::CAnsiString_Impl::IsLowerOrEqualThan(const Nyx::CAnsiString* pString) const
{
	return (m_String <= GetImpl(pString)->m_String);
}
