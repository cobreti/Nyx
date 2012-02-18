#ifndef _NYXNETPIPESOCKETREADER_HPP_
#define _NYXNETPIPESOCKETREADER_HPP_

#include "NyxNetPipeSocketReader.hpp"
#include "NyxObject_Impl.hpp"
#include "NyxBuffer.hpp"
#include "NyxAString.hpp"
#include "NyxEvent.hpp"

namespace NyxNetOSX
{
	class CPipeSocketReader_Impl : public Nyx::CObject_Impl<NyxNet::CPipeSocketReader>
	{
	public:
		CPipeSocketReader_Impl();
		virtual ~CPipeSocketReader_Impl();
		
	public: // CPipeSocket methods
	
		virtual Nyx::NyxResult Create( const char* szPipename, const Nyx::NyxSize& BufferSize );
		virtual Nyx::NyxResult Connect();
		virtual void Disconnect();
		virtual Nyx::NyxResult Write(	const void* pBuffer, const Nyx::NyxSize& DataSize, Nyx::NyxSize& WrittenSize );
		virtual Nyx::NyxResult Read(	void* pBuffer, const Nyx::NyxSize& DataSize, Nyx::NyxSize& ReadSize );
		virtual void SetListener( NyxNet::ISocketListener* pListener );
        virtual bool Valid() const;
        virtual Nyx::NyxResult Renew();
		
	protected:
	
		int							m_PipeId;
		bool						m_bConnected;
		Nyx::TBuffer<Nyx::Byte>		m_Buffer;
		Nyx::CAString				m_Pipename;
		timeval						m_Timeout;
		NyxNet::ISocketListener*	m_pListener;
		Nyx::CEventRef				m_refWaitEvent;
	};
}


#endif // _NYXNETPIPESOCKETREADER_HPP_
