#ifndef _NYXNETTCPIPTRACEOUTPUT_HPP_
#define _NYXNETTCPIPTRACEOUTPUT_HPP_

#include "NyxTraceOutput.hpp"

DECLARE_NSPOBJECTREF(NyxNet, CTcpIpTraceOutput)

namespace NyxNet
{
	class CTcpIpTraceOutput : public Nyx::CTraceOutput
	{
	public:
        
		static CTcpIpTraceOutputRef Alloc( const char* Name, const char* addr );
	};
}

#endif // _NYXNETTCPIPTRACEOUTPUT_HPP_
