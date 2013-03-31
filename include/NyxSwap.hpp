#ifndef _NYXSWAP_HPP_
#define _NYXSWAP_HPP_

#include "NyxTypes.hpp"

namespace Nyx
{
	inline
	UInt16 Swap_UInt16(UInt16 i) {
		UInt8 c1, c2;

		c1 = i & 255;
		c2 = (i >> 8) & 255;

		return (c1 << 8) + c2;
	}

	inline
	UInt32 Swap_UInt32(UInt32 i) {
		UInt8 c1, c2, c3, c4;

		c1 = i & 255;
		c2 = (i >> 8) & 255;
		c3 = (i >> 16) & 255;
		c4 = (i >> 24) & 255;

		return ((UInt32)c1 << 24) + ((UInt32)c2 << 16) + ((UInt32)c3 << 8) + c4;
	}

	inline
	UInt64 Swap_UInt64(UInt64 i) {
		UInt8 c1, c2, c3, c4, c5, c6, c7, c8;

		c1 = i & 255;
		c2 = (i >> 8) & 255;
		c3 = (i >> 16) & 255;
		c4 = (i >> 24) & 255;
		c5 = (i >> 32) & 255;
		c6 = (i >> 40) & 255;
		c7 = (i >> 48) & 255;
		c8 = (i >> 56) & 255;

		return ((UInt64)c1 << 56) +
				((UInt64)c2 << 48) +
				((UInt64)c3 << 40) +
				((UInt64)c4 << 32) +
				((UInt64)c5 << 24) +
				((UInt64)c6 << 16) +
				((UInt64)c7 << 8) +
				c8;
	}
}

#endif // _NYXSWAP_HPP_
