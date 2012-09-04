#include "NyxNetModule_Impl.hpp"
#include "NyxTraces.hpp"

#include <netdb.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

/**
 *
 */
NyxNet::CModule*	NyxNetOSX::CModule_Impl::s_pDefault;


/**
 *
 */
NyxNet::CModuleRef NyxNet::CModule::Alloc()
{
	return new NyxNetOSX::CModule_Impl();
}


/**
 *
 */
NyxNet::CModule* NyxNet::CModule::Default()
{
	return NyxNetOSX::CModule_Impl::s_pDefault;
}


/**
 *
 */
NyxNetOSX::CModule_Impl::CModule_Impl()
{
	s_pDefault = this;
    m_refConnectionsTable = new NyxNet::CConnectionsTable_Impl();
}


/**
 *
 */
NyxNetOSX::CModule_Impl::~CModule_Impl()
{
	s_pDefault = NULL;
}


/**
 *
 */
Nyx::NyxResult NyxNetOSX::CModule_Impl::GetHostname( Nyx::CAString& rHostname )
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
Nyx::NyxResult NyxNetOSX::CModule_Impl::GetHostIp( const char* szComputerName, Nyx::CAString& rHostIp )
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
NyxNet::CConnectionsTable* NyxNetOSX::CModule_Impl::GetConnectionsTable() const
{
    return m_refConnectionsTable;
}