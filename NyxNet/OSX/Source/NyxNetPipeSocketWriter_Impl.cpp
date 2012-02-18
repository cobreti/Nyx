#include "NyxNetPipeSocketWriter_Impl.hpp"
#include "NyxNetSocketListener.hpp"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


static void NyxNetOSXPipeClosed(int dummy)
{
}


/**
 *
 */
NyxNet::CPipeSocketWriterRef NyxNet::CPipeSocketWriter::Alloc()
{
	return new NyxNetOSX::CPipeSocketWriter_Impl();
}


/**
 *
 */
NyxNetOSX::CPipeSocketWriter_Impl::CPipeSocketWriter_Impl() :
m_PipeId(-1),
m_pListener(NULL)
{
}


/**
 *
 */
NyxNetOSX::CPipeSocketWriter_Impl::~CPipeSocketWriter_Impl()
{
}


/**
 *
 */
Nyx::NyxResult NyxNetOSX::CPipeSocketWriter_Impl::Create( const char* szPipename )
{
	Nyx::NyxResult		res = Nyx::kNyxRes_Success;

	signal( SIGPIPE, NyxNetOSXPipeClosed );
	
	m_Pipename = "/tmp/";
	m_Pipename += szPipename;
	
	return res;
}


/**
 *
 */
Nyx::NyxResult NyxNetOSX::CPipeSocketWriter_Impl::Connect()
{
	Nyx::NyxResult		res = Nyx::kNyxRes_Success;
	
	m_PipeId = open( m_Pipename.c_str(), O_WRONLY );
	if ( m_PipeId == -1 )
		res = Nyx::kNyxRes_Failure;
	else
	{
		if ( m_pListener != NULL )
			m_pListener->OnSocketConnected(this);
	}
	
	return res;
}


/**
 *
 */
void NyxNetOSX::CPipeSocketWriter_Impl::Disconnect()
{	
	if ( m_PipeId > 0 )
	{
		close(m_PipeId);
		m_PipeId = -1;
		
		if ( m_pListener != NULL )
			m_pListener->OnSocketDisconnected(this);
	}
}


/**
 *
 */
Nyx::NyxResult NyxNetOSX::CPipeSocketWriter_Impl::Write( const void* pBuffer, const Nyx::NyxSize& DataSize, Nyx::NyxSize& WrittenSize )
{
	Nyx::NyxResult			res = Nyx::kNyxRes_Success;
	ssize_t					BytesWritten;
	
	BytesWritten = write(m_PipeId, pBuffer, DataSize);
	if ( BytesWritten > 0 )
	{
		WrittenSize = BytesWritten;
	}
	else
		res = Nyx::kNyxRes_Failure;

	return res;
}


/**
 *
 */
Nyx::NyxResult NyxNetOSX::CPipeSocketWriter_Impl::Read(	void* pBuffer, const Nyx::NyxSize& DataSize, Nyx::NyxSize& ReadSize )
{
	return Nyx::kNyxRes_Failure;
}


/**
 *
 */
void NyxNetOSX::CPipeSocketWriter_Impl::SetListener( NyxNet::ISocketListener* pListener )
{
	m_pListener = pListener;
}


/**
 *
 */
bool NyxNetOSX::CPipeSocketWriter_Impl::Valid() const
{
    return true;
}


/**
 *
 */
Nyx::NyxResult NyxNetOSX::CPipeSocketWriter_Impl::Renew()
{
    return Nyx::kNyxRes_Success;
}


