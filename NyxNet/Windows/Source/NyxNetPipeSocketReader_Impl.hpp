#ifndef _NYXNETPIPESOCKETREADER_IMPL_HPP_
#define _NYXNETPIPESOCKETREADER_IMPL_HPP_

#include "NyxNetPipeSocketReader.hpp"
#include "NyxObject_Impl.hpp"
#include "NyxBuffer.hpp"
#include "NyxAString.hpp"

#include <Windows.h>

namespace NyxNetWin32
{
	class CPipeSocketReader_Impl : public Nyx::CObject_Impl<NyxNet::CPipeSocketReader>
	{
	public:
		CPipeSocketReader_Impl();
		virtual ~CPipeSocketReader_Impl();

	public:

		virtual Nyx::NyxResult Create( const char* szPipename, const Nyx::NyxSize& BufferSize );
		virtual Nyx::NyxResult Connect();
		virtual void Disconnect();
		virtual Nyx::NyxResult Write( const void* pBuffer, const Nyx::NyxSize& DataSize, Nyx::NyxSize& WrittenSize );
		virtual Nyx::NyxResult Read( void* pBuffer, const Nyx::NyxSize& DataSize, Nyx::NyxSize& ReadSize );
		virtual void SetListener( NyxNet::ISocketListener* pListener );
        virtual bool Valid() const;
        virtual Nyx::NyxResult Renew();

	protected:

		virtual void CreateEvents();
		virtual void ReleaseEvents();

	protected:
		HANDLE						m_hPipe;
		HANDLE						m_ahPipeEvent[2];
		OVERLAPPED					m_PipeOverlap;
		Nyx::TBuffer<Nyx::Byte>		m_Buffer;
        Nyx::TBuffer<Nyx::Byte>     m_ReadBuffer;
		Nyx::CAString				m_Pipename;
		bool						m_bConnected;
		NyxNet::ISocketListener*	m_pListener;
	};
}

#endif // _NYXNETPIPESOCKETREADER_IMPL_HPP_
