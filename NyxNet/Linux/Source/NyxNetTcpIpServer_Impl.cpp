#include "NyxNetTcpIpServer_Impl.hpp"
#include "NyxBodyBlock.hpp"
#include "NyxStreamHandler.hpp"
#include "NyxNetTcpIpClientConn.hpp"
#include "NyxNetSSLTcpIpSocket.hpp"


/**
 *
 */
NyxNet::CTcpIpServerRef NyxNet::CTcpIpServer::Alloc()
{
	return new NyxNetLinux::CTcpIpServer_Impl();
}


/**
 *
 */
NyxNetLinux::CTcpIpServer_Impl::CTcpIpServer_Impl() :
m_Port(0),
m_MaxConnections(0),
m_eState(eState_Stopped),
m_pConnectionHandler(NULL),
m_bUseSSL(false)
{
	m_refListeners = new NyxNet::CServerListeners();
}


/**
 *
 */
NyxNetLinux::CTcpIpServer_Impl::~CTcpIpServer_Impl()
{
}


/**
 *
 */
Nyx::NyxResult NyxNetLinux::CTcpIpServer_Impl::Create(	const NyxNet::TcpIpPort& port,
														const Nyx::UInt32& MaxConnections,
														NyxNet::IConnectionHandler* pConnHandler )
{
	Nyx::NyxResult			res = Nyx::kNyxRes_Success;

	NyxBeginBody("CTcpIpServer creation")
	{
		m_Port = port;
		m_MaxConnections = MaxConnections;
		m_pConnectionHandler = pConnHandler;
		
        if ( m_bUseSSL )
        {
            NyxNet::CSSLTcpIpSocketRef  refSocket = NyxNet::CSSLTcpIpSocket::Alloc();
            refSocket->SetPrivKeyFile(m_privKeyFile);
            refSocket->SetPublicKeyFile(m_publicKeyFile);
            refSocket->SetDhKeyFile(m_dhKeyFile);

            m_refBoundSocket = static_cast<NyxNet::CSSLTcpIpSocket*>( (NyxNet::CTcpIpSocket*)refSocket );
        }
        else
        {
        	m_refBoundSocket = NyxNet::CTcpIpSocket::Alloc();
        }

		m_refTaskExecuterPool = Nyx::CTaskExecuterPool::Alloc();		
	}
	NyxEndBody(res)
	
	return res;
}


/**
 *
 */
Nyx::NyxResult NyxNetLinux::CTcpIpServer_Impl::Start()
{
	Nyx::NyxResult		res = Nyx::kNyxRes_Success;
	
	NyxBeginBody("Start")
	{
		m_eState = eState_Running;
		
		m_refBoundSocket->Bind(m_Port);
		Nyx::HandleErrorOnCond( Nyx::Failed(res), "failure to bind socket on desired port" );
		
		res = m_refBoundSocket->Listen(m_MaxConnections);
		Nyx::HandleErrorOnCond( Nyx::Failed(res), "failure to listen for input connection" );

		m_refThread = Nyx::CThread::Alloc();
		m_refThread->Start( new Nyx::CThreadDelegate<NyxNetLinux::CTcpIpServer_Impl>(this,
			&NyxNetLinux::CTcpIpServer_Impl::RunningLoop,
			&NyxNetLinux::CTcpIpServer_Impl::StopRunningLoop) );
	}
	NyxEndBody(res)
	
	return res;
}


/**
 *
 */
Nyx::NyxResult NyxNetLinux::CTcpIpServer_Impl::Stop()
{
	Nyx::NyxResult		res = Nyx::kNyxRes_Success;
	
	NyxBeginBody("Stop")
	{
		m_eState = eState_Stopped;
		m_refBoundSocket->Disconnect();
		m_refThread->Stop();
		m_refThread = NULL;
	}
	NyxEndBody(res)

	return res;
}


/**
 *
 */
bool NyxNetLinux::CTcpIpServer_Impl::IsRunning() const
{
	return (m_refThread.Valid() && m_refThread->IsRunning());
}


/**
 *
 */
NyxNet::CServerListenersRef NyxNetLinux::CTcpIpServer_Impl::Listeners()
{
	return m_refListeners;
}


/**
 *
 */
void NyxNetLinux::CTcpIpServer_Impl::SetUseSSL()
{
    m_bUseSSL = true;
}


/**
 *
 */
void NyxNetLinux::CTcpIpServer_Impl::SetSSLFiles( 	const Nyx::CAString& privKeyFile,
                                                	const Nyx::CAString& publicKeyFile,
                                                	const Nyx::CAString& dhFile )
{
    m_privKeyFile = privKeyFile;
    m_publicKeyFile = publicKeyFile;
    m_dhKeyFile = dhFile;
}


/**
 *
 */
void NyxNetLinux::CTcpIpServer_Impl::RunningLoop()
{
	Nyx::NyxResult			res = Nyx::kNyxRes_Success;;
	NyxNet::CTcpIpSocketRef	refConnSocket;

	NyxBeginBody("CTcpIpServer running loop")
	{
		//Nyx::CTraceStream(0x0).Write(L"starting running loop");

		m_refListeners->OnServerStarted(this);

		while ( m_eState == eState_Running )
		{
			refConnSocket = NULL;
			res = m_refBoundSocket->Accept(refConnSocket);
			
			if ( Nyx::Succeeded(res) )
			{
				NyxNet::IConnectionHandler*		pConnHandler = NULL;
				Nyx::CTaskExecuterRef			refTaskExecuter;
				NyxNetLinux::CTcpIpClientConnRef	refConnection;

				refConnection = new NyxNetLinux::CTcpIpClientConn(refConnSocket);
				
				res = m_pConnectionHandler->OnNewConnection(static_cast<NyxNet::IConnection*>(refConnection), pConnHandler);
				if ( Nyx::Succeeded(res) )
				{
					refConnection->SetConnectionHandler(pConnHandler);
					res = m_refTaskExecuterPool->Execute(refConnection);
				}

				//Nyx::CTraceStream(0x0).Write(L"succeeded in accepting a connection");
			}
			else
			{
				//Nyx::CTraceStream(0x0).Write(L"Failed to accept a connection");
			}
		}
		
		m_refListeners->OnServerStopped(this);

		Nyx::CTraceStream(0x0).Write(L"Terminating running loop");
	}
	NyxEndBody(res)
}


/**
 *
 */
void NyxNetLinux::CTcpIpServer_Impl::StopRunningLoop()
{
}

