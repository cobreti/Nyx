#ifndef __NYXNETPIPESOCKETREADER_HPP_
#define __NYXNETPIPESOCKETREADER_HPP_

#include "NyxNetPipeSocket.hpp"

DECLARE_NSPOBJECTREF(NyxNet, CPipeSocketReader)

namespace NyxNet
{
	class CPipeSocketReader : public NyxNet::CPipeSocket
	{
	public:
	
		static NyxNet::CPipeSocketReaderRef Alloc();

	public:
	
		virtual Nyx::NyxResult Create( const char* szPipename, const Nyx::NyxSize& BufferSize ) = 0;
	};
}


#endif // __NYXNETPIPESOCKETREADER_HPP_
