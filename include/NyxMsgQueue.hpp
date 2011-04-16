#ifndef _NYXMSGQUEUE_HPP_
#define _NYXMSGQUEUE_HPP_

#include "NyxObject.hpp"

namespace Nyx
{
	class CMsg;
	class IMsgQueueEventHandler;

	/**
	 *	\brief		Message queue object
	 */
	class CMsgQueue : public Nyx::CObject
	{
	public:
		static Nyx::CMsgQueue* Alloc();
		
	public:
	
		virtual void Push( CMsg* const pMsg ) = 0;
		virtual CMsg* Pop() = 0;
		virtual void SetHandler( IMsgQueueEventHandler* pHandler ) = 0;
	};


	/**
	 *	\brief		Interface to receive message queue events
	 */
	class IMsgQueueEventHandler
	{
	public:
	
		/**
		 *	\brief	Function called when the message queue goes from 0 to 1 message
		 */
		virtual void OnMessageReceived() = 0;
	};
}


#endif // _NYXMSGQUEUE_HPP_
