#ifndef _NYXNETTCPIPSERVER_IMPL_HPP_
#define _NYXNETTCPIPSERVER_IMPL_HPP_

#include "NyxNetTcpIpServer.hpp"
#include "NyxObject_Impl.hpp"
#include "NyxThread.hpp"
#include "NyxNetTcpIpSocket.hpp"
#include "NyxTaskExecuterPool.hpp"

namespace NyxNetOSX
{
	class CTcpIpServer_Impl : public Nyx::CObject_Impl<NyxNet::CTcpIpServer>
	{
	public:
		CTcpIpServer_Impl();
		virtual ~CTcpIpServer_Impl();
		
	public:
	
		virtual Nyx::NyxResult Create(	const NyxNet::TcpIpPort& port,
										const Nyx::UInt32& MaxConnections,
										NyxNet::IConnectionHandler* pConnHandler );

		virtual Nyx::NyxResult Start();
		virtual Nyx::NyxResult Stop();
		virtual bool IsRunning() const;
        virtual NyxNet::CServerListenersRef Listeners();

	protected: // protected types
	
		enum EState
		{
			eState_Running,
			eState_Stopped
		};
        
	protected: // protected methods
	
		virtual void RunningLoop();
		virtual void StopRunningLoop();

	protected: // protected members
	
		NyxNet::TcpIpPort					m_Port;
		Nyx::UInt32							m_MaxConnections;
		Nyx::CThreadRef						m_refThread;
		EState								m_eState;
		NyxNet::CTcpIpSocketRef				m_refBoundSocket;
		NyxNet::IConnectionHandler*			m_pConnectionHandler;
		Nyx::CTaskExecuterPoolRef			m_refTaskExecuterPool;
        NyxNet::CServerListenersRef         m_refListeners;
	};
}


#endif // _NYXNETTCPIPSERVER_IMPL_HPP_
