#ifndef _NYXMFSTRING_HPP_
#define _NYXMFSTRING_HPP_

#include <NyxTypes.hpp>
#include <NyxStringsFormat.hpp>

namespace Nyx
{
	class CMFStringRef;
	class CMFString;
	class CMFTmpString;
	class CAString;
	class CWString;
	
	
	/**
	 *
	 */
	union TStringBufferPtr
	{
		void*			pData;
		char*			pChar;
		wchar_t*		pWChar;
		const char*		pConstChar;
		const wchar_t*	pConstWChar;
	};

	
	/**
	 *
	 */
	struct TStringFlags
	{
		TStringFlags();
		
		void Clear();
		
		Nyx::Byte		fChar:1;
		Nyx::Byte		fWideChar:1;
		Nyx::Byte		fFixedSize:1;
		Nyx::Byte		fDynAllocated:1;
		Nyx::Byte		fMutable:1;
	};
	
	
	/**
	 *
	 */
	class CMFString
	{
		friend class CAString;
		friend class CWString;
		
	public:
		CMFString();
		explicit CMFString(const char* szValue, EStringsFormat format = kSF_Ansi);
		explicit CMFString(const wchar_t* wszValue);
		explicit CMFString(const CMFStringRef& refValue);
		explicit CMFString(const CMFString& str);
		explicit CMFString(size_t size, EStringsFormat format);
		~CMFString();
		
		const CMFString& operator = (const char* szValue);
		const CMFString& operator = (const wchar_t* wszValue);
		const CMFString& operator = (const CMFString& str);
		const CMFString& operator = (const CMFTmpString& str);
		
		const CMFString& operator += (const char* szValue);
		const CMFString& operator += (const wchar_t* wszValue);
		const CMFString& operator += (const CMFString& str);

		CMFTmpString operator + (const CMFString& str) const;
		CMFTmpString operator + (const char* szValue) const;
		CMFTmpString operator + (const wchar_t* wszCalue) const;

		bool IsWideString() const		{ return m_Flags.fWideChar; }
		bool IsAnsiString() const		{ return m_Flags.fChar; }
		
		const CAString& AString() const;
		CAString& AString();

		const CWString& WString() const;
		CWString& WString();

		size_t Size() const; // return string size in characters

		void Reserve( size_t NumberOfCharacters ); // pre-allocate the given number of characters

	protected:

		void ReleaseBuffer();
		void Resize( size_t newsize );

		void Set( const char* szValue, EStringsFormat format = kSF_Ansi  );
		void Set( const wchar_t* wszValue );
		void Set( const CMFString& str );

		void Append( const char* szValue );
		void Append( const wchar_t* wszValue );
		void Append( const CMFString& str );

		void Add( const CMFString& str, CMFString& resultStr ) const;
		void Add( const char* szValue, CMFString& resultStr ) const;
		void Add( const wchar_t* wszValue, CMFString& resultStr ) const;
		void Add( const char* szValue, size_t len, CMFString& resultStr ) const;
		void Add( const wchar_t* wszValue, size_t len, CMFString& resultStr ) const;

		void FromCharToWideChar( const char* szString );
		void FromCharToWideChar( const char* szString, char* encoding );
		void FromWideCharToChar( const wchar_t* wszString );
		
		size_t LenToSize(size_t len, size_t elem_size) const	{ return len*elem_size; }
		
		size_t BufferLen() const;
		
		bool CanResize() const	{ return !m_Flags.fFixedSize && m_Flags.fDynAllocated && m_Flags.fMutable; }
		
		bool IsSameFormat(const CMFString& str) const		{ return m_Flags.fChar == str.m_Flags.fChar && m_Flags.fWideChar == str.m_Flags.fWideChar; }

	protected:

		TStringFlags		m_Flags;
		TStringBufferPtr	m_Buffer;
		size_t				m_BufferSize;	//	in bytes
		EStringsFormat		m_Format;
	};
	
	
	/**
	 *
	 */
	class CMFStringRef
	{
		friend class CMFString;
		
	public:
		CMFStringRef(const char* szValue);
		CMFStringRef(const wchar_t* wszValue);
		
	private:
		TStringBufferPtr		m_Buffer;
		TStringFlags			m_Flags;
		EStringsFormat			m_Format;
	};
	
	
	
	/**
	 *
	 */
	class CMFTmpString : public CMFString
	{
	public:
		CMFTmpString() {};
		explicit CMFTmpString(size_t size, EStringsFormat format) : CMFString(size, format) {}
		virtual ~CMFTmpString() {};
	};
}


#endif // _NYXMFSTRING_HPP_

