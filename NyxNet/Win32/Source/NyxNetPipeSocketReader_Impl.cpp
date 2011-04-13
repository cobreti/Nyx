#include "NyxNetPipeSocketReader_Impl.hpp"
#include "NyxNetSocketListener.hpp"


/**
 *
 */
NyxNet::CPipeSocketReaderRef NyxNet::CPipeSocketReader::Alloc()
{
	return new NyxNetWin32::CPipeSocketReader_Impl();
}



/**
 *
 */
NyxNetWin32::CPipeSocketReader_Impl::CPipeSocketReader_Impl() :
m_hPipe(INVALID_HANDLE_VALUE),
m_bConnected(false),
m_pListener(NULL)
{
	m_ahPipeEvent[0] = INVALID_HANDLE_VALUE;
	m_ahPipeEvent[1] = INVALID_HANDLE_VALUE;
}


/**
 *
 */
NyxNetWin32::CPipeSocketReader_Impl::~CPipeSocketReader_Impl()
{
	ReleaseEvents();

	if ( m_hPipe != INVALID_HANDLE_VALUE )
		CloseHandle(m_hPipe);
}


/**
 *
 */
Nyx::NyxResult NyxNetWin32::CPipeSocketReader_Impl::Create( const char* szPipename, const Nyx::NyxSize& BufferSize )
{
	Nyx::NyxResult	res = Nyx::kNyxRes_Success;

	m_Buffer.Alloc(BufferSize);

	m_refPipename = Nyx::CAnsiString::Alloc("\\\\.\\pipe\\");
	m_refPipename->Append(szPipename);

	return res;
}


/**
 *
 */
Nyx::NyxResult NyxNetWin32::CPipeSocketReader_Impl::Connect()
{
	Nyx::NyxResult	res = Nyx::kNyxRes_Success;

	m_hPipe = ::CreateNamedPipeA(
				m_refPipename->c_str(),
				PIPE_ACCESS_DUPLEX | FILE_FLAG_OVERLAPPED,
				PIPE_TYPE_BYTE,
				1,
				(DWORD)m_Buffer.Size(),
				(DWORD)m_Buffer.Size(),
				0,
				NULL );

	if (m_hPipe == INVALID_HANDLE_VALUE)
		res = Nyx::kNyxRes_Failure;

	if (m_hPipe != INVALID_HANDLE_VALUE)
	{
		CreateEvents();

		::memset(&m_PipeOverlap, 0, sizeof(OVERLAPPED));
		m_PipeOverlap.hEvent = m_ahPipeEvent[0];

		if ( ::ConnectNamedPipe(m_hPipe, &m_PipeOverlap) )
		{
			res = Nyx::kNyxRes_Failure;
		}
		else
		{
			m_bConnected = true;

			if ( NULL != m_pListener )
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
void NyxNetWin32::CPipeSocketReader_Impl::Disconnect()
{
	Nyx::NyxResult	res = Nyx::kNyxRes_Success;

	if ( m_bConnected )
	{
		DisconnectNamedPipe(m_hPipe);
		m_bConnected = false;
		SetEvent(m_ahPipeEvent[1]);

		ReleaseEvents();

		CloseHandle(m_hPipe);
		m_hPipe = INVALID_HANDLE_VALUE;

		if ( NULL != m_pListener )
			m_pListener->OnSocketDisconnected(this);
	}
}


/**
 *
 */
Nyx::NyxResult NyxNetWin32::CPipeSocketReader_Impl::Write( const void* pBuffer, const Nyx::NyxSize& DataSize, Nyx::NyxSize& WrittenSize )
{
	return Nyx::kNyxRes_Failure;
}


/**
 *
 */
Nyx::NyxResult NyxNetWin32::CPipeSocketReader_Impl::Read( void* pBuffer, const Nyx::NyxSize& DataSize, Nyx::NyxSize& ReadSize )
{
	Nyx::NyxResult	res = Nyx::kNyxRes_Failure;

	ReadSize = 0;

	BOOL		fSuccess;
	DWORD		cbRet;
	DWORD		dwErr;
	DWORD		dwWait;
	bool		bPendingIO = false;
	bool		bDataRead = false;
	DWORD		dwBytesRead;

	while ( !bDataRead && m_bConnected )
	{
		dwWait = WaitForMultipleObjects(2, m_ahPipeEvent, FALSE, INFINITE);

		if ( !bPendingIO )
		{
			fSuccess = ReadFile(m_hPipe, m_Buffer.Buffer(), (DWORD)DataSize, &dwBytesRead, &m_PipeOverlap);
		}

		dwErr = 0;
		fSuccess = GetOverlappedResult(m_ahPipeEvent[0], &m_PipeOverlap, &cbRet, FALSE);
		if ( !fSuccess )
			dwErr = GetLastError();

		bPendingIO = (dwErr == ERROR_IO_INCOMPLETE);

		if ( !bPendingIO )
		{
			if ( m_PipeOverlap.InternalHigh != 0 && m_PipeOverlap.Internal == 0 && m_bConnected )
			{
				bDataRead = true;
				res = Nyx::kNyxRes_Success;
				ReadSize = m_PipeOverlap.InternalHigh;
				memcpy(pBuffer, m_Buffer.Buffer(), ReadSize);
			}
		}
	}

	return res;
}


/**
 *
 */
void NyxNetWin32::CPipeSocketReader_Impl::SetListener( NyxNet::ISocketListener* pListener )
{
	m_pListener = pListener;
}


/**
 *
 */
void NyxNetWin32::CPipeSocketReader_Impl::CreateEvents()
{
	ReleaseEvents();

	m_ahPipeEvent[0] = ::CreateEvent(NULL, TRUE, TRUE, NULL);
	m_ahPipeEvent[1] = ::CreateEvent(NULL, TRUE, FALSE, NULL);
}


/**
 *
 */
void NyxNetWin32::CPipeSocketReader_Impl::ReleaseEvents()
{
	if ( m_ahPipeEvent[0] != INVALID_HANDLE_VALUE )
	{
		CloseHandle( m_ahPipeEvent[0] );
		m_ahPipeEvent[0] = INVALID_HANDLE_VALUE;
	}

	if ( m_ahPipeEvent[1] != INVALID_HANDLE_VALUE )
	{
		CloseHandle( m_ahPipeEvent[1] );
		m_ahPipeEvent[1] = INVALID_HANDLE_VALUE;
	}
}


