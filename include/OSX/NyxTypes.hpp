#ifndef _NYXTYPES_HPP_
#define _NYXTYPES_HPP_

#include <carbon/carbon.h>
#include <libkern/OSAtomic.h>
#include "NyxSize.hpp"

namespace Nyx
{
	typedef		u_int8_t            UInt8;
	
	typedef		int8_t				Int8;
	
	typedef		UInt8				Byte;
	
	typedef		u_int16_t           UInt16;
	
	typedef		int16_t				Int16;
	
	typedef		u_int32_t           UInt32;
	
	typedef		int32_t				Int32;
    
    typedef     u_int64_t           UInt64;
    
    typedef     int64_t             Int64;
	
	/**
	 *	\brief	Message identifier
	 */
	typedef		UInt32              MsgIdentifier;
	
	/**
	 *	\brief	trace filters
	 */
	typedef		UInt32              TraceFilter;
    
    
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
