#ifndef _NYXMTINTERFACEACCESS_HPP_
#define _NYXMTINTERFACEACCESS_HPP_

#include "NyxMutex.hpp"
#include "NyxLock.hpp"
#include "NyxMTObjAccessor.hpp"
#include "NyxSystem.hpp"

#pragma warning (disable: 4250)

namespace Nyx
{
	/**
	 *
	 */
	template <class OBJTYPE, class BASE, class INTERFACE>
	class CMTBaseInterfaceAccess : virtual public BASE, virtual protected INTERFACE
	{
	public: // public types
		friend class Nyx::CMTObjAccessor<OBJTYPE, INTERFACE>;
		friend class Nyx::CMTObjAccessor<OBJTYPE, INTERFACE>::XAccessorBase;
		friend class Nyx::CMTObjAccessor<OBJTYPE, INTERFACE>::XValidAccessor;
		friend class Nyx::CMTObjAccessor<OBJTYPE, INTERFACE>::XInvalidAccessor;
		friend class Nyx::CConstMTObjAccessor<OBJTYPE, INTERFACE>;

		typedef		Nyx::CMTObjAccessor<OBJTYPE, INTERFACE>					Accessor;
		typedef		Nyx::CConstMTObjAccessor<OBJTYPE, INTERFACE>			ConstAccessor;
		
	public:
		CMTBaseInterfaceAccess() : BASE() {}
		virtual ~CMTBaseInterfaceAccess() {}
	};
	

	/**
	 *
	 */
	template <class OBJTYPE, class INTERFACE>
	class CMTInterfaceAccess : virtual protected INTERFACE
	{
	public:	// public types

		friend class Nyx::CMTObjAccessor<OBJTYPE, INTERFACE>;
		friend class Nyx::CMTObjAccessor<OBJTYPE, INTERFACE>::XAccessorBase;
		friend class Nyx::CMTObjAccessor<OBJTYPE, INTERFACE>::XValidAccessor;
		friend class Nyx::CMTObjAccessor<OBJTYPE, INTERFACE>::XInvalidAccessor;
		friend class Nyx::CConstMTObjAccessor<OBJTYPE, INTERFACE>;

		typedef		Nyx::CMTObjAccessor<OBJTYPE, INTERFACE>					Accessor;
		typedef		Nyx::CConstMTObjAccessor<OBJTYPE, INTERFACE>			ConstAccessor;

	public:
		CMTInterfaceAccess() :
		  m_LockCount(0)
		{
			m_refDataAccessMutex = Nyx::CMutex::Alloc();
			m_refLockingMutex = Nyx::CMutex::Alloc();
		}

		virtual ~CMTInterfaceAccess()
		{
		}


	protected:
		virtual bool MTLock( EMTAccessMode mode = eMTAM_Write )
		{
			bool		bLocked = false;

			while ( !bLocked && !MTCancelLock() )
			{
				{
					Nyx::TLock<Nyx::CMutex>		lock(m_refLockingMutex, true);

					if ( mode == eMTAM_Write )
					{
						bLocked = m_refDataAccessMutex->AttemptLock();
					}
					else // read access
					{
						if ( m_LockCount == 0 )
							bLocked = m_refDataAccessMutex->AttemptLock();
						else
							bLocked = true;
					}

					if ( bLocked )
						++ m_LockCount;
				}

				if ( !bLocked )
					Nyx::CSystem().Sleep(5);
			}

			return bLocked;
		}

		virtual bool MTTryLock( EMTAccessMode mode = eMTAM_Write )
		{
			bool		bLocked = false;

			Nyx::TLock<Nyx::CMutex>		lock(m_refLockingMutex, true);

			if ( mode == eMTAM_Write )
			{
				bLocked = m_refDataAccessMutex->AttemptLock();
			}
			else // read access
			{
				if ( m_LockCount == 0 )
					bLocked = m_refDataAccessMutex->AttemptLock();
				else
					bLocked = true;
			}

			if ( bLocked )
				++ m_LockCount;

			return bLocked;
		}


		virtual void MTUnlock( EMTAccessMode mode = eMTAM_Write )
		{
			bool bCallOnMTLastWriteUnlock = false;

			{
				Nyx::TLock<Nyx::CMutex>		lock(m_refLockingMutex, true);

				if ( mode == eMTAM_Write )
				{
					m_refDataAccessMutex->Unlock();
					-- m_LockCount;

					bCallOnMTLastWriteUnlock = (m_LockCount == 0);
				}
				else // read access
				{
					-- m_LockCount;

					if ( m_LockCount == 0 )
						m_refDataAccessMutex->Unlock();
				}
			}

			if ( bCallOnMTLastWriteUnlock )
				OnMTLastWriteUnlock();
		}

		virtual void OnMTLastWriteUnlock()
		{
		}

		virtual bool MTCancelLock() const
		{
			return false;
		}

	protected:
		Nyx::CMutexRef				m_refDataAccessMutex;
		Nyx::CMutexRef				m_refLockingMutex;
		Nyx::UInt32					m_LockCount;
	};
}


#endif // _NYXMTINTERFACEACCESS_HPP_

