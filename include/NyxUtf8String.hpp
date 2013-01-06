#ifndef __NYXUTF8STRING_HPP_
#define __NYXUTF8STRING_HPP_

#include "NyxMFString.hpp"

namespace Nyx
{
	/**
	 *
	 */
	class CUtf8String : public CMFString
	{
	public:
		CUtf8String();
		explicit CUtf8String(size_t size);
		explicit CUtf8String(const char* value);

		const CUtf8String& operator = (const char* szText);

		const char* c_str() const		{ return m_Buffer.pConstChar; }
		size_t size() const;
	};
}


#endif // __NYXUTF8STRING_HPP_
