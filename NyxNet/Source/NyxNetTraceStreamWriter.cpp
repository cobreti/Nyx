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
        Nyx::UInt32                 SectionsCount = 6;
        
    	CNxStreamWriter				SWriter((NyxNet::CNxConnection*)m_refConnection, eNxDT_TraceData);
        CTraceFlags			        flags( s_BaseTraceFlags, CTraceFlags::TFlags_WideChar );
        
        if ( SWriter.Valid() )
        {
            // write sections count
            {
                CNxSectionStreamWriter      SectionsCountWriter(SWriter, sizeof(SectionsCount));
                
                SectionsCountWriter.Write(&SectionsCount, sizeof(SectionsCount));
            }
            
            // flags
            {
                CNxSectionStreamWriter		FlagsWriter(SWriter, sizeof(flags));
                
                FlagsWriter.Write(&flags, sizeof(flags));
            }

            // write local time reference
            {
                //Nyx::UInt32                 value =     ((header.TimeReference().Time().Hours()) << 16) | 
                //                                        ((header.TimeReference().Time().Minutes()) << 8) |
                //                                        (header.TimeReference().Time().Seconds());

                Nyx::NyxSize                time_length = header.TimeReference().TimeString().Length() + 1;

                CNxSectionStreamWriter      LocalTimeWriter(SWriter, time_length);
                LocalTimeWriter.Write((void*)header.TimeReference().TimeString().c_str(), time_length);
            }

            // write tick count reference
            {
                CNxSectionStreamWriter      RefTickCountWriter(SWriter, header.TimeReference().TickCount().Length()+1);

                RefTickCountWriter.Write( (void*)header.TimeReference().TickCount().c_str(), (NyxNet::NxDataSize)header.TimeReference().TickCount().Length()+1);
            }
            
            // write thread id
            {
                CNxSectionStreamWriter		ThreadIdWriter(SWriter, (NyxNet::NxDataSize)header.ThreadId().Length()+1);
                
                ThreadIdWriter.Write( (void*)header.ThreadId().c_str(), (NyxNet::NxDataSize)header.ThreadId().Length()+1);
            }
            
            // write tickcount
            {
                CNxSectionStreamWriter		TickCountWriter(SWriter, (NyxNet::NxDataSize)header.TickCount().Length()+1);
                
                TickCountWriter.Write( (void*)header.TickCount().c_str(), (NyxNet::NxDataSize)header.TickCount().Length()+1);
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
            
            // write flags
            {
                CNxSectionStreamWriter		FlagsWriter(SWriter, sizeof(flags));
                
                FlagsWriter.Write(&flags, sizeof(flags));
            }
            
            // write local time reference
            {
                //Nyx::UInt32                 value =     ((header.TimeReference().Time().Hours()) << 16) | 
                //                                        ((header.TimeReference().Time().Minutes()) << 8) |
                //                                        (header.TimeReference().Time().Seconds());

                Nyx::NyxSize                time_length = header.TimeReference().TimeString().Length() + 1;

                CNxSectionStreamWriter      LocalTimeWriter(SWriter, time_length);
                LocalTimeWriter.Write((void*)header.TimeReference().TimeString().c_str(), time_length);
            }

            // write tick count reference
            {
                CNxSectionStreamWriter      RefTickCountWriter(SWriter, header.TimeReference().TickCount().Length()+1);

                RefTickCountWriter.Write( (void*)header.TimeReference().TickCount().c_str(), (NyxNet::NxDataSize)header.TimeReference().TickCount().Length()+1);
            }
            
            // write thread id
            {
                CNxSectionStreamWriter		ThreadIdWriter(SWriter, (NyxNet::NxDataSize)header.ThreadId().Length()+1);
                
                ThreadIdWriter.Write( (void*)header.ThreadId().c_str(), (NyxNet::NxDataSize)header.ThreadId().Length()+1);
            }
            
            // write tickcount
            {
                CNxSectionStreamWriter		TickCountWriter(SWriter, (NyxNet::NxDataSize)header.TickCount().Length()+1);
                
                TickCountWriter.Write( (void*)header.TickCount().c_str(), (NyxNet::NxDataSize)header.TickCount().Length()+1);
            }
            
            // write data
            {
                size_t						len = strlen(szText)+1;
                CNxSectionStreamWriter		DataWriter(SWriter, (NyxNet::NxDataSize)(len*sizeof(char)));
                
                DataWriter.Write( (void*)szText, (NyxNet::NxDataSize)(len*sizeof(char)) );
            }
        }
        
    }


    /**
     *
     */
    void CTraceStreamWriter::Write( Nyx::CAString& name, const Nyx::CTraceHeader& header, const wchar_t* wszText )
    {
        Nyx::UInt32                 SectionsCount = 7;
        
    	CNxStreamWriter				SWriter((NyxNet::CNxConnection*)m_refConnection, eNxDT_TraceData);
        CTraceFlags			        flags( s_BaseTraceFlags, CTraceFlags::TFlags_WideChar );
        
        if ( SWriter.Valid() )
        {
            // write sections count
            {
                CNxSectionStreamWriter      SectionsCountWriter(SWriter, sizeof(SectionsCount));
                
                SectionsCountWriter.Write(&SectionsCount, sizeof(SectionsCount));
            }

            // name
            {
                NyxNet::NxDataSize                  size = (NyxNet::NxDataSize)name.length() + 1;
                NyxNet::CNxSectionStreamWriter      SectionWriter(SWriter, size);
                
                SectionWriter.Write( name.BufferPtr(), size );
            }
            
            // flags
            {
                CNxSectionStreamWriter		FlagsWriter(SWriter, sizeof(flags));
                
                FlagsWriter.Write(&flags, sizeof(flags));
            }
            
            // write local time reference
            {
                //Nyx::UInt32                 value =     ((header.TimeReference().Time().Hours()) << 16) | 
                //                                        ((header.TimeReference().Time().Minutes()) << 8) |
                //                                        (header.TimeReference().Time().Seconds());
                
                Nyx::NyxSize                time_length = header.TimeReference().TimeString().Length() + 1;
                
                CNxSectionStreamWriter      LocalTimeWriter(SWriter, time_length);
                LocalTimeWriter.Write((void*)header.TimeReference().TimeString().c_str(), time_length);
            }
            
            // write tick count reference
            {
                CNxSectionStreamWriter      RefTickCountWriter(SWriter, header.TimeReference().TickCount().Length()+1);
                
                RefTickCountWriter.Write( (void*)header.TimeReference().TickCount().c_str(), (NyxNet::NxDataSize)header.TimeReference().TickCount().Length()+1);
            }
            
            // write thread id
            {
                CNxSectionStreamWriter		ThreadIdWriter(SWriter, (NyxNet::NxDataSize)header.ThreadId().Length()+1);
                
                ThreadIdWriter.Write( (void*)header.ThreadId().c_str(), (NyxNet::NxDataSize)header.ThreadId().Length()+1);
            }
            
            // write tickcount
            {
                CNxSectionStreamWriter		TickCountWriter(SWriter, (NyxNet::NxDataSize)header.TickCount().Length()+1);
                
                TickCountWriter.Write( (void*)header.TickCount().c_str(), (NyxNet::NxDataSize)header.TickCount().Length()+1);
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
    void CTraceStreamWriter::Write( Nyx::CAString& name, const Nyx::CTraceHeader& header, const char* szText )
    {
        Nyx::UInt32                 SectionsCount = 7;
        
        CNxStreamWriter				SWriter((NyxNet::CNxConnection*)m_refConnection, eNxDT_TraceData);
        CTraceFlags			        flags( s_BaseTraceFlags, CTraceFlags::TFlags_Ansi );
        
        if ( SWriter.Valid() )
        {
            // write sections count
            {
                CNxSectionStreamWriter      SectionsCountWriter(SWriter, sizeof(SectionsCount));
                
                SectionsCountWriter.Write(&SectionsCount, sizeof(SectionsCount));
            }
            
            // name
            {
                NyxNet::NxDataSize                  size = (NyxNet::NxDataSize)name.length() + 1;
                NyxNet::CNxSectionStreamWriter      SectionWriter(SWriter, size);
                
                SectionWriter.Write( name.BufferPtr(), size );
            }
            
            // write flags
            {
                CNxSectionStreamWriter		FlagsWriter(SWriter, sizeof(flags));
                
                FlagsWriter.Write(&flags, sizeof(flags));
            }
            
            // write local time reference
            {
                //Nyx::UInt32                 value =     ((header.TimeReference().Time().Hours()) << 16) | 
                //                                        ((header.TimeReference().Time().Minutes()) << 8) |
                //                                        (header.TimeReference().Time().Seconds());
                
                Nyx::NyxSize                time_length = header.TimeReference().TimeString().Length() + 1;
                
                CNxSectionStreamWriter      LocalTimeWriter(SWriter, time_length);
                LocalTimeWriter.Write((void*)header.TimeReference().TimeString().c_str(), time_length);
            }
            
            // write tick count reference
            {
                CNxSectionStreamWriter      RefTickCountWriter(SWriter, header.TimeReference().TickCount().Length()+1);
                
                RefTickCountWriter.Write( (void*)header.TimeReference().TickCount().c_str(), (NyxNet::NxDataSize)header.TimeReference().TickCount().Length()+1);
            }
            
            // write thread id
            {
                CNxSectionStreamWriter		ThreadIdWriter(SWriter, (NyxNet::NxDataSize)header.ThreadId().Length()+1);
                
                ThreadIdWriter.Write( (void*)header.ThreadId().c_str(), (NyxNet::NxDataSize)header.ThreadId().Length()+1);
            }
            
            // write tickcount
            {
                CNxSectionStreamWriter		TickCountWriter(SWriter, (NyxNet::NxDataSize)header.TickCount().Length()+1);
                
                TickCountWriter.Write( (void*)header.TickCount().c_str(), (NyxNet::NxDataSize)header.TickCount().Length()+1);
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

