#include "NyxTestUnitsGroup_Impl.hpp"


/**
 *
 */
Nyx::CTestUnitsGroupRef Nyx::CTestUnitsGroup::Alloc()
{
	return new NyxOSX::CTestUnitsGroup_Impl();
}


/**
 *
 */
NyxOSX::CTestUnitsGroup_Impl::CTestUnitsGroup_Impl()
{
}


/**
 *
 */
NyxOSX::CTestUnitsGroup_Impl::~CTestUnitsGroup_Impl()
{
}


/**
 *
 */
bool NyxOSX::CTestUnitsGroup_Impl::Add( const Nyx::CTestUnitsGroup::TestUnitID& id, Nyx::CTestUnit* pTU )
{
	bool						bRet(false);
	TestUnitsTable::iterator	pos;
	
	pos = m_Table.find(id);

	if ( m_Table.end() == pos )
	{
		m_Table.insert( std::make_pair(id, pTU) );
		bRet = true;
	}
	
	return bRet;
}


/**
 *
 */
Nyx::CTestUnitRef NyxOSX::CTestUnitsGroup_Impl::Get( const Nyx::CTestUnitsGroup::TestUnitID& id )
{
	Nyx::CTestUnitRef			refTU = NULL;
	TestUnitsTable::iterator	pos;
	
	pos = m_Table.find(id);
	if ( m_Table.end() != pos )
	{
		refTU = pos->second;
	}
	
	return refTU;
}


/**
 *
 */
bool NyxOSX::CTestUnitsGroup_Impl::Remove( const Nyx::CTestUnitsGroup::TestUnitID& id )
{
	bool						bRet(false);
	TestUnitsTable::iterator	pos;
	
	pos = m_Table.find(id);
	if ( m_Table.end() != pos )
	{
		m_Table.erase(id);
		bRet = true;
	}
		
	return bRet;
}


/**
 *
 */
Nyx::UInt32 NyxOSX::CTestUnitsGroup_Impl::Perform( const Nyx::CTestUnitsGroup::TestUnitID& id )
{
	Nyx::UInt32			unRet(0);
	Nyx::CTestUnit*		pTestUnit = NULL;
	
	pTestUnit = Get(id);
	if ( NULL != pTestUnit )
	{
		unRet = pTestUnit->Perform();
	}
	
	return unRet;
}
