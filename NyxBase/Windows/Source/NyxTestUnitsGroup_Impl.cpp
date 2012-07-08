#include "NyxTestUnitsGroup_Impl.hpp"


/**
 *
 */
Nyx::CTestUnitsGroupRef Nyx::CTestUnitsGroup::Alloc()
{
	return new NyxWin32::CTestUnitsGroup_Impl();
}


/**
 *
 */
NyxWin32::CTestUnitsGroup_Impl::CTestUnitsGroup_Impl()
{
}


/**
 *
 */
NyxWin32::CTestUnitsGroup_Impl::~CTestUnitsGroup_Impl()
{
}


/**
 *
 */
bool NyxWin32::CTestUnitsGroup_Impl::Add( const Nyx::CTestUnitsGroup::TestUnitID& id, Nyx::CTestUnit* pTU )
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
Nyx::CTestUnitRef NyxWin32::CTestUnitsGroup_Impl::Get( const Nyx::CTestUnitsGroup::TestUnitID& id )
{
	Nyx::CTestUnit*				pTU = NULL;
	TestUnitsTable::iterator	pos;
	
	pos = m_Table.find(id);
	if ( m_Table.end() != pos )
	{
		pTU = pos->second;
	}
	
	return pTU;
}


/**
 *
 */
bool NyxWin32::CTestUnitsGroup_Impl::Remove( const Nyx::CTestUnitsGroup::TestUnitID& id )
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
Nyx::UInt32 NyxWin32::CTestUnitsGroup_Impl::Perform( const Nyx::CTestUnitsGroup::TestUnitID& id )
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
