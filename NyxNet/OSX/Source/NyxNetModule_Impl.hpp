#ifndef _NYXNETMODULE_IMPL_HPP_
#define _NYXNETMODULE_IMPL_HPP_

#include "NyxNetModule.hpp"
#include "NyxObject_Impl.hpp"
#include "NyxNetConnectionsTable_Impl.hpp"


namespace NyxNetOSX
{
	class CModule_Impl : public Nyx::CObject_Impl<NyxNet::CModule>
	{
	public:
	
		static NyxNet::CModule*		s_pDefault;
	
	public:
		CModule_Impl();
		virtual ~CModule_Impl();
		
	public:
	
		virtual Nyx::NyxResult GetHostname( Nyx::CAString& rHostname );
		virtual Nyx::NyxResult GetHostIp( const char* szComputerName, Nyx::CAString& rHostIp );
        virtual NyxNet::CConnectionsTable* GetConnectionsTable() const;
        
    protected:
        
        NyxNet::CConnectionsTableRef        m_refConnectionsTable;
	};
}


#endif // _NYXNETMODULE_IMPL_HPP_
