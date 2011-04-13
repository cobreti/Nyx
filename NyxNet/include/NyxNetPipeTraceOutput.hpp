#ifndef _NYXNETPIPETRACEOUTPUT_HPP_
#define _NYXNETPIPETRACEOUTPUT_HPP_

#include "NyxTraceOutput.hpp"

DECLARE_NSPOBJECTREF(NyxNet, CPipeTraceOutput)

namespace NyxNet
{
	class CPipeTraceOutput : public Nyx::CTraceOutput
	{
	public:

		static CPipeTraceOutputRef Alloc( const char* Name );
	};
}

#endif // _NYXNETPIPETRACEOUTPUT_HPP_
