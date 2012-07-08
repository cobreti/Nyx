#include "NyxNetModule_Impl.hpp"

#include <Windows.h>
#include <winsock.h>

/**
 *
 */
NyxNet::CModule* NyxNetWin32::CModule_Impl::s_pDefault = NULL;


/**
 *
 */
NyxNet::CModuleRef NyxNet::CModule::Alloc()
{
	return new NyxNetWin32::CModule_Impl();
}


/**
 *
 */
NyxNet::CModule* NyxNet::CModule::Default()
{
	return NyxNetWin32::CModule_Impl::s_pDefault;
}


/**
 *
 */
NyxNetWin32::CModule_Impl::CModule_Impl()
{
	Init();
}


/**
 *
 */
NyxNetWin32::CModule_Impl::~CModule_Impl()
{
	Terminate();
}

/**
 *
 */
Nyx::NyxResult NyxNetWin32::CModule_Impl::GetHostname( Nyx::CAString& rHostname )
{
	const int			knHostnameSize = 200;

	Nyx::NyxResult		res = Nyx::kNyxRes_Success;
	char				szHostname[knHostnameSize];
	
	if ( gethostname(szHostname, knHostnameSize) != -1 )
	{
		rHostname = szHostname;
	}
	else
		res = Nyx::kNyxRes_Failure;

	return res;
}


/**
 *
 */
Nyx::NyxResult NyxNetWin32::CModule_Impl::GetHostIp( const char* szComputerName, Nyx::CAString& rHostIp )
{
	Nyx::NyxResult		res = Nyx::kNyxRes_Failure;
	hostent*			pHostent = NULL;			

	pHostent = gethostbyname(szComputerName);

	if ( pHostent != NULL )
	{
		char* szIp = inet_ntoa(*((struct in_addr *)pHostent->h_addr_list[0]));

		rHostIp = szIp;
		
		res = Nyx::kNyxRes_Success;
	}
	
	return res;
}


/**
 *
 */
void NyxNetWin32::CModule_Impl::Init()
{
	WORD		wVersion;
	WSADATA		wsaData;
	int			err;

	wVersion = MAKEWORD(1, 0);

	err = WSAStartup(wVersion, &wsaData);
}


/**
 *
 */
void NyxNetWin32::CModule_Impl::Terminate()
{
	WSACleanup();
}
