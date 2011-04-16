#ifndef __NYXASTRING__HPP_
#define __NYXASTRING__HPP_

#include "NyxMFString.hpp"

namespace Nyx
{
	class CWString;
	
	/**
	 *
	 */
	class CAString : public CMFString
	{
	public:
		CAString();
		explicit CAString(size_t size);
		explicit CAString(const char* szValue);
		explicit CAString(const CMFString& rString);
		
		const char& operator [] (size_t index) const;
		char& operator [] (size_t index);

		CMFTmpString operator + (const CMFString& str) const;
		CMFTmpString operator + (const char* szValue) const;
		
		const CAString& operator = (const CMFString& str);
		const CAString& operator = (const CMFTmpString& str);
		const CAString& operator = (const CWString& str);
		const CAString& operator = (const char* szText);
		const CAString& operator = (const wchar_t* wszText);

		bool operator < (const CAString& str) const;
		
		const char* c_str() const		{ return m_Buffer.pConstChar; }

		char* BufferPtr()	{ return m_Buffer.pChar; }
	};
}


#endif // __NYXASTRING__HPP_

