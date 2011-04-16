#pragma unmanaged

#include "NyxStringFormater_Impl.hpp"

#include <stdio.h>

/**
 *
 */
Nyx::CStringFormaterRef		Nyx::CStringFormater::Alloc(size_t BufferSize)
{
	return new NyxWin32::CStringFormater_Impl(BufferSize);
}


/**
 *
 */
NyxWin32::CStringFormater_Impl::CStringFormater_Impl(size_t BufferSize) :
m_wszBuffer(NULL),
m_BufferSize(0)
{
	m_wszBuffer = (wchar_t*)malloc( BufferSize * sizeof(wchar_t) );
	if ( m_wszBuffer != NULL )
	{
		m_BufferSize = BufferSize;
		m_wszBuffer[0] = L'\0';
	}
}


/**
 *
 */
NyxWin32::CStringFormater_Impl::~CStringFormater_Impl()
{
	if ( NULL != m_wszBuffer )
	{
		free(m_wszBuffer);
		m_BufferSize = 0;
	}
}


/**
 *
 */
Nyx::NyxResult NyxWin32::CStringFormater_Impl::Format( const wchar_t* wszFormat, ... )
{
	if ( m_wszBuffer == NULL || wszFormat == NULL )
		return Nyx::kNyxRes_Failure;

	const size_t		kShortFormatSize = 50;

	wchar_t*			pCur = m_wszBuffer;
	const wchar_t*		pFormat = wszFormat;
	size_t				BufferSize = m_BufferSize-1;
	wchar_t				wszShortFormat[kShortFormatSize];
	wchar_t*			pShortFormat = wszShortFormat;
	size_t				ShortFormatSize = kShortFormatSize;
	va_list				argptr;

	va_start(argptr, wszFormat);

	while ( BufferSize > 0 && *pFormat != L'\0' )
	{
		switch ( *pFormat )
		{
			case L'%':
				{
					int			AddedSize = 1;
					wchar_t		wc;

					pShortFormat = wszShortFormat;
					ShortFormatSize = kShortFormatSize-1;

					*pShortFormat = L'%';
					-- ShortFormatSize;
					++ pShortFormat;
					++ pFormat;

					do
					{
						wc = *pShortFormat = *pFormat;
						++ pFormat;
						++ pShortFormat;
						-- ShortFormatSize;
					}
					while ( iswalpha(wc) == 0 && *pFormat != L'%' && ShortFormatSize > 0 );

					*pShortFormat = L'\0';

					switch (wc)
					{
						case L'x':
						case L'X':
						case L'i':
						case L'I':
						case L'u':
						case L'U':
							AddedSize = swprintf(pCur, BufferSize, wszShortFormat, va_arg(argptr, long));
							break;

						case L'S':
							AddedSize = swprintf(pCur, BufferSize, L"%s", va_arg(argptr, wchar_t*));
							break;

						case L's':
							AddedSize = swprintf(pCur, BufferSize, L"%S", va_arg(argptr, char*));
							break;

						default:
							*pCur = L'%';
							break;
					};

					if ( AddedSize > 0 )
					{
						pCur += AddedSize;
						BufferSize -= AddedSize;
					}
					else
					{
						BufferSize = 0;
					}
				}
				break;
			default:
				*pCur = *pFormat;
				++pCur;
				--BufferSize;
				++ pFormat;
				break;
		};
	}

	*pCur = L'\0';

	return Nyx::kNyxRes_Success;
}


/**
 *
 */
const wchar_t* NyxWin32::CStringFormater_Impl::GetBuffer()
{
	return m_wszBuffer;
}
