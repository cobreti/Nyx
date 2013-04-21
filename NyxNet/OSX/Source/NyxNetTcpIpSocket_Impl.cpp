#include "NyxNetTcpIpSocket_Impl.hpp"
#include "NyxNetSocketListener.hpp"

#include <sys/socket.h>
#include <sys/types.h> 
#include <netinet/in.h>
#include <arpa/inet.h>

/**
 *
 */
NyxNet::CTcpIpSocketRef NyxNet::CTcpIpSocket::Alloc()
{
	return new NyxNetOSX::CTcpIpSocket_Impl();
}


/**
 *
 */
NyxNetOSX::CTcpIpSocket_Impl::CTcpIpSocket_Impl() :
m_Socket(0),
m_Port(0),
m_pListener(NULL),
m_bValid(false)
{
	m_Socket = socket(PF_INET, SOCK_STREAM, 0);
}


/**
 *
 */
NyxNetOSX::CTcpIpSocket_Impl::CTcpIpSocket_Impl( const int& SocketValue ) :
m_Socket(SocketValue),
m_Port(0),
m_pListener(NULL),
m_bValid(true)
{
}


/**
 *
 */
NyxNetOSX::CTcpIpSocket_Impl::~CTcpIpSocket_Impl()
{
	if ( m_Socket > 0 )
		close(m_Socket);
}


/**
 *
 */
Nyx::NyxResult NyxNetOSX::CTcpIpSocket_Impl::Listen( const Nyx::UInt32& MaxPendingConnections )
{
	Nyx::NyxResult		res = Nyx::kNyxRes_Failure;
	int					nRet = 0;
	
	if ( m_Socket > 0 )
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
Nyx::NyxResult NyxNetOSX::CTcpIpSocket_Impl::Bind( const NyxNet::TcpIpPort& Port )
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
	
	return res;
}


/**
 *
 */
Nyx::NyxResult NyxNetOSX::CTcpIpSocket_Impl::Accept( NyxNet::CTcpIpSocketRef& NewSocket )
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
            NyxNetOSX::CTcpIpSocket_Impl*       pNewSocket = new NyxNetOSX::CTcpIpSocket_Impl(AcceptSocket);
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
Nyx::NyxResult NyxNetOSX::CTcpIpSocket_Impl::Connect()
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
        close(m_Socket);
        m_Socket = socket(PF_INET, SOCK_STREAM, 0);
    }

	return res;
}


/**
 *
 */
void NyxNetOSX::CTcpIpSocket_Impl::Disconnect()
{
	if ( m_Socket > 0 )
	{
        m_bValid = false;
		close(m_Socket);
		m_Socket = 0;
		
		if ( m_pListener != NULL )
			m_pListener->OnSocketDisconnected(this);
	}
}


/**
 *
 */
Nyx::NyxResult NyxNetOSX::CTcpIpSocket_Impl::Write(	const void* pBuffer, const Nyx::NyxSize& DataSize, Nyx::NyxSize& WrittenSize )
{
    if ( !m_bValid )
        return Nyx::kNyxRes_Failure;
    
	Nyx::NyxResult		res = Nyx::kNyxRes_Failure;
	ssize_t		size;
	
    size = ::write(m_Socket, pBuffer, DataSize);
    if ( size > 0 )
    {
        WrittenSize = size;
        res = Nyx::kNyxRes_Success;
    }
	
	return res;
}


Nyx::NyxResult NyxNetOSX::CTcpIpSocket_Impl::Read( void* pBuffer, const Nyx::NyxSize& DataSize, Nyx::NyxSize& ReadSize )
{
    if ( !m_bValid )
        return Nyx::kNyxRes_Failure;
    
	Nyx::NyxResult		res = Nyx::kNyxRes_Failure;
	ssize_t             size;
    ssize_t             sizeToRead = DataSize;
    char*               pByteBuffer = (char*)pBuffer;
	
    ReadSize = 0;
    
//    do
    {
        size = ::read(m_Socket, pByteBuffer, sizeToRead);
        if ( size > 0 )
        {
            ReadSize += size;
            sizeToRead -= size;
            pByteBuffer += size;
            res = Nyx::kNyxRes_Success;
        }
    }
//    while ( sizeToRead > 0 && size != 0 );
    
    if ( sizeToRead == 0 )
        res = Nyx::kNyxRes_Success;
    
	return res;
}
	

/**
 *
 */
Nyx::NyxResult NyxNetOSX::CTcpIpSocket_Impl::Create( const char* szIp, const NyxNet::TcpIpPort& Port )
{
	m_Ip = szIp;
	m_Port = Port;	
	
	return Nyx::kNyxRes_Success;
}


/**
 *
 */
void NyxNetOSX::CTcpIpSocket_Impl::SetListener( NyxNet::ISocketListener* pListener )
{
	m_pListener = pListener;
}


/**
 *
 */
bool NyxNetOSX::CTcpIpSocket_Impl::Valid() const
{
    return m_bValid;
}


/**
 *
 */
Nyx::NyxResult NyxNetOSX::CTcpIpSocket_Impl::Renew()
{
	if ( m_Socket > 0 )
    {
		close(m_Socket);
        m_Socket = 0;
    }
    
    m_Socket = socket(PF_INET, SOCK_STREAM, 0);
    
    return Nyx::kNyxRes_Success;
}
