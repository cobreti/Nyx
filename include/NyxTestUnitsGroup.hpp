#ifndef _NYXTESTUNITSGROUP_HPP_
#define _NYXTESTUNITSGROUP_HPP_

#include "NyxObject.hpp"
#include "NyxTestUnit.hpp"
#include "NyxRef.hpp"

DECLARE_NYXOBJECTREF(CTestUnitsGroup)

namespace Nyx
{	
	class CTestUnitsGroup : public Nyx::CObject
	{
	public:
	
		typedef		UInt32		TestUnitID;
	
	public:
	
		static CTestUnitsGroupRef Alloc();
		
	public:
	
		virtual bool Add( const TestUnitID& id, CTestUnit* pTU ) = 0;
		
		virtual CTestUnitRef Get( const TestUnitID& id ) = 0;
		
		virtual bool Remove( const TestUnitID& id ) = 0;
		
		virtual Nyx::UInt32 Perform( const TestUnitID& id ) = 0;
	};
};


#endif // _NYXTESTUNITSGROUP_HPP_
