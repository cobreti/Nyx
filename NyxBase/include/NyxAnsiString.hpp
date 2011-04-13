#ifndef _NYXANSISTRING_HPP_
#define _NYXANSISTRING_HPP_

#include "NyxObject.hpp"
#include "NyxRef.hpp"
#include "NyxStringT.hpp"

DECLARE_NYXOBJECTREF(CAnsiString)

namespace Nyx
{
	class CAnsiString : public Nyx::CObject
	{
	public:
	
		static CAnsiStringRef Alloc();
		static CAnsiStringRef Alloc(const char* szText);
		
	public:
		
		virtual const char* c_str() const = 0;
		virtual void Set( const char* szText ) = 0;
		virtual void Set( const CAnsiString* pString ) = 0;
		virtual void Set( const wchar_t* wszText ) = 0;
		virtual void Append( const char* szText ) = 0;
		virtual bool IsEqualTo(const char* szText) const = 0;
		virtual bool IsEqualTo(const Nyx::CAnsiString* pString) const = 0;
		virtual bool IsGreaterThan(const char* szText) const = 0;
		virtual bool IsGreaterThan(const Nyx::CAnsiString* pString) const = 0;
		virtual bool IsGreaterOrEqualThan(const char* szText) const = 0;
		virtual bool IsGreaterOrEqualThan(const Nyx::CAnsiString* pString) const = 0;
		virtual bool IsLowerThan(const char* szText) const = 0;
		virtual bool IsLowerThan(const Nyx::CAnsiString* pString) const = 0;
		virtual bool IsLowerOrEqualThan(const char* szText) const = 0;
		virtual bool IsLowerOrEqualThan(const Nyx::CAnsiString* pString) const = 0;
	};

	typedef		TString<Nyx::CAnsiString, char>			CTAnsiString;
}


#endif // _NYXANSISTRING_HPP_

