#ifndef _NYXNETPIPECLIENTCONN_HPP_
#define _NYXNETPIPECLIENTCONN_HPP_

#include "NyxTask.hpp"
#include "NyxObject_Impl.hpp"
#include "NyxNetPipeSocketReader.hpp"
#include "NyxStreamRW.hpp"
#include "NyxNetConnection.hpp"
#include "NyxNetConnectionHandler.hpp"

DECLARE_NSPOBJECTREF(NyxNetOSX, CPipeClientConn)

namespace NyxNetOSX
{
	class CPipeClientConn : public Nyx::CObject_Impl<Nyx::CTask>,
							public Nyx::IStreamRW,
							public NyxNet::IConnection
	{
	public:
		CPipeClientConn( NyxNet::CPipeSocketReaderRef refSocket );
		virtual ~CPipeClientConn();

		virtual void SetConnectionHandler( NyxNet::IConnectionHandler* pConnHandler );

	public: // CTask methods

		virtual Nyx::NyxResult Execute();
		virtual Nyx::NyxResult Stop();
	
	public: // CStreamRW methods

		virtual Nyx::NyxResult Read(	void* pBuffer,
										const Nyx::NyxSize& SizeToRead,
										Nyx::NyxSize& SizeRead );
		
		virtual Nyx::NyxResult Write(	void* pBuffer,
										const Nyx::NyxSize& SizeToWrite,
										Nyx::NyxSize& SizeWritten );

	public: // IConnection methods

		virtual void Close();
        virtual NyxNet::CSocketRef Socket();

	protected:

		NyxNet::CPipeSocketReaderRef	m_refSocket;
		NyxNet::IConnectionHandler*		m_pConnectionHandler;
	};
}

#endif // _NYXNETPIPECLIENTCONN_HPP_
