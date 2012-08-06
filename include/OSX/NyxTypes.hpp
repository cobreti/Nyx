#ifndef _NYXTYPES_HPP_
#define _NYXTYPES_HPP_

#include <carbon/carbon.h>

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
    
    typedef     __int64_t           Int64;
    
    typedef     __uint64_t          UInt64;
	
	/**
	 *	\brief	Message identifier
	 */
	typedef		unsigned long		MsgIdentifier;
	
	/**
	 *	\brief	trace filters
	 */
	typedef		unsigned long		TraceFilter;
    
    
    /**
     * \brief   external module handle
     */
    typedef     void*               ExternalModuleHandle;


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
