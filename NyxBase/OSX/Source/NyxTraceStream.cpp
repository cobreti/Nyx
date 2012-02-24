#include "NyxTraceStream.hpp"
#include "NyxTraceFeed.hpp"
#include "NyxTraceFeeds.hpp"


/**
 *
 */
class CSingleWideCharTraceFeed : public Nyx::CWideCharTraceFeed
{
public:
	CSingleWideCharTraceFeed() : Nyx::CWideCharTraceFeed(m_wszBuffer) { m_wszBuffer[0] = 0; m_wszBuffer[1] = 0; }
	virtual ~CSingleWideCharTraceFeed() {}
	
	virtual void Set( const wchar_t& c ) { m_wszBuffer[0] = c; }
	
protected:
	
	wchar_t		m_wszBuffer[2];
};



/**
 *
 */
class CSingleAnsiCharTraceFeed : public Nyx::CAnsiTraceFeed
{
public:
	CSingleAnsiCharTraceFeed() : Nyx::CAnsiTraceFeed(m_szBuffer) { m_szBuffer[0] = 0; m_szBuffer[1] = 0; }
	virtual ~CSingleAnsiCharTraceFeed() {}
	
	virtual void Set( const char& c ) { m_szBuffer[0] = c; }
	
protected:
	
	char		m_szBuffer[2];
};



/**
 *
 */
Nyx::CTraceStream& Nyx::CTraceStream::Write( const wchar_t* const wszText, ... )
{
	CSingleWideCharTraceFeed			CharFeed;
	va_list								arg_ptr;
	const wchar_t*						pC = wszText;
	
	va_start( arg_ptr, wszText );

	while ( *pC != L'\0' )
	{
		if ( *pC == L'%' )
		{
			++ pC;
			
			switch (*pC)
			{
				case L'X':
				case L'x':
				{
					long	hexvalue = va_arg(arg_ptr, long);
					operator << ( Nyx::CTF_Hex(hexvalue) );
				}
				break;
				
				case L'I':
				case L'i':
				{
					Nyx::Int32	value = va_arg(arg_ptr, Nyx::Int32);
					operator << ( Nyx::CTF_Int(value) );
				}
				break;
                    
                case L'f':
                {
                    double value = va_arg(arg_ptr, double);
                    operator << ( Nyx::CTF_Float(value) );
                }
                break;

				case L'%':
					CharFeed.Set(*pC);
					operator << (CharFeed);
					break;					
			};

			++ pC;
		}
		else
		{
			CharFeed.Set(*pC);
			operator << (CharFeed);
			 ++ pC;
		}
	}
	
	va_end( arg_ptr );
	
	return *this;
}


/**
 *
 */
Nyx::CTraceStream& Nyx::CTraceStream::Write( const char* const szText, ... )
{
	if ( m_pTrace == NULL )
		return *this;
	
	CSingleAnsiCharTraceFeed			CharFeed;
	va_list								arg_ptr;
	const char*							pC = szText;
	
	va_start( arg_ptr, szText );
	
	while ( *pC != '\0' )
	{
		if ( *pC == '%' )
		{
			++ pC;
			
			switch (*pC)
			{
				case 'X':
				case 'x':
				{
					long	hexvalue = va_arg(arg_ptr, long);
					operator << ( Nyx::CTF_Hex(hexvalue) );
				}
					break;
					
				case 'I':
				case 'i':
				{
					Nyx::Int32	value = va_arg(arg_ptr, Nyx::Int32);
					operator << ( Nyx::CTF_Int(value) );
				}
					break;
					
				case 'f':
				{
					double	value = va_arg(arg_ptr, double);
					operator << ( Nyx::CTF_Float(value) );
				}
					break;
					
				case '%':
					CharFeed.Set(*pC);
					operator << (CharFeed);
					break;					
			};
			
			++ pC;
		}
		else
		{		
			CharFeed.Set(*pC);
			operator << (CharFeed);
			++ pC;
		}
	}
	
	va_end( arg_ptr );
	
	return *this;
}

