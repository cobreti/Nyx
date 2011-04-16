#ifndef _NYXTRACEMODULE_HPP_
#define _NYXTRACEMODULE_HPP_


namespace Nyx
{
	class CTraceCompositor;

	class CTraceModule
	{
	public:
	
		/**
		 *	\brief		Returns the reference trace compositor
		 *				(the first trace compositor to be created)
		 *	\return		Trace compositor pointer
		 */
		virtual CTraceCompositor* Reference() = 0;

		/**
		 *	\brief		Sets the thread's default trace compositor
		 *	\param		pDefault : trace compositor pointer
		 */
		virtual void SetThreadDefault( CTraceCompositor* pDefault ) = 0;
		
		/**
		 *	\brief		returns the thread's default trace compositor
		 *	\return		Trace compositor pointer
		 */
		virtual CTraceCompositor* ThreadDefault() = 0;
		
		/**
		 *	\brief		Remove the thread's trace compositor
		 */
		virtual void RemoveThreadDefault() = 0;
	};
}


#endif // _NYXTRACEMODULE_HPP_

