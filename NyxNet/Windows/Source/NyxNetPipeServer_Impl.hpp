#ifndef _NYXNETPIPESERVER_IMPL_HPP_
#define _NYXNETPIPESERVER_IMPL_HPP_

#include "NyxNetPipeServer.hpp"
#include "NyxObject_Impl.hpp"
#include "NyxThread.hpp"
#include "NyxRef.hpp"
#include "NyxStreamRW.hpp"
#include "NyxAString.hpp"
#include "NyxNetPipeSocketReader.hpp"
#include "NyxNetPipeClientConn.hpp"

#include <Windows.h>

#pragma managed(push, off)

namespace NyxNetWin32
{
	class CPipeServer_Impl : public Nyx::CObject_Impl<NyxNet::CPipeServer>
	{
	public:
		CPipeServer_Impl();
		virtual ~CPipeServer_Impl();

	public:
		virtual Nyx::NyxResult Create(	const char* szPipeName,
										const Nyx::NyxSize& unBufferSize,
										NyxNet::IConnectionHandler* pConnHandler );
	
		virtual Nyx::NyxResult Start();
		virtual Nyx::NyxResult Stop();
		virtual bool IsRunning() const;
        virtual NyxNet::CServerListenersRef Listeners();

	protected:

		virtual void ThreadRunningLoop();
		virtual void ThreadStop();

	protected:
		Nyx::CThreadRef						m_refThread;
		bool								m_bTerminate;
		NyxNet::IConnectionHandler*			m_pConnectionHandler;
		NyxNet::CPipeSocketReaderRef		m_refSocket;
		NyxNetWin32::CPipeClientConnRef		m_refConnection;
        NyxNet::CServerListenersRef			m_refListeners;
	};
}

#pragma managed(pop)

#endif // _NYXNETPIPESERVER_IMPL_HPP_

