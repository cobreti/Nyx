#ifndef _NYXANSISTRING_IMPL_HPP_
#define _NYXANSISTRING_IMPL_HPP_

#include "NyxAnsiString.hpp"
#include "NyxObject_Impl.hpp"

#include <string>

namespace NyxWin32
{
	class CAnsiString_Impl : public Nyx::CObject_Impl<Nyx::CAnsiString>
	{
	public:
		CAnsiString_Impl();
		CAnsiString_Impl(const char* szText);
		virtual ~CAnsiString_Impl();
	
	public:
	
		virtual const char* c_str() const;
		virtual void Set( const char* szText );
		virtual void Set( const Nyx::CAnsiString* pString );
		virtual void Set( const wchar_t* wszText );
		virtual void Append( const char* szText );
		virtual bool IsEqualTo(const char* szText) const;
		virtual bool IsEqualTo(const Nyx::CAnsiString* pString) const;
		virtual bool IsGreaterThan(const char* szText) const;
		virtual bool IsGreaterThan(const Nyx::CAnsiString* pString) const;
		virtual bool IsGreaterOrEqualThan(const char* szText) const;
		virtual bool IsGreaterOrEqualThan(const Nyx::CAnsiString* pString) const;
		virtual bool IsLowerThan(const char* szText) const;
		virtual bool IsLowerThan(const Nyx::CAnsiString* pString) const;
		virtual bool IsLowerOrEqualThan(const char* szText) const;
		virtual bool IsLowerOrEqualThan(const Nyx::CAnsiString* pString) const;

	protected:

		const CAnsiString_Impl* GetImpl(const Nyx::CAnsiString* const pString) const
		{
			return static_cast<const CAnsiString_Impl*>(pString);
		}

	protected:
	
		std::string		m_String;
	};
}


#endif // _NYXANSISTRING_IMPL_HPP_

