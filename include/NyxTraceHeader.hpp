#ifndef _NYXTRACEHEADER_HPP_
#define _NYXTRACEHEADER_HPP_

#include "NyxTypes.hpp"
#include "NyxFixedString.hpp"
#include "NyxTraceTimeReference.hpp"

namespace Nyx
{
	/**
	 *
	 */
	class CTraceHeader
	{
	public:

		/**
		 *	\typedef		thread id
		 */
		typedef		TFixedString<char, 20>			TThreadId;


		/**
		 *	\typedef		tick count
		 */
		typedef		TFixedString<char, 30>			TTickCount;

	public:
		CTraceHeader()	{ m_Version = 1; }
		~CTraceHeader() {}

		const Nyx::UInt32& Version() const		{ return m_Version; }

		const TThreadId& ThreadId() const	{ return m_ThreadId; }
		TThreadId& ThreadId()				{ return m_ThreadId; }

		const TTickCount& TickCount() const		{ return m_TickCount; }
		TTickCount& TickCount()					{ return m_TickCount; }

        const CTraceTimeReference& TimeReference() const        { return m_TimeReference; }

	protected:

		Nyx::UInt32			    m_Version;
		TThreadId			    m_ThreadId;
		TTickCount			    m_TickCount;
        CTraceTimeReference     m_TimeReference;

	private:
		// disable copy-constructor
		CTraceHeader(const CTraceHeader&);

		// disable = operator
		const CTraceHeader& operator = (const CTraceHeader&);
	};
}


#endif // _NYXTRACEHEADER_HPP_
