#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>


#include "NyxNetModule_Impl.hpp"
#include "NyxTraces.hpp"


/**
 *
 */
void SigPipeHandler(int);


/**
 *
 */
NyxNet::CModule*	NyxNetLinux::CModule_Impl::s_pDefault;


/**
 *
 */
NyxNet::CModuleRef NyxNet::CModule::Alloc()
{
	return new NyxNetLinux::CModule_Impl();
}


/**
 *
 */
NyxNet::CModule* NyxNet::CModule::Default()
{
	return NyxNetLinux::CModule_Impl::s_pDefault;
}


/**
 *
 */
NyxNetLinux::CModule_Impl::CModule_Impl()
{
	s_pDefault = this;
	signal(SIGPIPE, SIG_IGN);
}


/**
 *
 */
NyxNetLinux::CModule_Impl::~CModule_Impl()
{
	s_pDefault = NULL;
}


/**
 *
 */
Nyx::NyxResult NyxNetLinux::CModule_Impl::GetHostname( Nyx::CAString& rHostname )
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
Nyx::NyxResult NyxNetLinux::CModule_Impl::GetHostIp( const char* szComputerName, Nyx::CAString& rHostIp )
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
void SigPipeHandler(int)
{
	int i = 0;
}

