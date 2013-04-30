//
//  ConnStream.hpp
//  NyxWebSvr
//
//  Created by Danny Thibaudeau on 2013-04-29.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#ifndef NyxWebSvr_ConnStream_hpp
#define NyxWebSvr_ConnStream_hpp

#include <NyxNet.hpp>

namespace NyxWebSvr
{
    class CConnStream
    {
    public:
        
        virtual Nyx::NyxResult Read( void* pBuffer, const Nyx::NyxSize& sizeToRead, Nyx::NyxSize& readSize ) = 0;
        virtual Nyx::NyxResult Write( void* pBuffer, const Nyx::NyxSize& sizeToWrite, Nyx::NyxSize& writtenSize ) = 0;
        
        virtual NyxNet::CSocketRef Socket() = 0;
    };
}


#endif
