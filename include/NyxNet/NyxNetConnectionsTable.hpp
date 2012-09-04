#ifndef _NYXNETCONNECTIONSTABLE_HPP_
#define _NYXNETCONNECTIONSTABLE_HPP_

#include "Nyx.hpp"
#include "NyxNetTypes.hpp"

DECLARE_NSPOBJECTREF(NyxNet, CConnectionsTable);

namespace NyxNet
{
    class IConnection;
    
    class CConnectionsTable : public Nyx::CObject
    {
    public:
        
        virtual ConnectionID Insert( IConnection* ) = 0;
    };
}


#endif // _NYXNETCONNECTIONSTABLE_HPP_
