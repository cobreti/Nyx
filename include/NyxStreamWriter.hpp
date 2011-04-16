#ifndef _NYXSTREAMWRITER_HPP_
#define _NYXSTREAMWRITER_HPP_

namespace Nyx
{
	class IStreamWriter
	{
	public:
		
		/**
		 *	\brief		Writes data to a stream
		 *	\param		pBuffer : [out] address of a buffer containing the data
		 *	\param		SizeToWrite : size of the data to write (in bytes)
		 *	\param		SizeWritten : [out] size of the data actually written
		 *	\return		Nyx result value
		 */
		virtual Nyx::NyxResult Write(	void* pBuffer,
										const Nyx::NyxSize& SizeToWrite,
										Nyx::NyxSize& SizeWritten ) = 0;
	};
}


#endif // _NYXSTREAMWRITER_HPP_
