#ifndef _NYXNETPIPESERVER_HPP_
#define _NYXNETPIPESERVER_HPP_

#include "NyxObject.hpp"
#include "NyxRef.hpp"
#include "NyxNetConnectionHandler.hpp"
#include "NyxNetServer.hpp"

DECLARE_NSPOBJECTREF(NyxNet, CPipeServer)

namespace NyxNet
{
	class CPipeServer : public NyxNet::CServer
	{
	public:
	
		static CPipeServerRef Alloc();
		
	public:
	
		virtual Nyx::NyxResult Create(	const char* szPipeName,
										const Nyx::NyxSize& unBufferSize,
										NyxNet::IConnectionHandler* pConnHandler ) = 0;
	};
}


#endif // _NYXNETPIPESERVER_HPP_
