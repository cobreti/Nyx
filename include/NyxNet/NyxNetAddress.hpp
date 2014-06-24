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


        bool Empty() const
        {
            return m_Ip.length() > 0;
        }

        const CAddress& operator = (const CAddress& addr)
        {
            m_Ip = addr.m_Ip;
            m_Port = addr.m_Port;

            return *this;
        }


        bool operator == (const CAddress& addr) const
        {
            return (m_Port == addr.m_Port && m_Ip == addr.m_Ip);
        }


        bool operator != (const CAddress& addr) const
        {
            return (m_Port != addr.m_Port || m_Ip != addr.m_Ip);
        }


        bool operator < (const CAddress& addr) const
        {
            if ( m_Ip < addr.m_Ip )
            {
                return true;
            }
            else
            {
                if ( m_Port < addr.m_Port )
                {
                    return true;
                }
            }

            return false;
        }
        
        
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
