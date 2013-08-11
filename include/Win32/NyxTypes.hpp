#ifndef _NYXTYPES_HPP_
#define _NYXTYPES_HPP_

#define NOMINMAX

#include <sys/types.h>
#include <windows.h>

#include "NyxSize.hpp"

namespace Nyx
{
	typedef		unsigned char		UInt8;
	
	typedef		char				Int8;

	typedef		UInt8				Byte;
	
	typedef		unsigned short		UInt16;
	
	typedef		short				Int16;
	
	typedef		unsigned int		UInt32;
	
	typedef		int					Int32;

    typedef     __int64             Int64;

    typedef     unsigned __int64    UInt64;

	typedef		unsigned long		MsgIdentifier;
	
	/**
	 *	\brief		trace filters
	 */
	typedef		unsigned long		TraceFilter;

    /**
     *  \brief      external module handle
     */
    typedef     HMODULE             ExternalModuleHandle;


	typedef enum
	{
		kNyxRes_Success = 0x00000000,
		
		kNyxRes_Failure = 0x80000000,

		kNyxRes_InvalidArgs = kNyxRes_Failure | 0x0001,

		kNyxRes_MTAccessDenied = kNyxRes_Failure | 0x0002

	} NyxResult;
	

	
	inline bool Failed(const NyxResult& result)
	{
		return (kNyxRes_Failure == (result & kNyxRes_Failure));
	}

	
	inline bool Succeeded(const NyxResult& result)
	{
		return (0 == (result & kNyxRes_Failure));
	}
};



#endif // _NYXTYPES_HPP_
