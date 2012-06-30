#ifndef _NYXNETTRACESTREAMWRITER_HPP_
#define _NYXNETTRACESTREAMWRITER_HPP_

#include <Nyx.hpp>

#include "NyxObject.hpp"
#include "NyxTypes.hpp"
#include "NyxTraceHeader.hpp"
#include "NyxNetNxConnection.hpp"
#include "NyxNetTraceFlags.hpp"


namespace NyxNet
{
    /**
     *
     */
    class CTraceStreamWriter
    {
    public:
        CTraceStreamWriter();
        virtual ~CTraceStreamWriter();
        
        virtual void Init( CNxConnectionRef refConnection );
        virtual void Terminate();
        
        virtual void Write( const Nyx::CTraceHeader& header, const wchar_t* wszText );
        virtual void Write( const Nyx::CTraceHeader& header, const char* szText );
        virtual void Write( Nyx::CAString& name, const Nyx::CTraceHeader& header, const wchar_t* wszText );
        virtual void Write( Nyx::CAString& name, const Nyx::CTraceHeader& header, const char* szText );
                        
    protected:
        
        CNxConnectionRef                m_refConnection;

        static const CTraceFlags        s_BaseTraceFlags;
    };
}


#endif // _NYXNETTRACESTREAMWRITER_HPP_
