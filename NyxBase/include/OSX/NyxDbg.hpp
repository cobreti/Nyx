#ifndef _NYXDBG_HPP_
#define _NYXDBG_HPP_


#include <signal.h>
#include "NyxTraceStream.hpp"


#define		NYXASSERT( _cond, _msg )			if ( !(_cond) )\
												{\
													Nyx::CTraceStream(0x0).Write(L##_msg);\
													raise(SIGTRAP);\
												}
												


#endif // _NYXDBG_HPP_
