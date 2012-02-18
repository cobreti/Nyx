#include "NyxNetTraceStreamWriter.hpp"
#include "NyxNetNxStreamRW.hpp"
#include "NyxNetTraceFlags.hpp"


namespace NyxNet
{
    const CTraceFlags       CTraceStreamWriter::s_BaseTraceFlags;

    /**
     *
     */
    CTraceStreamWriter::CTraceStreamWriter()
    {
    }
    
    
    /**
     *
     */
    CTraceStreamWriter::~CTraceStreamWriter()
    {
        
    }
    
    
    /**
     *
     */
    void CTraceStreamWriter::Init( NyxNet::CNxConnectionRef refConnection )
    {
        m_refConnection = refConnection;
    }
    
    
    /**
     *
     */
    void CTraceStreamWriter::Terminate()
    {
        m_refConnection.Release();
    }
    
    
    /**
     *
     */
    void CTraceStreamWriter::Write( const Nyx::CTraceHeader& header, const wchar_t* wszText )
    {
        Nyx::UInt32                 SectionsCount = 4;
        
    	CNxStreamWriter				SWriter((NyxNet::CNxConnection*)m_refConnection, eNxDT_TraceData);
        CTraceFlags			        flags( s_BaseTraceFlags, CTraceFlags::TFlags_WideChar );
        
        if ( SWriter.Valid() )
        {
            // write sections count
            {
                CNxSectionStreamWriter      SectionsCountWriter(SWriter, sizeof(SectionsCount));
                
                SectionsCountWriter.Write(&SectionsCount, sizeof(SectionsCount));
            }
            
            // write version
            {
                CNxSectionStreamWriter		FlagsWriter(SWriter, sizeof(flags));
                
                FlagsWriter.Write(&flags, sizeof(flags));
            }
            
            // write thread id
            {
                CNxSectionStreamWriter		ThreadIdWriter(SWriter, (NyxNet::NxDataSize)header.ThreadId().Length()+1);
                
                ThreadIdWriter.Write( (void*)(const char*)header.ThreadId(), (NyxNet::NxDataSize)header.ThreadId().Length()+1);
            }
            
            // write tickcount
            {
                CNxSectionStreamWriter		TickCountWriter(SWriter, (NyxNet::NxDataSize)header.TickCount().Length()+1);
                
                TickCountWriter.Write( (void*)(const char*)header.TickCount(), (NyxNet::NxDataSize)header.TickCount().Length()+1);
            }
            
            // write data
            {
                size_t						len = wcslen(wszText)+1;
                CNxSectionStreamWriter		DataWriter(SWriter, (NyxNet::NxDataSize)(len*sizeof(wchar_t)));
                
                DataWriter.Write( (void*)wszText, (NyxNet::NxDataSize)(len*sizeof(wchar_t)) );
            }
        }
    }
    
    
    /**
     *
     */
    void CTraceStreamWriter::Write( const Nyx::CTraceHeader& header, const char* szText )
    {
        Nyx::UInt32                 SectionsCount = 4;

        CNxStreamWriter				SWriter((NyxNet::CNxConnection*)m_refConnection, eNxDT_TraceData);
        CTraceFlags			        flags( s_BaseTraceFlags, CTraceFlags::TFlags_Ansi );
        
        if ( SWriter.Valid() )
        {
            // write sections count
            {
                CNxSectionStreamWriter      SectionsCountWriter(SWriter, sizeof(SectionsCount));
                
                SectionsCountWriter.Write(&SectionsCount, sizeof(SectionsCount));
            }
            
            // write version
            {
                CNxSectionStreamWriter		FlagsWriter(SWriter, sizeof(flags));
                
                FlagsWriter.Write(&flags, sizeof(flags));
            }
            
            // write thread id
            {
                CNxSectionStreamWriter		ThreadIdWriter(SWriter, (NyxNet::NxDataSize)header.ThreadId().Length()+1);
                
                ThreadIdWriter.Write( (void*)(const char*)header.ThreadId(), (NyxNet::NxDataSize)header.ThreadId().Length()+1);
            }
            
            // write tickcount
            {
                CNxSectionStreamWriter		TickCountWriter(SWriter, (NyxNet::NxDataSize)header.TickCount().Length()+1);
                
                TickCountWriter.Write( (void*)(const char*)header.TickCount(), (NyxNet::NxDataSize)header.TickCount().Length()+1);
            }
            
            // write data
            {
                size_t						len = strlen(szText)+1;
                CNxSectionStreamWriter		DataWriter(SWriter, (NyxNet::NxDataSize)(len*sizeof(char)));
                
                DataWriter.Write( (void*)szText, (NyxNet::NxDataSize)(len*sizeof(char)) );
            }
        }
        
    }
}

