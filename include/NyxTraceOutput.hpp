#ifndef _NYXTRACEOUTPUT_HPP_
#define _NYXTRACEOUTPUT_HPP_

#include "NyxObject.hpp"
#include "NyxRef.hpp"
#include "NyxTraceHeader.hpp"

DECLARE_NYXOBJECTREF(CTraceOutput);

namespace Nyx
{
	/**
	 *	\brief		Trace output interface
	 */
	class CTraceOutput : public Nyx::CObject
	{
	public:	
		virtual void Write( const Nyx::CTraceHeader& header, const wchar_t* wszText ) = 0;
		virtual void Write( const Nyx::CTraceHeader& header, const char* szText ) = 0;
	};
}


#endif // _NYXTRACEOUTPUT_HPP_
