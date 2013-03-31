#include "NyxNetPipeServer_Impl.hpp"
#include "NyxThread.hpp"
#include "NyxTraces.hpp"

#pragma unmanaged

/**
 *
 */
NyxNet::CPipeServerRef NyxNet::CPipeServer::Alloc()
{
	return new NyxNetWin32::CPipeServer_Impl();
}


/**
 *
 */
NyxNetWin32::CPipeServer_Impl::CPipeServer_Impl() :
m_pConnectionHandler(NULL)
{
    m_refListeners = new NyxNet::CServerListeners();
}


/**
 *
 */
NyxNetWin32::CPipeServer_Impl::~CPipeServer_Impl()
{
}


/**
 *
 */
Nyx::NyxResult NyxNetWin32::CPipeServer_Impl::Create(	const char* szPipeName,
														const Nyx::NyxSize& unBufferSize,
														NyxNet::IConnectionHandler* pConnHandler )
{
	Nyx::NyxResult		res = Nyx::kNyxRes_Success;

	m_pConnectionHandler = pConnHandler;

	m_refSocket = NyxNet::CPipeSocketReader::Alloc();
	m_refSocket->Create(szPipeName, unBufferSize);

	m_refConnection = new NyxNetWin32::CPipeClientConn(m_refSocket);

	return res;
}


/**
 *
 */
Nyx::NyxResult NyxNetWin32::CPipeServer_Impl::Start()
{
	Nyx::NyxResult		res = Nyx::kNyxRes_Success;

	if ( !m_refThread.Valid() )
	{
		m_refThread = Nyx::CThread::Alloc();
	}

	if ( !m_refThread->IsRunning() )
	{
		m_bTerminate = false;
		m_refThread->Start( new Nyx::CThreadDelegate<CPipeServer_Impl>(this, 
			&NyxNetWin32::CPipeServer_Impl::ThreadRunningLoop, 
			&NyxNetWin32::CPipeServer_Impl::ThreadStop) );
	}

	return res;
}


/**
 *
 */
Nyx::NyxResult NyxNetWin32::CPipeServer_Impl::Stop()
{
	m_refThread->Stop();

	return Nyx::kNyxRes_Success;
}


/**
 *
 */
bool NyxNetWin32::CPipeServer_Impl::IsRunning() const
{
	return (m_refThread.Valid() && m_refThread->IsRunning());
}


/**
 *
 */
NyxNet::CServerListenersRef NyxNetWin32::CPipeServer_Impl::Listeners()
{
    return m_refListeners;
}


/**
 *
 */
void NyxNetWin32::CPipeServer_Impl::ThreadRunningLoop()
{
	NyxNet::IConnectionHandler*			pConnHandler = NULL;
	Nyx::NyxResult						res;

	m_refListeners->OnServerStarted(this);

	while (!m_bTerminate)
	{
		res = m_pConnectionHandler->OnNewConnection( static_cast<NyxNet::IConnection*>(m_refConnection), pConnHandler );
		if ( Nyx::Succeeded(res) )
		{
			m_refConnection->SetConnectionHandler(pConnHandler);
			m_refConnection->Execute();
		}
	}

	m_refListeners->OnServerStopped(this);

	Nyx::CTraceStream(0x00) << Nyx::CTF_Text(L"Connection terminated");
}


/**
 *
 */
void NyxNetWin32::CPipeServer_Impl::ThreadStop()
{
	Nyx::CTraceStream(0x00) << Nyx::CTF_Text(L"ThreadStop");
	m_bTerminate = true;
	m_refConnection->Stop();
}
