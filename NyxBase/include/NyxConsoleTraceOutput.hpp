#ifndef _NYXCONSOLETRACEOUTPUT_HPP_
#define _NYXCONSOLETRACEOUTPUT_HPP_

#include "NyxTraceOutput.hpp"

DECLARE_NYXOBJECTREF(CConsoleTraceOutput);

namespace Nyx
{
	
	/**
	 *	\brief		Console trace output
	 */
	class CConsoleTraceOutput : public CTraceOutput
	{
	public:
		static CConsoleTraceOutputRef Alloc();
	};
}

#endif // _NYXCONSOLETRACEOUTPUT_HPP_
