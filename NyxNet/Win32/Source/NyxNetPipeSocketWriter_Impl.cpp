#include "NyxNetPipeSocketWriter_Impl.hpp"
#include "NyxNetSocketListener.hpp"


/**
 *
 */
NyxNet::CPipeSocketWriterRef NyxNet::CPipeSocketWriter::Alloc()
{
	return new NyxNetWin32::CPipeSocketWriter_Impl();
}


/**
 *
 */
NyxNetWin32::CPipeSocketWriter_Impl::CPipeSocketWriter_Impl() :
m_hPipe(INVALID_HANDLE_VALUE),
m_pListener(NULL)
{
}


/**
 *
 */
NyxNetWin32::CPipeSocketWriter_Impl::~CPipeSocketWriter_Impl()
{
}


/**
 *
 */
Nyx::NyxResult NyxNetWin32::CPipeSocketWriter_Impl::Create( const char* szPipename )
{
	Nyx::NyxResult	res = Nyx::kNyxRes_Success;

	m_Pipename = "\\\\.\\pipe\\";
	m_Pipename += szPipename;

	return res;
}


/**
 *
 */
Nyx::NyxResult NyxNetWin32::CPipeSocketWriter_Impl::Connect()
{
	if ( m_hPipe != INVALID_HANDLE_VALUE )
		return Nyx::kNyxRes_Failure;

	Nyx::NyxResult			res = Nyx::kNyxRes_Success;

	m_hPipe = ::CreateFileA(	m_Pipename.c_str(),
								GENERIC_WRITE,
								0,
								NULL,
								OPEN_EXISTING,
								FILE_ATTRIBUTE_NORMAL,
								NULL );
	if ( m_hPipe == INVALID_HANDLE_VALUE )
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
void NyxNetWin32::CPipeSocketWriter_Impl::Disconnect()
{
	if ( m_hPipe != INVALID_HANDLE_VALUE )
	{
		CloseHandle(m_hPipe);
		m_hPipe = INVALID_HANDLE_VALUE;
		
		if ( m_pListener != NULL )
			m_pListener->OnSocketDisconnected(this);
	}
}


/**
 *
 */
Nyx::NyxResult NyxNetWin32::CPipeSocketWriter_Impl::Write( const void* pBuffer, const Nyx::NyxSize& DataSize, Nyx::NyxSize& WrittenSize )
{
	if ( m_hPipe == INVALID_HANDLE_VALUE )
		return Nyx::kNyxRes_Failure;

	Nyx::NyxResult			res = Nyx::kNyxRes_Failure;
	BOOL					bRet;
	DWORD					dwBytesWritten;
	
	bRet = ::WriteFile(m_hPipe, pBuffer, (DWORD)DataSize, &dwBytesWritten, NULL);

	if ( bRet )
	{
		res = Nyx::kNyxRes_Success;
		WrittenSize = dwBytesWritten;
	}

	return res;
}


/**
 *
 */
Nyx::NyxResult NyxNetWin32::CPipeSocketWriter_Impl::Read( void* pBuffer, const Nyx::NyxSize& DataSize, Nyx::NyxSize& ReadSize )
{
	return Nyx::kNyxRes_Failure;
}


/**
 *
 */
void NyxNetWin32::CPipeSocketWriter_Impl::SetListener( NyxNet::ISocketListener* pListener )
{
	m_pListener = pListener;
}


/**
 *
 */
bool NyxNetWin32::CPipeSocketWriter_Impl::Valid() const
{
    return (m_hPipe != INVALID_HANDLE_VALUE);
}


/**
 *
 */
Nyx::NyxResult NyxNetWin32::CPipeSocketWriter_Impl::Renew()
{
    return Nyx::kNyxRes_Success;
}
