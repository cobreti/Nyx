#include "NyxNetTcpIpSocket_Impl.hpp"
#include "NyxNetSocketListener.hpp"
#include "NyxTraces.hpp"

#include <sys/socket.h>
#include <sys/types.h> 
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

/**
 *
 */
NyxNet::CTcpIpSocketRef NyxNet::CTcpIpSocket::Alloc()
{
	return new NyxNetLinux::CTcpIpSocket_Impl();
}


/**
 *
 */
NyxNetLinux::CTcpIpSocket_Impl::CTcpIpSocket_Impl() :
m_Socket(0),
m_Port(0),
m_pListener(NULL),
m_bValid(false)
{
	Nyx::CTraceStream(0x0) << Nyx::CTF_Text(L"CTcpIpSocket creation");

	m_Socket = socket(PF_INET, SOCK_STREAM, 0);
}


/**
 *
 */
NyxNetLinux::CTcpIpSocket_Impl::CTcpIpSocket_Impl( const int& SocketValue ) :
m_Socket(SocketValue),
m_Port(0),
m_pListener(NULL),
m_bValid(true)
{
	Nyx::CTraceStream(0x0) << Nyx::CTF_Text(L"CTcpIpSocket creation from socket value");
}


/**
 *
 */
NyxNetLinux::CTcpIpSocket_Impl::~CTcpIpSocket_Impl()
{
	Nyx::CTraceStream(0x0) << Nyx::CTF_Text(L"CTcpIpSocket destruction");

	if ( m_Socket > 0 )
		close(m_Socket);
}


/**
 *
 */
Nyx::NyxResult NyxNetLinux::CTcpIpSocket_Impl::Listen( const Nyx::UInt32& MaxPendingConnections )
{
	Nyx::NyxResult		res = Nyx::kNyxRes_Failure;
	int					nRet = 0;
	
	if ( m_Socket > 0 )
	{
		nRet = listen(m_Socket, MaxPendingConnections);
		if ( nRet != -1 )
			res = Nyx::kNyxRes_Success;
	}
	
	m_bValid = Nyx::Succeeded(res);

	return res;
}


/**
 *
 */
Nyx::NyxResult NyxNetLinux::CTcpIpSocket_Impl::Bind( const NyxNet::TcpIpPort& Port )
{
	Nyx::NyxResult		res = Nyx::kNyxRes_Failure;
	int					nRet = 0;
	sockaddr_in			BindAddr;
	
	if ( m_Socket > 0 )
	{
		BindAddr.sin_family = AF_INET;
		BindAddr.sin_addr.s_addr = INADDR_ANY;
		BindAddr.sin_port = htons(Port);
		
		nRet = bind(m_Socket, (sockaddr*) &BindAddr, sizeof(BindAddr));
		
		if ( nRet > 0 )
			res = Nyx::kNyxRes_Success;
	}
	
	m_bValid = Nyx::Succeeded(res);

	return res;
}


/**
 *
 */
Nyx::NyxResult NyxNetLinux::CTcpIpSocket_Impl::Accept( NyxNet::CTcpIpSocketRef& NewSocket )
{
	Nyx::NyxResult		res = Nyx::kNyxRes_Failure;
	sockaddr_in			client_addr;
	int					AcceptSocket;
	socklen_t			client_addr_len;
	
	if ( m_Socket > 0 )
	{
		client_addr_len = sizeof(client_addr);
		AcceptSocket = accept(m_Socket, (sockaddr*)&client_addr, &client_addr_len);
		
		if ( AcceptSocket > 0 )
		{
			NewSocket = new NyxNetLinux::CTcpIpSocket_Impl(AcceptSocket);
			res = Nyx::kNyxRes_Success;
		}
	}
	
	m_bValid = Nyx::Succeeded(res);

	return res;
}


/**
 *
 */
Nyx::NyxResult NyxNetLinux::CTcpIpSocket_Impl::Connect()
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
		m_bValid = true;
		
		if ( m_pListener != NULL )
			m_pListener->OnSocketConnected(this);
	}
	else
	{
		m_bValid = false;
	}

	return res;
}


/**
 *
 */
void NyxNetLinux::CTcpIpSocket_Impl::Disconnect()
{
	if ( m_Socket > 0 )
	{
		close(m_Socket);
		m_Socket = 0;
		
		if ( m_pListener != NULL )
			m_pListener->OnSocketDisconnected(this);

		m_bValid = false;
	}
}


/**
 *
 */
Nyx::NyxResult NyxNetLinux::CTcpIpSocket_Impl::Write(	const void* pBuffer, const Nyx::NyxSize& DataSize, Nyx::NyxSize& WrittenSize )
{
	if ( !Valid() )
	{
		WrittenSize = 0;
		return Nyx::kNyxRes_Failure;
	}

	Nyx::NyxResult		res = Nyx::kNyxRes_Failure;
	ssize_t		size;

	try
	{
		size = ::write(m_Socket, pBuffer, DataSize);
		if ( size > 0 )
		{
			WrittenSize = size;
			res = Nyx::kNyxRes_Success;
		}
	}
	catch (...)
	{
		Nyx::CTraceStream(0x0) << Nyx::CTF_Text(L"CTcpIpSocket_Impl::Write - exception");

		m_bValid = false;
		res = Nyx::kNyxRes_Failure;
	}
	
	return res;
}


Nyx::NyxResult NyxNetLinux::CTcpIpSocket_Impl::Read( void* pBuffer, const Nyx::NyxSize& DataSize, Nyx::NyxSize& ReadSize )
{
	if ( !Valid() )
	{
		ReadSize = 0;
		return Nyx::kNyxRes_Failure;
	}

	Nyx::NyxResult		res = Nyx::kNyxRes_Failure;
	ssize_t		size;
	
	size = ::read(m_Socket, pBuffer, DataSize);
	if ( size > 0 )
	{
		ReadSize = size;
		res = Nyx::kNyxRes_Success;
	}
	
	return res;
}


/**
 *
 */
Nyx::NyxResult NyxNetLinux::CTcpIpSocket_Impl::Create( const char* szIp, const NyxNet::TcpIpPort& Port )
{
	m_Ip = szIp;
	m_Port = Port;	
	
	return Nyx::kNyxRes_Success;
}


/**
 *
 */
void NyxNetLinux::CTcpIpSocket_Impl::SetListener( NyxNet::ISocketListener* pListener )
{
	m_pListener = pListener;
}


/**
 *
 */
bool NyxNetLinux::CTcpIpSocket_Impl::Valid() const
{
	return m_bValid;
}


/**
 *
 */
Nyx::NyxResult NyxNetLinux::CTcpIpSocket_Impl::Renew()
{
	if ( m_Socket > 0 )
	{
		close(m_Socket);
		m_Socket = 0;
	}

	m_Socket = socket(PF_INET, SOCK_STREAM, 0);

	return Nyx::kNyxRes_Success;
}

