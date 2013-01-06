#ifndef _NYXWSTRING_HPP_
#define _NYXWSTRING_HPP_

#include "NyxMFString.hpp"
#include "NyxRange.hpp"

namespace Nyx
{
	class CAString;
	class CUtf8String;

	/**
	 *
	 */
	class CWString : public Nyx::CMFString
	{
	public:
		CWString();
		explicit CWString(size_t size);
		explicit CWString(const wchar_t* wszValue);
		explicit CWString(const CMFString& rString);
		
		const wchar_t& operator [] (size_t index) const;
		wchar_t& operator [] (size_t index);
		
		CMFTmpString operator + (const CMFString& str) const;
		CMFTmpString operator + (const wchar_t* wszValue) const;
		
		const CWString& operator = (const CMFString& str);
		const CWString& operator = (const CMFTmpString& str);
		const CWString& operator = (const CAString& str);
		const CWString& operator = (const CUtf8String& str);
		const CWString& operator = (const wchar_t* wszText);
		const CWString& operator = (const char* szText);
//		const CWString& AssignUTF8 (const char* szText);
		
		const wchar_t* c_str() const		{ return m_Buffer.pConstWChar; }
        size_t length() const;

		bool operator == (const CWString& str) const;
		bool operator != (const CWString& str) const;
		bool operator < (const CWString& str) const;
        bool operator > (const CWString& str) const;
        
        size_t CountOccurencesOf( const wchar_t& c ) const;
        void GetSplitRanges( const char delimiter, CRangesArray& ranges );
        
        CMFTmpString GetSubString( CRange range );
        
        void Format( const wchar_t* wszFormat, ... );
        void Format( const wchar_t* wszFormat, va_list args_list );
	};
}


#endif // _NYXWSTRING_HPP_
