#ifndef _NYXSTRING_HPP_
#define _NYXSTRING_HPP_

#include "NyxObject.hpp"
#include "NyxTypes.hpp"
#include "NyxRef.hpp"
#include "NyxStringT.hpp"

DECLARE_NYXOBJECTREF(CString)

namespace Nyx
{
	class CString : public Nyx::CObject
	{
	public:

		static CStringRef Alloc();
		static CStringRef Alloc(const wchar_t* const wszText);

	public:

		virtual const wchar_t* c_str() const = 0;
		virtual void Set(const wchar_t* const wszText) = 0;
		virtual void Set(const Nyx::CString* pString) = 0;
		virtual void Set(const char* const szText) = 0;
		virtual bool IsEqualTo(const wchar_t* wszText) const = 0;
		virtual bool IsEqualTo(const Nyx::CString* pString) const = 0;
		virtual bool IsGreaterThan(const wchar_t* wszText) const = 0;
		virtual bool IsGreaterThan(const Nyx::CString* pString) const = 0;
		virtual bool IsGreaterOrEqualThan(const wchar_t* wszText) const = 0;
		virtual bool IsGreaterOrEqualThan(const Nyx::CString* pString) const = 0;
		virtual bool IsLowerThan(const wchar_t* wszText) const = 0;
		virtual bool IsLowerThan(const Nyx::CString* pString) const = 0;
		virtual bool IsLowerOrEqualThan(const wchar_t* wszText) const = 0;
		virtual bool IsLowerOrEqualThan(const Nyx::CString* pString) const = 0;
	};


	typedef		TString<Nyx::CString, wchar_t>			CTString;
}

#endif // _NYXSTRING_HPP_
