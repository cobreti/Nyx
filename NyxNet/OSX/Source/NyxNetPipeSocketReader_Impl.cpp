#include "NyxNetPipeSocketReader_Impl.hpp"
#include "NyxNetSocketListener.hpp"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


/**
 *
 */
NyxNet::CPipeSocketReaderRef NyxNet::CPipeSocketReader::Alloc()
{
	return new NyxNetOSX::CPipeSocketReader_Impl();
}


/**
 *
 */
NyxNetOSX::CPipeSocketReader_Impl::CPipeSocketReader_Impl() :
m_PipeId(-1),
m_bConnected(false),
m_pListener(NULL)
{
}


/**
 *
 */
NyxNetOSX::CPipeSocketReader_Impl::~CPipeSocketReader_Impl()
{
}


/**
 *
 */
Nyx::NyxResult NyxNetOSX::CPipeSocketReader_Impl::Create( const char* szPipename, const Nyx::NyxSize& BufferSize )
{
	Nyx::NyxResult		res = Nyx::kNyxRes_Success;
	
	m_Pipename = "/tmp/";
	m_Pipename += szPipename;
	
	m_Buffer.Alloc(BufferSize);
	
	return res;
}

/**
 *
 */
Nyx::NyxResult NyxNetOSX::CPipeSocketReader_Impl::Connect()
{
	Nyx::NyxResult		res = Nyx::kNyxRes_Success;
	int					nRet;
	
	m_Timeout.tv_sec = 1;
	m_Timeout.tv_usec = 0;
	
	nRet = mkfifo(m_Pipename.c_str(), 0666);
    if ( nRet == -1 )
    {
        remove(m_Pipename.c_str());
        nRet = mkfifo(m_Pipename.c_str(), 0666);
    }
    
	if ( nRet != -1 )
	{
		m_PipeId = open(m_Pipename.c_str(), O_RDONLY | O_NONBLOCK );
		if ( m_PipeId == -1 )
			res = Nyx::kNyxRes_Failure;
		else
		{
			m_bConnected = true;
			
			if ( m_pListener != NULL )
				m_pListener->OnSocketConnected(this);
		}
	}
	else
		res = Nyx::kNyxRes_Failure;
	
	return res;
}


/**
 *
 */
void NyxNetOSX::CPipeSocketReader_Impl::Disconnect()
{
	m_bConnected = false;

	if ( m_PipeId > 0 )
	{
		close(m_PipeId);
		m_PipeId = -1;
		remove(m_Pipename.c_str());
		
		if ( m_pListener != NULL )
			m_pListener->OnSocketDisconnected(this);
	}
}


/**
 *
 */
Nyx::NyxResult NyxNetOSX::CPipeSocketReader_Impl::Write( const void* pBuffer, const Nyx::NyxSize& DataSize, Nyx::NyxSize& WrittenSize )
{
	return Nyx::kNyxRes_Failure;
}


/**
 *
 */
Nyx::NyxResult NyxNetOSX::CPipeSocketReader_Impl::Read(	void* pBuffer, const Nyx::NyxSize& DataSize, Nyx::NyxSize& ReadSize )
{
	Nyx::NyxResult		res = Nyx::kNyxRes_Success;
	int					nRet = 0;
	fd_set				fdset;
	ssize_t				BytesRead(0);
		
	while ( m_bConnected && !(BytesRead > 0) )
	{
		FD_ZERO(&fdset);
		FD_SET(m_PipeId, &fdset);

		nRet = select(m_PipeId+1, &fdset, NULL, NULL, &m_Timeout);
		if ( nRet > 0 )
		{
			BytesRead = read(m_PipeId, m_Buffer.Buffer(), DataSize);
		}
	}
	
	if ( m_bConnected && BytesRead > 0 )
	{
		::memcpy(pBuffer, m_Buffer.Buffer(), BytesRead);
		ReadSize = BytesRead;
	}
	else 
		res = Nyx::kNyxRes_Failure;

	
	return res;
}


/**
 *
 */
void NyxNetOSX::CPipeSocketReader_Impl::SetListener( NyxNet::ISocketListener* pListener )
{
	m_pListener = pListener;
}


