#ifndef _NYXTESTUNITSGROUP_IMPL_HPP_
#define _NYXTESTUNITSGROUP_IMPL_HPP_

#include "NyxTestUnitsGroup.hpp"
#include "NyxTestUnit.hpp"
#include "NyxObject_Impl.hpp"
#include "NyxRef.hpp"

#include <map>

DECLARE_NYXOBJECTREF(CTestUnit);

namespace NyxOSX
{
	class CTestUnitsGroup_Impl : public Nyx::CObject_Impl<Nyx::CTestUnitsGroup>
	{
	public:
		CTestUnitsGroup_Impl();
		virtual ~CTestUnitsGroup_Impl();
		
		virtual bool Add( const Nyx::CTestUnitsGroup::TestUnitID& id, Nyx::CTestUnit* pTU );
		virtual Nyx::CTestUnitRef Get( const Nyx::CTestUnitsGroup::TestUnitID& id );
		virtual bool Remove( const Nyx::CTestUnitsGroup::TestUnitID& id );
		virtual Nyx::UInt32 Perform( const Nyx::CTestUnitsGroup::TestUnitID& id );
		
	protected:
	
		typedef		std::map<Nyx::CTestUnitsGroup::TestUnitID, Nyx::CTestUnitRef>		TestUnitsTable;

	protected:
	
		TestUnitsTable		m_Table;
	
	};
}


#endif // _NYXTESTUNITSGROUP_IMPL_HPP_
