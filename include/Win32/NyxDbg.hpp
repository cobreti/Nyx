#ifndef _NYXDBG_HPP_
#define _NYXDBG_HPP_

#define NOMINMAX

#include <windows.h>
#include <assert.h>


#define		NYXASSERT( _cond, _msg )			if ( !(_cond) )\
												{\
													assert(false);\
												}
												


#endif // _NYXDBG_HPP_
