#ifndef _NYXNETSERVERLISTENER_HPP_
#define _NYXNETSERVERLISTENER_HPP_

#include "Nyx.hpp"
#include "NyxObject_Impl.hpp"

#include <map>

DECLARE_NSPOBJECTREF(NyxNet, IServerListener)
DECLARE_NSPOBJECTREF(NyxNet, CServerListeners)

namespace NyxNet
{
    class CServer;
    
    /**
     *
     */
    class IServerListener : public Nyx::CObject
    {
    public:
        
        virtual void OnServerStarted( NyxNet::CServer* pServer ) = 0;
        virtual void OnServerStopped( NyxNet::CServer* pServer ) = 0;
    };
    
    
    /**
     *
     */
    class CServerListeners : public Nyx::CObject_Impl<IServerListener>
    {
    protected:
        
        typedef     std::map<IServerListener*, IServerListenerRef>    ListenersMap;
        
    public:
        CServerListeners() {}
        virtual ~CServerListeners() {}
        
        void Add( IServerListener* pListener )
        {
            if ( m_Listeners.count(pListener) == 0 )
                m_Listeners.insert( std::make_pair(pListener, pListener) );
        }
        
        void Remove( IServerListener* pListener )
        {
            ListenersMap::iterator  pos = m_Listeners.find(pListener);
            
            if ( pos != m_Listeners.end() )
                m_Listeners.erase(pos);
        }
        
        void Clear()
        {
            m_Listeners.clear();
        }
        
        virtual void OnServerStarted( NyxNet::CServer* pServer )
        {
            ListenersMap::iterator        pos = m_Listeners.begin();
            
            while ( pos != m_Listeners.end() )
            {
                pos->second->OnServerStarted(pServer);
                ++ pos;
            }
        }
        
        virtual void OnServerStopped( NyxNet::CServer* pServer )
        {
            ListenersMap::iterator        pos = m_Listeners.begin();
            
            while ( pos != m_Listeners.end() )
            {
                pos->second->OnServerStopped(pServer);
                ++ pos;
            }
        }
    
    protected:
        
        ListenersMap            m_Listeners;
    };
}


#endif // _NYXNETSERVERLISTENER_HPP_
