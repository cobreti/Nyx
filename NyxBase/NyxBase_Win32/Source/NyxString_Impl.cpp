#include "NyxString_Impl.hpp"
#include "NyxBuffer.hpp"



/**
 *
 */
Nyx::CStringRef Nyx::CString::Alloc()
{
	return new NyxWin32::CString_Impl();
}


/**
 *
 */
Nyx::CStringRef Nyx::CString::Alloc(const wchar_t* const wszText)
{
	return new NyxWin32::CString_Impl(wszText);
}


/**
 *
 */
NyxWin32::CString_Impl::CString_Impl()
{
}


/**
 *
 */
NyxWin32::CString_Impl::CString_Impl(const wchar_t* wszText) :
m_string(wszText)
{
}


/**
 *
 */
NyxWin32::CString_Impl::~CString_Impl()
{
}


/**
 *
 */
const wchar_t* NyxWin32::CString_Impl::c_str() const
{
	return m_string.c_str();
}


/**
 *
 */
void NyxWin32::CString_Impl::Set(const wchar_t* const wszText)
{
	m_string = wszText;
}


/**
 *
 */
void NyxWin32::CString_Impl::Set(const Nyx::CString* const pString)
{
	m_string = GetImpl(pString)->m_string;
}


/**
 *
 */
void NyxWin32::CString_Impl::Set(const char* const szText)
{
	int						nRequiredSize = 0;
	int						nLen = (int)strlen(szText);
	Nyx::TBuffer<wchar_t>	Buffer;

	nRequiredSize = MultiByteToWideChar(CP_ACP, MB_COMPOSITE, szText, nLen, NULL, 0);

	if ( nRequiredSize > 0 )
	{
		Buffer.Alloc(nRequiredSize+1);

		MultiByteToWideChar(CP_ACP, MB_COMPOSITE, szText, nLen, Buffer, (int)Buffer.Size());

		Buffer[nRequiredSize] = 0;
		m_string = Buffer;
	}
}


/**
 *
 */
bool NyxWin32::CString_Impl::IsEqualTo( const wchar_t* wszText ) const
{
	return (m_string == wszText);
}


/**
 *
 */
bool NyxWin32::CString_Impl::IsEqualTo( const Nyx::CString* pString) const
{
	return (m_string == GetImpl(pString)->m_string);
}


/**
 *
 */
bool NyxWin32::CString_Impl::IsGreaterThan(const wchar_t* wszText) const
{
	return (m_string > wszText);
}


/**
 *
 */
bool NyxWin32::CString_Impl::IsGreaterThan(const Nyx::CString* pString) const
{
	return (m_string > GetImpl(pString)->m_string);
}


/**
 *
 */
bool NyxWin32::CString_Impl::IsGreaterOrEqualThan(const wchar_t* wszText) const
{
	return (m_string >= wszText);
}


/**
 *
 */
bool NyxWin32::CString_Impl::IsGreaterOrEqualThan(const Nyx::CString* pString) const
{
	return (m_string >= GetImpl(pString)->m_string);
}


/**
 *
 */
bool NyxWin32::CString_Impl::IsLowerThan(const wchar_t* wszText) const
{
	return (m_string < wszText);
}


/**
 *
 */
bool NyxWin32::CString_Impl::IsLowerThan(const Nyx::CString* pString) const
{
	return (m_string < GetImpl(pString)->m_string);
}


/**
 *
 */
bool NyxWin32::CString_Impl::IsLowerOrEqualThan(const wchar_t* wszText) const
{
	return (m_string <= wszText);
}


/**
 *
 */
bool NyxWin32::CString_Impl::IsLowerOrEqualThan(const Nyx::CString* pString) const
{
	return (m_string <= GetImpl(pString)->m_string);
}


