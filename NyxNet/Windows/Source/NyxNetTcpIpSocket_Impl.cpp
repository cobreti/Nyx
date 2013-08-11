#include <winsock2.h>
#include <Ws2tcpip.h>

#include "NyxNetTcpIpSocket_Impl.hpp"
#include "NyxNetSocketListener.hpp"

//#include <Windows.h>

/**
 *
 */
NyxNet::CTcpIpSocketRef NyxNet::CTcpIpSocket::Alloc()
{
	return new NyxNet::CTcpIpSocket_Impl();
}


/**
 *
 */
NyxNet::CTcpIpSocket_Impl::CTcpIpSocket_Impl() :
m_Socket(INVALID_SOCKET),
m_Port(0),
m_pListener(NULL),
m_bValid(false)
{
	m_Socket = socket(PF_INET, SOCK_STREAM, 0);
}


/**
 *
 */
NyxNet::CTcpIpSocket_Impl::CTcpIpSocket_Impl( const SOCKET& SocketValue ) :
m_Socket(SocketValue),
m_Port(0),
m_pListener(NULL),
m_bValid(true)
{
}


/**
 *
 */
NyxNet::CTcpIpSocket_Impl::~CTcpIpSocket_Impl()
{
	if ( m_Socket != INVALID_SOCKET )
		closesocket(m_Socket);
}


/**
 *
 */
Nyx::NyxResult NyxNet::CTcpIpSocket_Impl::Listen( const Nyx::UInt32& MaxPendingConnections )
{
	Nyx::NyxResult		res = Nyx::kNyxRes_Failure;
	int					nRet = 0;
	
	if ( m_Socket != INVALID_SOCKET )
	{
		nRet = listen(m_Socket, MaxPendingConnections);
		if ( nRet != -1 )
			res = Nyx::kNyxRes_Success;
	}
	
	return res;
}


/**
 *
 */
Nyx::NyxResult NyxNet::CTcpIpSocket_Impl::Bind( const NyxNet::TcpIpPort& Port )
{
	Nyx::NyxResult		res = Nyx::kNyxRes_Failure;
	int					nRet = 0;
	sockaddr_in			BindAddr;
	
	if ( m_Socket != INVALID_SOCKET )
	{
		BindAddr.sin_family = AF_INET;
		BindAddr.sin_addr.s_addr = INADDR_ANY;
		BindAddr.sin_port = htons(Port);
		
		nRet = bind(m_Socket, (sockaddr*) &BindAddr, sizeof(BindAddr));
		
		if ( nRet > 0 )
			res = Nyx::kNyxRes_Success;
	}
	
	return res;
}


/**
 *
 */
Nyx::NyxResult NyxNet::CTcpIpSocket_Impl::Accept( NyxNet::CTcpIpSocketRef& NewSocket )
{
	Nyx::NyxResult		res = Nyx::kNyxRes_Failure;
	sockaddr_in			client_addr;
	SOCKET				AcceptSocket;
	int					client_addr_len;
	
	if ( m_Socket != INVALID_SOCKET )
	{
		client_addr_len = sizeof(client_addr);
		AcceptSocket = accept(m_Socket, (sockaddr*)&client_addr, &client_addr_len);
		
		if ( AcceptSocket != INVALID_SOCKET )
		{
			//NewSocket = new NyxNet::CTcpIpSocket_Impl(AcceptSocket);
			//res = Nyx::kNyxRes_Success;
            NyxNet::CTcpIpSocket_Impl*       pNewSocket = new NyxNet::CTcpIpSocket_Impl(AcceptSocket);
            inet_ntop( AF_INET, &client_addr.sin_addr.s_addr,
                      pNewSocket->m_ClientAddress.Ip().BufferPtr(), pNewSocket->m_ClientAddress.Ip().Size());
            pNewSocket->m_ClientAddress.Port() = ntohs(client_addr.sin_port);

			NewSocket = pNewSocket;
			res = Nyx::kNyxRes_Success;
		}
	}
	
	return res;
}


/**
 *
 */
Nyx::NyxResult NyxNet::CTcpIpSocket_Impl::Create( const char* szIp, const NyxNet::TcpIpPort& Port )
{
	m_Ip = szIp;
	m_Port = Port;

	return Nyx::kNyxRes_Success;
}


/**
 *
 */
Nyx::NyxResult NyxNet::CTcpIpSocket_Impl::Connect()
{
	Nyx::NyxResult			res = Nyx::kNyxRes_Failure;
	sockaddr_in				serv_addr;
	int						nRet = 0;
	
    serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(m_Ip.c_str());
	serv_addr.sin_port = htons(m_Port);
    nRet = connect(m_Socket, (sockaddr*)&serv_addr,sizeof(serv_addr));
	if ( nRet >= 0 )
	{
		res = Nyx::kNyxRes_Success;

		if ( NULL != m_pListener )
			m_pListener->OnSocketConnected(this);
	} 

	return res;
}


/**
 *
 */
void NyxNet::CTcpIpSocket_Impl::Disconnect()
{
	if ( m_Socket != INVALID_SOCKET )
	{
		closesocket(m_Socket);
		m_Socket = INVALID_SOCKET;

		if ( m_pListener != NULL )
			m_pListener->OnSocketDisconnected(this);
	}
}


/**
 *
 */
Nyx::NyxResult NyxNet::CTcpIpSocket_Impl::Write(	const void* pBuffer, const Nyx::NyxSize& DataSize, Nyx::NyxSize& WrittenSize )
{
	Nyx::NyxResult		res = Nyx::kNyxRes_Failure;
	int					nRet(0);
		
	nRet = send(m_Socket, (const char*)pBuffer, (int)DataSize, 0);
	if ( nRet > 0 )
	{
		WrittenSize = nRet;
		res = Nyx::kNyxRes_Success;
	}
	
	return res;
}


Nyx::NyxResult NyxNet::CTcpIpSocket_Impl::Read( void* pBuffer, const Nyx::NyxSize& DataSize, Nyx::NyxSize& ReadSize )
{
	Nyx::NyxResult		res = Nyx::kNyxRes_Failure;
	int					nRet(0);
	
	nRet = recv(m_Socket, (char*)pBuffer, (int)DataSize, 0);
	if ( nRet > 0 )
	{
		ReadSize = nRet;
		res = Nyx::kNyxRes_Success;
	}
	
	return res;
}


/**
 *
 */
void NyxNet::CTcpIpSocket_Impl::SetListener( NyxNet::ISocketListener* pListener )
{
	m_pListener = pListener;
}


/**
 *
 */
bool NyxNet::CTcpIpSocket_Impl::Valid() const
{
    return (m_Socket != INVALID_SOCKET);
}


/**
 *
 */
Nyx::NyxResult NyxNet::CTcpIpSocket_Impl::Renew()
{
	if ( m_Socket > 0 )
	{
		closesocket(m_Socket);
		m_Socket = 0;
	}

	m_Socket = socket(PF_INET, SOCK_STREAM, 0);

    return Nyx::kNyxRes_Success;
}
