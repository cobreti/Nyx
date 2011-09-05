#ifndef _NYXSTRINGFORMATER_HPP_
#define _NYXSTRINGFORMATER_HPP_

#include "NyxTypes.hpp"
#include "NyxObject.hpp"
#include "NyxRef.hpp"

DECLARE_NYXOBJECTREF(CStringFormater)

namespace Nyx
{
	class CStringFormater : public Nyx::CObject
	{
	public:
		
		static CStringFormaterRef Alloc(size_t BufferSize);

	public:

		virtual Nyx::NyxResult Format( const wchar_t* wszFormat, ... ) = 0;
		virtual const wchar_t* GetFormattedString() = 0;
	};
}

#endif // _NYXSTRINGFORMATER_HPP_
