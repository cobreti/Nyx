#include "NyxNetPipeTraceOutput_Impl.hpp"
#include "NyxNetNxStreamRW.hpp"


NyxNet::CPipeTraceOutputRef NyxNet::CPipeTraceOutput::Alloc(const char* szName)
{
	return new NyxNet::CPipeTraceOutput_Impl(szName);
}


/**
 *
 */
NyxNet::CPipeTraceOutput_Impl::CPipeTraceOutput_Impl(const char* szName)
{
	m_refPipeName = Nyx::CAnsiString::Alloc(szName);
	m_refPipeName->Append("_Pipe");

	m_refSocket = NyxNet::CPipeSocketWriter::Alloc();
	m_refSocket->Create(m_refPipeName->c_str());

	m_refConnection = NyxNet::CNxConnection::Alloc();
	m_refConnection->Open(m_refSocket);

	m_refSocket->Connect();
}


/**
 *
 */
NyxNet::CPipeTraceOutput_Impl::~CPipeTraceOutput_Impl()
{
	m_refSocket->Disconnect();
}


/**
 *
 */
void NyxNet::CPipeTraceOutput_Impl::Write( const Nyx::CTraceHeader& header, const wchar_t* wszText )
{
	CNxStreamWriter				SWriter((NyxNet::CNxConnection*)m_refConnection, eNxDT_TraceData);
	Nyx::UInt32					version = 0x0002;

	if ( SWriter.Valid() )
	{
		// write version
		{
			CNxSectionStreamWriter		VersionWriter(SWriter, sizeof(version));

			VersionWriter.Write(&version, sizeof(version));
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
void NyxNet::CPipeTraceOutput_Impl::Write( const Nyx::CTraceHeader& header, const char* szText )
{
	CNxStreamWriter				SWriter((NyxNet::CNxConnection*)m_refConnection, eNxDT_TraceData);
	Nyx::UInt32					version = 0x0001;

	if ( SWriter.Valid() )
	{
		// write version
		{
			CNxSectionStreamWriter		VersionWriter(SWriter, sizeof(version));

			VersionWriter.Write(&version, sizeof(version));
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
