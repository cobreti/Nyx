#ifndef _NYXMEMPOOLWSTRING_HPP_
#define _NYXMEMPOOLWSTRING_HPP_

#include <NyxWString.hpp>
#include <NyxMemPoolObj.hpp>

namespace Nyx
{
	/**
	 *
	 */
	class CMemPoolWString : public CMemPoolObj<CWString>
	{
		typedef		CMemPoolObj<CWString>		BaseType;
		
	public:
		CMemPoolWString( CMemoryPool* pPool );
		~CMemPoolWString();
		
		const CMemPoolWString& operator = (const char* szText);
		const CMemPoolWString& operator = (const wchar_t* wszText);
	};
}


#endif // _NYXMEMPOOLWSTRING_HPP_


