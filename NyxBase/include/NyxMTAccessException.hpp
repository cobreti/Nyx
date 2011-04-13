#ifndef _NYXMTACCESSEXCEPTION_HPP_
#define _NYXMTACCESSEXCEPTION_HPP_

#include "NyxResException.hpp"

namespace Nyx
{
	class CMTAccessException : public Nyx::CResException
	{
	public:
		CMTAccessException(const char* szMsg) throw() :
			CResException(szMsg, kNyxRes_MTAccessDenied) {}
			
		virtual ~CMTAccessException() throw() {}
	};
};

#endif // _NYXMTACCESSEXCEPTION_HPP_
