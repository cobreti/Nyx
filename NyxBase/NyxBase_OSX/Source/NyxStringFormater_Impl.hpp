#ifndef _NYXSTRINGFORMATER_IMPL_HPP_
#define _NYXSTRINGFORMATER_IMPL_HPP_

#pragma managed(push, off)

#include "NyxStringFormater.hpp"
#include "NyxObject_Impl.hpp"

namespace NyxOSX
{
	class CStringFormater_Impl : public Nyx::CObject_Impl<Nyx::CStringFormater>
	{
	public:
		CStringFormater_Impl(size_t BufferSize);
		virtual ~CStringFormater_Impl();

	public:
		virtual Nyx::NyxResult Format( const wchar_t* wszFormat, ... );
		virtual const wchar_t* GetBuffer();

	protected:

		wchar_t*		m_wszBuffer;
		size_t			m_BufferSize;
	};
};

#pragma managed(pop)

#endif // _NYXSTRINGFORMATER_IMPL_HPP_
