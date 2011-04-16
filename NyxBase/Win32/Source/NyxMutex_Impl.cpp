#include "NyxMutex_Impl.hpp"


/**
 *
 */
Nyx::CMutex* Nyx::CMutex::Alloc()
{
	return new NyxWin32::CMutex_Impl();
}


/**
 *
 */
NyxWin32::CMutex_Impl::CMutex_Impl() :
m_hMutex(INVALID_HANDLE_VALUE)
{
	m_hMutex = ::CreateMutex(NULL, FALSE, NULL);
}


/**
 *
 */
NyxWin32::CMutex_Impl::~CMutex_Impl()
{
	::CloseHandle(m_hMutex);
}


/**
 *
 */
void NyxWin32::CMutex_Impl::Lock()
{
	//::WaitForSingleObject(m_hMutex, INFINITE);
	DWORD		dwRes = 0;

	do
	{
		::MsgWaitForMultipleObjects(1, &m_hMutex, FALSE, INFINITE, QS_ALLEVENTS);

		if ( dwRes != WAIT_OBJECT_0 )
		{
			MSG		msg;

			while ( ::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) )
			{
				::TranslateMessage(&msg);
				::DispatchMessage(&msg);
			}
		}
	}
	while ( dwRes != WAIT_OBJECT_0 );
}


/**
 *
 */
bool NyxWin32::CMutex_Impl::AttemptLock()
{
	bool bRes = ( WAIT_TIMEOUT != ::WaitForSingleObject(m_hMutex, 0) );

	// in case we're in a windows thread, give a change to windows messages to be processed
	MSG		msg;

	while ( ::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) )
	{
		::TranslateMessage(&msg);
		::DispatchMessage(&msg);
	}

	return bRes;
}


/**
 *
 */
void NyxWin32::CMutex_Impl::Unlock()
{
	::ReleaseMutex(m_hMutex);
}
