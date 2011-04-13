#include "NyxEvent_Impl.hpp"


/**
 *
 */
Nyx::CEvent* Nyx::CEvent::Alloc()
{
	return new NyxWin32::CEvent_Impl();
}


/**
 *
 */
NyxWin32::CEvent_Impl::CEvent_Impl() :
m_hEvent(NULL)
{
	m_hEvent = ::CreateEvent(NULL, FALSE, FALSE, NULL);
}


/**
 *
 */
NyxWin32::CEvent_Impl::~CEvent_Impl()
{
	::CloseHandle(m_hEvent);
}


/**
 *
 */
void NyxWin32::CEvent_Impl::Signal( const Nyx::UInt32& unFlag )
{
	::SetEvent(m_hEvent);
}


/**
 *
 */
Nyx::NyxResult NyxWin32::CEvent_Impl::WaitSignaled( const Nyx::UInt32& unTimeout )
{
	Nyx::NyxResult		res = Nyx::kNyxRes_Failure;
	DWORD				dwRet(0);

	dwRet = WaitForSingleObject(m_hEvent, unTimeout);
	switch (dwRet)
	{
		case WAIT_TIMEOUT:
			res = Nyx::kNyxRes_Success;
			break;
		case WAIT_FAILED:
			res = Nyx::kNyxRes_Failure;
			break;
		default:
			res = Nyx::kNyxRes_Success;
			break;
	};

	return res;
}


Nyx::NyxResult NyxWin32::CEvent_Impl::WaitSignaled()
{
	Nyx::NyxResult		res = Nyx::kNyxRes_Failure;
	DWORD				dwRet(0);

	dwRet = WaitForSingleObject(m_hEvent, INFINITE);
	switch (dwRet)
	{
		case WAIT_TIMEOUT:
			res = Nyx::kNyxRes_Success;
			break;
		case WAIT_FAILED:
			res = Nyx::kNyxRes_Failure;
			break;
		default:
			res = Nyx::kNyxRes_Success;
			break;
	};

	return res;
}



