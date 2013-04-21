//
//  NyxNetAddress.hpp
//  NyxNet
//
//  Created by Danny Thibaudeau on 2013-04-21.
//
//

#ifndef NyxNet_NyxNetAddress_hpp
#define NyxNet_NyxNetAddress_hpp

#include <Nyx.hpp>
#include <NyxNetTypes.hpp>

namespace NyxNet
{
    
    
    /**
     *
     */
    class CAddress
    {
        enum
        {
            kMaxIpSize = 20
        };
        
    public:
        
        /**
         *
         */
        CAddress() :
            m_Ip(kMaxIpSize),
            m_Port(0)
        {
        }
        
        /**
         *
         */
        CAddress(const Nyx::CAString& ip, const NyxNet::TcpIpPort& port) :
            m_Ip(kMaxIpSize),
            m_Port(port)
        {
            m_Ip = ip;
        }
        
        
        /**
         *
         */
        CAddress(const CAddress& addr) :
            m_Ip(kMaxIpSize),
            m_Port(addr.m_Port)
        {
            m_Ip = addr.m_Ip;
        }
        
        
        /**
         *
         */
        ~CAddress() {}
        
        
        const Nyx::CAString&        Ip() const      { return m_Ip; }
        Nyx::CAString&              Ip()            { return m_Ip; }
        
        const NyxNet::TcpIpPort&    Port() const    { return m_Port; }
        NyxNet::TcpIpPort&          Port()          { return m_Port; }
        
        
    protected:
        
        Nyx::CAString       m_Ip;
        NyxNet::TcpIpPort   m_Port;
    };
}


#endif
