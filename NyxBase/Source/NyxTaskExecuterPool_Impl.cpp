#include "NyxTaskExecuterPool_Impl.hpp"
#include "NyxBodyBlock.hpp"
#include "NyxThreadTaskExecuter_Impl.hpp"
#include "NyxLock.hpp"
#include "NyxSystem.hpp"

/**
 *
 */
Nyx::CTaskExecuterPoolRef Nyx::CTaskExecuterPool::Alloc()
{
	return new NyxOSX::CTaskExecuterPool_Impl();
}


/**
 *
 */
NyxOSX::CTaskExecuterPool_Impl::CTaskExecuterPool_Impl()
{
	m_refExecutersAccess = Nyx::CMutex::Alloc();
}


/**
 *
 */
NyxOSX::CTaskExecuterPool_Impl::~CTaskExecuterPool_Impl()
{
	ReleaseTaskExecuters();
}


/**
 *
 */
void NyxOSX::CTaskExecuterPool_Impl::OnTaskExecuterAvailable( Nyx::CTaskExecuterRef refExecuter )
{
	Nyx::TLock<Nyx::CMutex>			ExecutersAccess(m_refExecutersAccess, true);
	
	TaskExecuterList::iterator		pos = m_UsedExecuters.begin();
	
	// remove from used list
	while ( pos != m_UsedExecuters.end() )
	{
		if ( *pos == refExecuter )
			break;
	
		++ pos;
	}
	
	if ( pos != m_UsedExecuters.end() )
	{
		m_UsedExecuters.erase(pos);
	}
	
	// add to free list
	m_FreeExecuters.push_back(refExecuter);
}




/**
 *
 */
Nyx::NyxResult NyxOSX::CTaskExecuterPool_Impl::Execute(Nyx::CTask *pTask)
{
	Nyx::NyxResult				res = Nyx::kNyxRes_Success;
	Nyx::CTaskExecuterRef		refTaskExecuter;

	res = GetTaskExecuter(refTaskExecuter);
	if ( Nyx::Succeeded(res) )
	{
		refTaskExecuter->Execute(pTask);
	}

	return res;
}


/**
 *
 */
void NyxOSX::CTaskExecuterPool_Impl::StopAllTasks()
{
	//
	// ask all used executers to stop
	//
	{
		Nyx::TLock<Nyx::CMutex>		UsedExecutersLock(m_refExecutersAccess, true);
		TaskExecuterList::iterator	pos = m_UsedExecuters.begin();
		
		while ( pos != m_UsedExecuters.end() )
		{
			(*pos)->StopCurrentTask();
			++ pos;
		}
	}
	
	//
	// wait for all used executers to be free
	//
	while ( !m_UsedExecuters.empty() )
	{
		Nyx::CSystem().Sleep(100);
	}
}


/**
 *
 */
Nyx::NyxResult NyxOSX::CTaskExecuterPool_Impl::GetTaskExecuter( Nyx::CTaskExecuterRef& refTaskExecuter )
{
	Nyx::NyxResult					res = Nyx::kNyxRes_Success;
	
	NyxBeginBody("GetTaskExecuter")
	{
		Nyx::TLock<Nyx::CMutex>		ExecutersAccess(m_refExecutersAccess, true);
		Nyx::CTaskExecuterRef		refFreeExecuter;
		
		// remove from free list or create new one
		if ( m_FreeExecuters.empty() )
		{
			NyxOSX::CThreadTaskExecuter_Impl*		pExecuter = new NyxOSX::CThreadTaskExecuter_Impl(*this);
			pExecuter->Start();
			
			refFreeExecuter = pExecuter;
		}
		else
		{
			refFreeExecuter = m_FreeExecuters.front();
			m_FreeExecuters.pop_front();
		}
		
		// add to used list
		m_UsedExecuters.push_back(refFreeExecuter);
		
		refTaskExecuter = refFreeExecuter;
	}
	NyxEndBody(res)
	
	return res;
}


/**
 *
 */
void NyxOSX::CTaskExecuterPool_Impl::ReleaseTaskExecuters()
{
	//
	// ask all used executers to stop
	//
	{
		Nyx::TLock<Nyx::CMutex>		UsedExecutersLock(m_refExecutersAccess, true);
		TaskExecuterList::iterator	pos = m_UsedExecuters.begin();
		
		while ( pos != m_UsedExecuters.end() )
		{
			(*pos)->StopCurrentTask();
			++ pos;
		}
	}
	
	//
	// wait for all used executers to be free
	//
	while ( !m_UsedExecuters.empty() )
	{
		Nyx::CSystem().Sleep(100);
	}
	
	//
	// release all executers
	//
	{
		Nyx::TLock<Nyx::CMutex>		UsedExecutersLock(m_refExecutersAccess, true);
		
		while ( !m_FreeExecuters.empty() )
		{
			Nyx::CTaskExecuter*	pExecuter = m_FreeExecuters.front();
			NyxOSX::CThreadTaskExecuter_Impl* pThreadExecuter = static_cast<NyxOSX::CThreadTaskExecuter_Impl*>(pExecuter);
			if ( NULL != pThreadExecuter )
				pThreadExecuter->Stop();
			m_FreeExecuters.pop_front();
		}
	}
	
}
