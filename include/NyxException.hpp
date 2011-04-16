#ifndef _NYXEXCEPTION_HPP_
#define _NYXEXCEPTION_HPP_

#include <exception>

namespace Nyx
{
	class CException : public std::exception
	{
	public:
		CException(const char* szMsg) throw() : m_szMsg(szMsg) {}
		virtual ~CException() throw() {};
		
		virtual const char* Msg() const { return m_szMsg; }
		
	protected:
	
		const char* m_szMsg;
	};
}



#endif // _NYXEXCEPTION_HPP_

