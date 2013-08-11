#define NOMINMAX

#include <Windows.h>
#include "NyxTraces.hpp"

#if defined(_DEBUG)
	#define NyxAssert( cond, text )			if ( !(cond) )\
											{\
												Nyx::CTraceStream(0x0) << Nyx::CTF_AnsiText(text);\
												DebugBreak();\
											}
#else
	#define NyxAssert( cond, text )
#endif
