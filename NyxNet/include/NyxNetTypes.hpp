#ifndef _NYXNETTYPES_HPP_
#define _NYXNETTYPES_HPP_

#include "NyxTypes.hpp"

namespace NyxNet
{
	typedef		Nyx::UInt32			TcpIpPort;

	typedef		Nyx::UInt32			NxDataType;

	typedef		Nyx::UInt32			NxDataSize;

	enum ENxDataType
	{
		eNxDT_Unknown				= 0x000,
		eNxDT_HandShake				= 0x001,
		eNxDT_TraceData				= 0x002,
		eNxDT_UserData				= 0x100
	};
}


#endif // _NYXNETTYPES_HPP_
