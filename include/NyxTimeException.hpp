#ifndef _NYXTIMEEXCEPTION_HPP_
#define _NYXTIMEEXCEPTION_HPP_

#include "NyxException.hpp"


namespace Nyx
{
	/**
	 *
	 */
	class CTimeException : public Nyx::CException
	{
	public:
		CTimeException() throw() : Nyx::CException("Attempting to use invalid time object") {}
	};
}


#endif // _NYXTIMEEXCEPTION_HPP_

