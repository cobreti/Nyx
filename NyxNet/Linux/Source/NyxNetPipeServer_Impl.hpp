#ifndef _NYXNETPIPESERVER_IMPL_HPP_
#define _NYXNETPIPESERVER_IMPL_HPP_

#include "NyxNetPipeServer.hpp"
#include "NyxObject_Impl.hpp"
#include "NyxThread.hpp"
#include "NyxStreamRW.hpp"
#include "NyxNetPipeSocketReader.hpp"
#include "NyxNetPipeClientConn.hpp"


namespace NyxNetLinux
{
	class CPipeServer_Impl :	public virtual Nyx::CObject_Impl<NyxNet::CPipeServer>
	{
	public:
		CPipeServer_Impl();
		virtual ~CPipeServer_Impl();
		
	public:	// CPipeServer methods

		virtual Nyx::NyxResult Create(	const char* szPipeName,
										const Nyx::NyxSize& BufferSize,
										NyxNet::IConnectionHandler* pConnHandler  );
	
		virtual Nyx::NyxResult Start();
		virtual Nyx::NyxResult Stop();
		virtual bool IsRunning() const;
		virtual NyxNet::CServerListenersRef Listeners();
				
	protected:

		virtual void Thread_RunningLoop();
		virtual void Thread_Stop();
		
	protected:
	
		Nyx::CThreadRef					m_refThread;
		bool							m_bTerminate;
				
		NyxNet::IConnectionHandler*		m_pConnectionHandler;
		NyxNet::CPipeSocketReaderRef	m_refSocket;
		NyxNetLinux::CPipeClientConnRef	m_refConnection;
		NyxNet::CServerListenersRef		m_refListeners;
	};
}


#endif // _NYXNETPIPESERVER_IMPL_HPP_

