#ifndef _NYXSTRINGT_HPP_
#define _NYXSTRINGT_HPP_


namespace Nyx
{
	/**
	 *
	 */
	template <class STRINGCLASS, typename CHARTYPE>
	class TString
	{
	public:
		TString()
		{
			m_String = STRINGCLASS::Alloc();
		}
		
		TString( const CHARTYPE* str )
		{
			m_String = STRINGCLASS::Alloc(str);
		}
		
		TString( const TString& str )
		{
			m_String = STRINGCLASS::Alloc( str.m_String->c_str() );
		}

		TString( const STRINGCLASS* pStr )
		{
			m_String = STRINGCLASS::Alloc(pStr->c_str());
		}
		
		~TString() {}

		const TString& operator = ( const STRINGCLASS* pStr )
		{
			m_String->Set( pStr->c_str() );
			return *this;
		}
		
		const TString& operator = (const TString& str)
		{
			m_String->Set( str.m_String->c_str() );
			return *this;
		}

		const TString& operator = ( const CHARTYPE* str )
		{
			m_String->Set(str);
			return *this;
		}

		bool operator == ( const CHARTYPE* text ) const			{ return (m_String->IsEqualTo(text)); }
		bool operator == ( const TString& str ) const			{ return (m_String->IsEqualTo(str.m_String)); }
		bool operator < ( const CHARTYPE* text ) const			{ return (m_String->IsLowerThan(text));	}
		bool operator < ( const TString& str ) const			{ return (m_String->IsLowerThan(str.m_String));	}
		bool operator <= ( const CHARTYPE* text ) const			{ return (m_String->IsLowerOrEqualThan(text)); }
		bool operator <= ( const TString& str ) const			{ return (m_String->IsLowerOrEqualThan(str.m_String)); }
		bool operator > ( const CHARTYPE* text ) const			{ return (m_String->IsGreaterThan(text)); }
		bool operator > ( const TString& str ) const			{ return (m_String->IsGreaterThan(str.m_String)); }
		bool operator >= ( const CHARTYPE* text ) const			{ return (m_String->IsGreaterOrEqualThan(text)); }
		bool operator >= ( const TString& str ) const			{ return (m_String->IsGreaterOrEqualThan(str.m_String)); }

		operator const CHARTYPE* () const { return m_String->c_str(); }
		operator STRINGCLASS* () { return m_String; }
		operator const STRINGCLASS* () const { return m_String; }
		
		const CHARTYPE* c_str() const { return m_String->c_str(); }
		
		virtual void Set(const wchar_t* const wszText) { m_String->Set(wszText); }
		virtual void Set(const char* const szText) { m_String->Set(szText); }

	protected:

		Nyx::CRef<STRINGCLASS>			m_String;
	};

};




#endif // _NYXSTRINGT_HPP_
