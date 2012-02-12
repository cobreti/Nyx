#ifndef _NYXNETPIPESOCKETWRITER_IMPL_HPP_
#define _NYXNETPIPESOCKETWRITER_IMPL_HPP_

#include "NyxNetPipeSocketWriter.hpp"
#include "NyxObject_Impl.hpp"
#include "NyxBuffer.hpp"
#include "NyxAString.hpp"

namespace NyxNetLinux
{
	class CPipeSocketWriter_Impl : public Nyx::CObject_Impl<NyxNet::CPipeSocketWriter>
	{
	public:
		CPipeSocketWriter_Impl();
		virtual ~CPipeSocketWriter_Impl();
		
	public: // CPipeSocket mehtods
	
		virtual Nyx::NyxResult Create( const char* szPipename );
		virtual Nyx::NyxResult Connect();
		virtual void Disconnect();
		virtual Nyx::NyxResult Write(	const void* pBuffer, const Nyx::NyxSize& DataSize, Nyx::NyxSize& WrittenSize );
		virtual Nyx::NyxResult Read(	void* pBuffer, const Nyx::NyxSize& DataSize, Nyx::NyxSize& ReadSize );
		virtual void SetListener( NyxNet::ISocketListener* pListener );
		virtual bool Valid() const;
		virtual Nyx::NyxResult Renew();
		
	protected:
	
		int							m_PipeId;
		Nyx::CAString               m_Pipename;
		NyxNet::ISocketListener*	m_pListener;
	};
}


#endif // _NYXNETPIPESOCKETWRITER_IMPL_HPP_
