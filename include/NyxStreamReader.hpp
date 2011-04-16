#ifndef _NYXSTREAMREADER_HPP_
#define _NYXSTREAMREADER_HPP_

#include "NyxObject.hpp"

namespace Nyx
{
	class IStreamReader
	{
	public:
		
		/**
		 *	\brief		Reads data from a stream
		 *	\param		pBuffer : [out] address of a buffer containing the data
		 *	\param		SizeToRead : size of the data to read (in bytes)
		 *	\param		SizeRead : [out] size of the data actually read
		 *	\return		Nyx result value
		 */
		virtual Nyx::NyxResult Read(	void* pBuffer,
										const Nyx::NyxSize& SizeToRead,
										Nyx::NyxSize& SizeRead ) = 0;
	};
}


#endif // _NYXSTREAMREADER_HPP_
