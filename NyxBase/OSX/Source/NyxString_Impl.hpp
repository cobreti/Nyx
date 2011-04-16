#ifndef _NYXSTRING_IMPL_HPP_
#define _NYXSTRING_IMPL_HPP_

#include "NyxString.hpp"
#include "NyxObject_Impl.hpp"

#include <string>

namespace NyxOSX
{
	class CString_Impl : public Nyx::CObject_Impl<Nyx::CString>
	{
	public:	// public functions
		CString_Impl();
		CString_Impl( const wchar_t* const szText );
		virtual ~CString_Impl();

	public: // public CString methods

		virtual const wchar_t* c_str() const;
		virtual void Set(const wchar_t* const wszText); 
		virtual void Set(const Nyx::CString* pString);
		virtual void Set(const char* const szText);
		virtual bool IsEqualTo(const wchar_t* wszText) const;
		virtual bool IsEqualTo(const Nyx::CString* pString) const;
		virtual bool IsGreaterThan(const wchar_t* wszText) const;
		virtual bool IsGreaterThan(const Nyx::CString* pString) const;
		virtual bool IsGreaterOrEqualThan(const wchar_t* wszText) const;
		virtual bool IsGreaterOrEqualThan(const Nyx::CString* pString) const;
		virtual bool IsLowerThan(const wchar_t* wszText) const;
		virtual bool IsLowerThan(const Nyx::CString* pString) const;
		virtual bool IsLowerOrEqualThan(const wchar_t* wszText) const;
		virtual bool IsLowerOrEqualThan(const Nyx::CString* pString) const;

	protected:

		const CString_Impl* GetImpl(const Nyx::CString* const pString) const
		{
			return static_cast<const CString_Impl*>(pString);
		}

	protected: // protected members

		std::wstring			m_string;
	};
}


#endif // _NYXSTRING_IMPL_HPP_
