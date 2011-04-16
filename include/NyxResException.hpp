#ifndef _NYXRESEXCEPTION_HPP_
#define _NYXRESEXCEPTION_HPP_

#include "NyxException.hpp"
#include "NyxTypes.hpp"

namespace Nyx
{
	class CResException : public Nyx::CException
	{
	public:
		CResException(const char* szMsg, const Nyx::NyxResult& result) throw() :
			CException(szMsg),
			m_Result(result) {}
			
		virtual ~CResException() throw() {}
		
		const Nyx::NyxResult& Result() const { return m_Result; }
	
	protected:
		Nyx::NyxResult		m_Result;
	};
}


#endif // _NYXRESEXCEPTION_HPP_
