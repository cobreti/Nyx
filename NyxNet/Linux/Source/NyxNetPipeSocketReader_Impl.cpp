#include <memory.h>

#include "NyxNetPipeSocketReader_Impl.hpp"
#include "NyxNetSocketListener.hpp"
#include <NyxTraceStream.hpp>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


/**
 *
 */
NyxNet::CPipeSocketReaderRef NyxNet::CPipeSocketReader::Alloc()
{
	return new NyxNetLinux::CPipeSocketReader_Impl();
}


/**
 *
 */
NyxNetLinux::CPipeSocketReader_Impl::CPipeSocketReader_Impl() :
m_PipeId(-1),
m_bConnected(false),
m_pListener(NULL)
{
	m_refWaitEvent = Nyx::CEvent::Alloc();
}


/**
 *
 */
NyxNetLinux::CPipeSocketReader_Impl::~CPipeSocketReader_Impl()
{
}


/**
 *
 */
Nyx::NyxResult NyxNetLinux::CPipeSocketReader_Impl::Create( const char* szPipename, const Nyx::NyxSize& BufferSize )
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
Nyx::NyxResult NyxNetLinux::CPipeSocketReader_Impl::Connect()
{
	Nyx::NyxResult		res = Nyx::kNyxRes_Success;
	int					nRet = 0;
	
	m_Timeout.tv_sec = 10;
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
void NyxNetLinux::CPipeSocketReader_Impl::Disconnect()
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
Nyx::NyxResult NyxNetLinux::CPipeSocketReader_Impl::Write( const void* pBuffer, const Nyx::NyxSize& DataSize, Nyx::NyxSize& WrittenSize )
{
	return Nyx::kNyxRes_Failure;
}


/**
 *
 */
Nyx::NyxResult NyxNetLinux::CPipeSocketReader_Impl::Read(	void* pBuffer,
														const Nyx::NyxSize& DataSize, 
														Nyx::NyxSize& ReadSize )
{
	Nyx::NyxResult		res = Nyx::kNyxRes_Success;
	int					nRet = 0;
	fd_set				fdset;
	ssize_t				BytesRead(0);

	if ( m_bConnected && m_Buffer.DataSize() >= DataSize )
	{
		ReadSize = m_Buffer.ReadData(pBuffer, DataSize);
	}
	else
	{		
		m_refWaitEvent->WaitSignaled(10);

		do
		{
            m_Timeout.tv_sec = 10;
            m_Timeout.tv_usec = 0;

            FD_ZERO(&fdset);
			FD_SET(m_PipeId, &fdset);
			BytesRead = 0;
			
			nRet = select(m_PipeId+1, &fdset, NULL, NULL, &m_Timeout);
			if ( nRet > 0 )
			{
				void*	pWritePos = m_Buffer.getWritePos();
				//Nyx::CTraceStream(0x0).Write(L"Buffer FreeSize: %i bytes", m_Buffer.FreeSize());
				BytesRead = read(m_PipeId, pWritePos, m_Buffer.FreeSize());
                if ( BytesRead > 0 )
                    m_Buffer.addDataSize(BytesRead);
				//Nyx::CTraceStream(0x0).Write(L"Read %i bytes from pipe", BytesRead);
			}
		}
		while ( m_bConnected && !(BytesRead > 0) && m_Buffer.FreeSize() > 100 );

		if ( m_bConnected && m_Buffer.DataSize() >= DataSize )
		{
			ReadSize = m_Buffer.ReadData(pBuffer, DataSize);
		}
		else
			res = Nyx::kNyxRes_Failure;
	}

	
	return res;
}


/**
 *
 */
void NyxNetLinux::CPipeSocketReader_Impl::SetListener( NyxNet::ISocketListener* pListener )
{
	m_pListener = pListener;
}


/**
 *
 */
bool NyxNetLinux::CPipeSocketReader_Impl::Valid() const
{
	return true;
}


/**
 *
 */
Nyx::NyxResult NyxNetLinux::CPipeSocketReader_Impl::Renew()
{
	return Nyx::kNyxRes_Success;
}
