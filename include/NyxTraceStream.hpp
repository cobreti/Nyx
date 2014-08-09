#ifndef _NYXTRACESTREAM_HPP_
#define _NYXTRACESTREAM_HPP_

#include "NyxModule.hpp"
#include "NyxTraceCompositor.hpp"
#include "NyxTraceFeed.hpp"


#pragma managed(push, off)


#define NYXTRACE(filter, output)        { Nyx::CTraceStream stream(filter); stream << output; }


namespace Nyx
{
	class CTraceStream
	{
	public: // public functions
        explicit CTraceStream(const Nyx::TraceFilter& filter) :
		m_pTrace(NULL)
		{
            Nyx::CModule* pModule = CModule::GetDefault();
            if ( pModule )
            {
                CTraceModule& rTracesModule = pModule->Traces();
                m_pTrace = rTracesModule.ThreadDefault();

                if ( m_pTrace == NULL )
                    m_pTrace = Nyx::CModule::GetDefault()->Traces().Reference();
                if ( m_pTrace )
                    m_pTrace->Begin(filter);
            }
			//m_pTrace->Write(CTF_TickCount());
		}


        explicit CTraceStream(const Nyx::TraceFilter& filter, Nyx::CTraceCompositor* pTraceCompositor) :
		m_pTrace(pTraceCompositor)
		{
			m_pTrace->Begin(filter);
		}
		
		~CTraceStream()
		{
			if ( m_pTrace )
				m_pTrace->End();
		}
		
		
		CTraceStream& operator << ( const Nyx::CTraceFeed& feed )
		{
			if ( m_pTrace )
				m_pTrace->Write(feed);
			
			return *this;
		}


		CTraceStream& Write( const wchar_t* const wszText, ... );

		CTraceStream& Write( const char* const szText, ... );

	protected: // protected functions
		
	protected: // protected members
		
		Nyx::CTraceCompositor*				m_pTrace;
	};
}

#pragma managed(pop)

#endif // _NYXTRACESTREAM_HPP_

