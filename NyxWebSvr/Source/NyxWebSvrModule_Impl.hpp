//
//  NyxWebSvrModule_Imp.hpp
//  NyxWebSvr
//
//  Created by Danny Thibaudeau on 2013-04-27.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#ifndef NyxWebSvr_NyxWebSvrModule_Imp_hpp
#define NyxWebSvr_NyxWebSvrModule_Imp_hpp

#include "NyxWebSvrModule.hpp"

namespace NyxWebSvr
{
   
    /**
     *
     */
    class CModule_Impl : public Nyx::CRefCount_Impl<NyxWebSvr::CModule>
    {
    public:
        
        CModule_Impl();
        virtual ~CModule_Impl();
    };

}


#endif
