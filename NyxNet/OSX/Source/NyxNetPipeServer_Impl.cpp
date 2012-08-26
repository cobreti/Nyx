#include "NyxNetPipeServer_Impl.hpp"

#include "NyxTraces.hpp"
#include "NyxSystem.hpp"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/**
 *
 */
NyxNet::CPipeServerRef NyxNet::CPipeServer::Alloc()
{
	return new NyxNetOSX::CPipeServer_Impl();
}


/**
 *
 */
NyxNetOSX::CPipeServer_Impl::CPipeServer_Impl() :
m_bTerminate(false)
{
    m_refListeners = new NyxNet::CServerListeners();
}


/**
 *
 */
NyxNetOSX::CPipeServer_Impl::~CPipeServer_Impl()
{
	Nyx::CTraceStream(0x0) << Nyx::CTF_Text(L"CPipeServer destructor");
}


/**
 *
 */
Nyx::NyxResult NyxNetOSX::CPipeServer_Impl::Create(	const char* szPipeName,
													const Nyx::NyxSize& BufferSize,
													NyxNet::IConnectionHandler* pConnHandler )
{
	Nyx::NyxResult		res( Nyx::kNyxRes_Failure );

	m_pConnectionHandler = pConnHandler;
	
	m_refSocket = NyxNet::CPipeSocketReader::Alloc();
	m_refSocket->Create(szPipeName, BufferSize);
	
	m_refConnection = new NyxNetOSX::CPipeClientConn(m_refSocket);

	return res;
}


/**
 *
 */
Nyx::NyxResult NyxNetOSX::CPipeServer_Impl::Start()
{
	if ( !m_refThread.Valid() )
		m_refThread = Nyx::CThread::Alloc();
		
	if ( !m_refThread->IsRunning() )
	{
		m_bTerminate = false;
		m_refThread->Start(	new Nyx::CThreadDelegate<NyxNetOSX::CPipeServer_Impl>(this,
			&NyxNetOSX::CPipeServer_Impl::Thread_RunningLoop,
			&NyxNetOSX::CPipeServer_Impl::Thread_Stop) );
	}
	
	return Nyx::kNyxRes_Success;
}


/**
 *
 */
Nyx::NyxResult NyxNetOSX::CPipeServer_Impl::Stop()
{
	m_refThread->Stop();
	
	return Nyx::kNyxRes_Success;
}


/**
 *
 */
bool NyxNetOSX::CPipeServer_Impl::IsRunning() const
{
	return (m_refThread.Valid() && m_refThread->IsRunning());
}


/**
 *
 */
NyxNet::CServerListenersRef NyxNetOSX::CPipeServer_Impl::Listeners()
{
    return m_refListeners;
}


/**
 *
 */
void NyxNetOSX::CPipeServer_Impl::Thread_RunningLoop()
{
	NyxNet::IConnectionHandler*			pConnHandler = NULL;
	Nyx::NyxResult						res;

    m_refListeners->OnServerStarted(this);
    
	while ( !m_bTerminate )
	{
		res = m_pConnectionHandler->OnNewConnection(  static_cast<NyxNet::IConnection*>(m_refConnection), pConnHandler );
		
		if ( Nyx::Succeeded(res) )
		{
			m_refConnection->SetConnectionHandler(pConnHandler);
			m_refConnection->Execute();
		}
		
		/*while ( !m_bConnected && !m_bTerminate )
			Nyx::CSystem().Sleep(1000);
	
		m_pConnectionListener->OnHandleStream( static_cast<Nyx::IStreamRW&>(*this) );*/
	}
    
    m_refListeners->OnServerStopped(this);
	
	//Disconnect();
	
	Nyx::CTraceStream(0x0) << Nyx::CTF_Text(L"PipeServer - Running loop ending");
}


/**
 *
 */
void NyxNetOSX::CPipeServer_Impl::Thread_Stop()
{
	m_bTerminate = true;
	m_refConnection->Stop();
}


/**
 *
 */
/*void NyxNetOSX::CPipeServer_Impl::Connect()
{
	Nyx::NyxResult		res;
	
	res = CreatePipe();

	m_bConnected = Nyx::Succeeded(res);
}*/


/**
 *
 */
/*void NyxNetOSX::CPipeServer_Impl::Disconnect()
{
	close(m_PipeId);
	m_PipeId = 0;
	remove(m_refPipeName->CStr());
	
	m_bConnected = false;
}*/


/**
 *
 */
/*void NyxNetOSX::CPipeServer_Impl::ReleaseBuffer()
{
	if ( NULL != m_pBuffer )
	{
		free(m_pBuffer);
		m_pBuffer = NULL;
		m_BufferSize = 0;
	}
}*/


/**
 *
 */
/*Nyx::NyxResult NyxNetOSX::CPipeServer_Impl::AllocBuffer(const Nyx::NyxSize& BufferSize)
{
	Nyx::NyxResult		res = Nyx::kNyxRes_Failure;
	
	ReleaseBuffer();
	
	m_pBuffer = malloc(BufferSize);
	if ( NULL != m_pBuffer )
	{
		m_BufferSize = BufferSize;
		res = Nyx::kNyxRes_Success;
	}
	
	return res;
}*/


/**
 *
 */
/*Nyx::NyxResult NyxNetOSX::CPipeServer_Impl::CreatePipe()
{
	Nyx::NyxResult		res = Nyx::kNyxRes_Success;
	int					nRet = 0;

	m_Timeout.tv_sec = 1;
	m_Timeout.tv_usec = 0;
	
	nRet = mkfifo(m_refPipeName->CStr(), 0666);
	if ( nRet != -1 )
	{
		m_PipeId = open(m_refPipeName->CStr(), O_RDONLY | O_NONBLOCK);
		
		FD_ZERO(&m_fdset);
		FD_SET(m_PipeId, &m_fdset);

		res = Nyx::kNyxRes_Success;
	}

	return res;
}*/


