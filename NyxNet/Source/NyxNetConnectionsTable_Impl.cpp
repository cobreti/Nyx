
#include "NyxNetConnectionsTable_Impl.hpp"

namespace NyxNet
{
    /**
     *
     */
    CConnectionsTable_Impl::CConnectionsTable_Impl() :
    m_NextAvailID(1)
    {
        
    }
    
    
    /**
     *
     */
    CConnectionsTable_Impl::~CConnectionsTable_Impl()
    {
        
    }
    
    
    /**
     *
     */
    NyxNet::ConnectionID CConnectionsTable_Impl::Insert( NyxNet::IConnection* pConnection )
    {
        ConnectionID        id = m_NextAvailID ++;
        
        m_Connections.insert( std::make_pair(id, XMapConnectionData(pConnection)));
        
        return id;
    }
}

