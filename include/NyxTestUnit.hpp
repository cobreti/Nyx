#ifndef _NYXTESTUNIT_HPP_
#define _NYXTESTUNIT_HPP_

#include "NyxObject.hpp"
#include "NyxRefCount_Impl.hpp"
#include "NyxRef.hpp"

DECLARE_NYXOBJECTREF(CTestUnit)

namespace Nyx
{
	/**
	 *	@brief		Object representing a test unit
	 *	@author		Danny Thibaudeau
	 */
	class CTestUnit : public Nyx::CObject
	{
	public: // public methods
				
		/**
		 *	@brief		Performs the test unit
		 *	@return		true if the test succeeded, false otherwise
		 */
		virtual bool Perform() = 0;
	};
};


#endif // _NYXTESTUNIT_HPP_

