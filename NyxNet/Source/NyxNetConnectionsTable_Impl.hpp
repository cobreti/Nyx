#ifndef _NYXNET_CONNECTIONSTABLE_IMPL_HPP_
#define _NYXNET_CONNECTIONSTABLE_IMPL_HPP_

#include "NyxNetConnectionsTable.hpp"

#include <map>

namespace NyxNet
{
    /**
     *
     */
    class CConnectionsTable_Impl : public Nyx::CObject_Impl<NyxNet::CConnectionsTable>
    {
    public:
        CConnectionsTable_Impl();
        virtual ~CConnectionsTable_Impl();
        
        virtual NyxNet::ConnectionID Insert( NyxNet::IConnection* pConnection );
        
    public:
        
        /**
         *
         */
        class XMapConnectionData
        {
        public:
            XMapConnectionData() : m_pConnection(NULL) {}
            XMapConnectionData(IConnection* pConnection) : m_pConnection(pConnection) {}
            XMapConnectionData(const XMapConnectionData& data) : m_pConnection(data.m_pConnection) {}
            ~XMapConnectionData() {}
            
            const XMapConnectionData& operator = (const XMapConnectionData& data)
            {
                m_pConnection = data.m_pConnection;
                return *this;
            }
            
            IConnection*&       Connection()            { return m_pConnection; }
            IConnection*        Connection() const      { return m_pConnection; }
            
        private:
            IConnection*        m_pConnection;
        };
        
        typedef     std::map<ConnectionID, XMapConnectionData>      ConnectionId2DataMap;
        
    private:
        
        ConnectionID                m_NextAvailID;
        ConnectionId2DataMap        m_Connections;
    };
}


#endif // _NYXNET_CONNECTIONSTABLE_IMPL_HPP_
