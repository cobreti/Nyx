#include <NyxMemPoolWString.hpp>
#include <NyxAssert.hpp>

#include <string.h>

namespace Nyx
{
	/**
	 *
	 */
	CMemPoolWString::CMemPoolWString( Nyx::CMemoryPool* pPool ) :
	BaseType(pPool)
	{
	}
	
	
	/**
	 *
	 */
	CMemPoolWString::~CMemPoolWString()
	{
	}
	
	
	/**
	 *
	 */
	const CMemPoolWString& CMemPoolWString::operator = (const char* szText)
	{
		NyxAssert( m_Buffer.pData == NULL, "String buffer already allocated" );
		
		m_Flags.fFixedSize = 1;
		
		size_t		BufferSize = LenToSize(strlen(szText) + 1, sizeof(wchar_t));
		
		m_Buffer.pData = MemoryPool()->AllocMem(BufferSize);
		if ( m_Buffer.pData )
		{
			m_BufferSize = BufferSize;
			FromCharToWideChar(szText);
		}
		
		return *this;
	}
	
	
	/**
	 *
	 */
	const CMemPoolWString& CMemPoolWString::operator = (const wchar_t* wszText)
	{
		NyxAssert( m_Buffer.pData == NULL, "String buffer already allocated" );
		
		m_Flags.fFixedSize = 1;
		
		size_t		BufferSize = LenToSize(wcslen(wszText) + 1, sizeof(wchar_t));
		
		m_Buffer.pData = MemoryPool()->AllocMem(BufferSize);
		if ( m_Buffer.pData )
		{
			m_BufferSize = BufferSize;
			Set(wszText);
		}
		
		return *this;
	}


	/**
	 *
	 */
	const CMemPoolWString& CMemPoolWString::operator = (const CUtf8String& text)
	{
		NyxAssert( m_Buffer.pData == NULL, "String buffer already allocated" );

		m_Flags.fFixedSize = 1;

		size_t		BufferSize = LenToSize(text.size() + 1, sizeof(wchar_t));

		m_Buffer.pData = MemoryPool()->AllocMem(BufferSize);
		if ( m_Buffer.pData )
		{
			m_BufferSize = BufferSize;
			FromCharToWideChar(text.c_str(), "UTF-8");
		}

		return *this;
	}
}
