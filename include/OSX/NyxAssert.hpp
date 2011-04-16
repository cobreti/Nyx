#include "NyxTraces.hpp"
#include <signal.h>

#if defined(_DEBUG)
	#define NyxAssert( cond, text )			if ( !(cond) )\
											{\
												Nyx::CTraceStream(0x0) << Nyx::CTF_AnsiText(text);\
												raise(SIGTRAP);\
											}
#else
	#define NyxAssert( cond, text )
#endif
