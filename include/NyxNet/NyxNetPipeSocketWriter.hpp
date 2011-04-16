#ifndef _NYXNETPIPESOCKETWRITER_HPP_
#define _NYXNETPIPESOCKETWRITER_HPP_

#include "NyxNetPipeSocket.hpp"

DECLARE_NSPOBJECTREF(NyxNet, CPipeSocketWriter)

namespace NyxNet
{
	class CPipeSocketWriter : public NyxNet::CPipeSocket
	{
	public:
	
		static NyxNet::CPipeSocketWriterRef Alloc();
		
	public:
	
		virtual Nyx::NyxResult Create( const char* szPipename ) = 0;	
	};
}


#endif // _NYXNETPIPESOCKETWRITER_HPP_

