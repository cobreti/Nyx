//
//  NyxWebSvrModule.hpp
//  NyxWebSvr
//
//  Created by Danny Thibaudeau on 2013-04-27.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#ifndef NyxWebSvr_NyxWebSvrModule_hpp
#define NyxWebSvr_NyxWebSvrModule_hpp

#include <Nyx.hpp>


namespace NyxWebSvr
{
    DECLARE_OBJECTREF( CModule )
    
    class CModule : public Nyx::CObject
    {
    public:
        
        static CModuleRef Alloc();
        
    protected:
    };
}


#endif
