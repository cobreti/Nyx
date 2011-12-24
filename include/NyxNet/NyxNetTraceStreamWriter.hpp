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
        
        virtual void Init( NyxNet::CNxConnectionRef refConnection );
        virtual void Terminate();
        
        virtual void Write( const Nyx::CTraceHeader& header, const wchar_t* wszText );
        virtual void Write( const Nyx::CTraceHeader& header, const char* szText );
        
    protected:
        
        virtual NyxNet::TraceFlags TraceFlags() const;
        
    protected:
        
        NyxNet::CNxConnectionRef        m_refConnection;
        Nyx::UInt32                     m_TraceBaseFlags;
    };
}


#endif // _NYXNETTRACESTREAMWRITER_HPP_
