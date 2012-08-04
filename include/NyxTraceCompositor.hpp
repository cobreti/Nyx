#ifndef _NYXTRACECOMPOSITOR_HPP_
#define _NYXTRACECOMPOSITOR_HPP_

#include "NyxObject.hpp"
#include "NyxTypes.hpp"
#include "NyxRef.hpp"


DECLARE_NYXOBJECTREF(CTraceCompositor)

namespace Nyx
{
	class CTraceFeed;
	class CTraceOutput;
	

	enum ETraceCompositorCharSet
	{
		eTCCS_WideChar,
		eTCCS_Ansi
	};

	
	/**
	 *	\brief		Object used to compose a single trace line from
	 *				the different trace streams
	 */
	class CTraceCompositor : public Nyx::CObject
	{
	public: // static functions

		/**
		 *	\brief		Allocates a new trace compositor object
		 */
		static CTraceCompositorRef Alloc(ETraceCompositorCharSet charset = eTCCS_WideChar, bool bUseAsDefault = true);
		
	public:  // public methods
		
		/**
		 *	\brief		Begin a trace set
		 *	\param		filter : filter used for the trace
		 */
		virtual void Begin(const TraceFilter& filter) = 0;
		
		/**
		 *	\brief		Ends a trace set
		 */
		virtual void End() = 0;
		
		/**
		 *	\brief		adds data to the trace set
		 *	\param		feed : trace feed object
		 */
		virtual void Write(const CTraceFeed& feed) = 0;
		
		/**
		 *	\brief		Creates a clone of the current compositor
		 *	\return		Trace compositor pointer
		 */
		virtual CTraceCompositor* Clone() = 0;
		
		/**
		 *	\brief		Sets the output for traces
		 *	\param		pOutput : trace output pointer
		 */
		virtual void SetOutput( CTraceOutput* pOutput ) = 0;

		/**
		 *	\brief		Override the thread id
		 *	\param		id : thread id
		 *	\param		mid : managed thread id (for managed code like .NET)
		 */
		virtual void OverrideThreadId(const unsigned int& id, const unsigned int& mid) = 0;
	};
}


#endif // _NYXTRACECOMPOSITOR_HPP_

