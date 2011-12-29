#ifndef _NYXTYPES_HPP_
#define _NYXTYPES_HPP_

#include <stddef.h>

namespace Nyx
{
	typedef		unsigned char		UInt8;
	
	typedef		char				Int8;
	
	typedef		UInt8				Byte;
	
	typedef		unsigned short		UInt16;
	
	typedef		short				Int16;
	
	typedef		unsigned int		UInt32;
	
	typedef		int					Int32;
    
    typedef     long long           Int64;
    
    typedef     unsigned long long  UInt64;
	
	/**
	 *	\brief	Nyx size type
	 */
	typedef		size_t				NyxSize;

	/**
	 *	\brief	Message identifier
	 */
	typedef		unsigned long		MsgIdentifier;
	
	/**
	 *	\brief		trace filters
	 */
	typedef		unsigned long		TraceFilter;


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
