#ifndef _NYXMTOBJACCESSOR_HPP_
#define _NYXMTOBJACCESSOR_HPP_

#include "NyxMTAccessException.hpp"

namespace Nyx
{
	/**
	 *
	 */
	enum EMTAccessMode
	{
		eMTAM_Read,
		eMTAM_Write
	};


	/**
	 *
	 */
	enum EMLockingMode
	{
		eMTLM_Lock,
		eMTLM_Trylock,
		eMTLM_Delayed
	};

	/**
	 *
	 *	\brief		Accessor object to give access to protected interface
	 *				of it while the object is locked to prevent
	 *				conccurent access
	 *
	 */
	template <class T, class I>
	class CMTObjAccessor
	{
	public:

		/**
		 *
		 */
		class XAccessorBase
		{
		public:
			XAccessorBase(T& rObj) : m_rObj(rObj) {}
			virtual ~XAccessorBase() {}

			virtual T& Obj() = 0;
			virtual const T& Obj() const = 0;

		protected:
			T& m_rObj;
		};


		/**
		 *
		 */
		class XInvalidAccessor : public XAccessorBase
		{
		public:
			XInvalidAccessor(T& rObj) : XAccessorBase(rObj) {}
			virtual ~XInvalidAccessor() {}

            virtual T& Obj() { throw Nyx::CMTAccessException("trying to access an unlocked object"); return this->m_rObj; }
            virtual const T& Obj() const { throw Nyx::CMTAccessException("trying to access an unlocked object"); return this->m_rObj; }
		};


		/**
		 *
		 */
		class XValidAccessor : public XAccessorBase
		{
		public:
			XValidAccessor(T& rObj) : XAccessorBase(rObj) {}
			virtual ~XValidAccessor() {}

            virtual T& Obj() { return this->m_rObj; }
            virtual const T& Obj() const { return this->m_rObj; }
		};

	public:
		CMTObjAccessor(T& rObj, const EMLockingMode LockingMode = eMTLM_Lock) : 
			m_rObj(rObj), 
			m_bLocked(false),
			m_ValidAccessor(rObj),
			m_InvalidAccessor(rObj),
			m_pAccessor(NULL)
		{
			m_pAccessor = &m_InvalidAccessor;

			Lock(LockingMode);

			//switch ( LockingMode )
			//{
			//	case eMTLM_TryLock:
			//		m_bLocked = m_rObj.MTTryLock();
			//		break;
			//	case eMTLM_Lock:
			//		m_bLocked = m_rObj.MTLock();
			//		break;
			//};

			//if ( LockingMode == eMTLM_Trylock )
			//	m_bLocked = m_rObj.MTTryLock();
			//else
			//	m_bLocked = m_rObj.MTLock();

			//if ( m_bLocked )
			//	m_pAccessor = &m_ValidAccessor;
		}

		~CMTObjAccessor()
		{
			Unlock();
			//if ( m_bLocked )
			//	m_rObj.MTUnlock();
		}

		bool Lock( const EMLockingMode LockingMode = eMTLM_Lock )
		{
			if ( m_bLocked )
				return true;

			switch ( LockingMode )
			{
				case eMTLM_Trylock:
					m_bLocked = m_rObj.MTTryLock();
					break;
				case eMTLM_Lock:
					m_bLocked = m_rObj.MTLock();
					break;
			};

			if ( m_bLocked )
				m_pAccessor = &m_ValidAccessor;

			return m_bLocked;
		}

		void Unlock()
		{
			if ( m_bLocked )
				m_rObj.MTUnlock();
		}

		bool Locked() const { return m_bLocked; }

		I* operator -> () { return static_cast<I*>(&(m_pAccessor->Obj())); }
		const I* operator -> () const { return static_cast<const I*>(&(m_pAccessor->Obj())); }

		operator T& () { return m_pAccessor->Obj(); }
		operator const T& () const { return m_pAccessor->Obj(); }

		const T& operator = ( const T& obj ) { return m_pAccessor->Obj().operator = (obj); }
		bool operator == ( const T& obj ) {	return m_pAccessor->Obj().operator == (obj); }
		bool operator != ( const T& obj ) { return m_pAccessor->Obj().operator != (obj); }

		T& operator ++ () { return m_pAccessor->Obj().operator ++ (); }
		T& operator -- () { return m_pAccessor->Obj().operator -- (); }

		operator bool () const	{ return m_bLocked; }

	protected:

		T&					m_rObj;
		bool				m_bLocked;
		XValidAccessor		m_ValidAccessor;
		XInvalidAccessor	m_InvalidAccessor;
		XAccessorBase*		m_pAccessor;
	};


	/**
	 *
	 *	\brief		const accessor object to give access to protected interface
	 *				of it while the object is locked to prevent
	 *				conccurent access
	 *
	 */
	template <class T, class I>
	class CConstMTObjAccessor
	{
	protected:
		/**
		 *
		 */
		class XAccessorBase
		{
		public:
			XAccessorBase(const T& rObj) : m_rObj(rObj) {}
			virtual ~XAccessorBase() {}

			virtual const T& Obj() const = 0;

		protected:
			const T& m_rObj;
		};


		/**
		 *
		 */
		class XInvalidAccessor : public XAccessorBase
		{
		public:
			XInvalidAccessor(const T& rObj) : XAccessorBase(rObj) {}
			virtual ~XInvalidAccessor() {}

			virtual const T& Obj() const { throw Nyx::CMTAccessException("trying to access an unlocked object"); return this->m_rObj; }
		};


		/**
		 *
		 */
		class XValidAccessor : public XAccessorBase
		{
		public:
			XValidAccessor(const T& rObj) : XAccessorBase(rObj) {}
			virtual ~XValidAccessor() {}

			virtual const T& Obj() const { return this->m_rObj; }
		};

	public:
		CConstMTObjAccessor(const T& rObj) : 
			m_rObj(rObj), 
			m_bLocked(false),
			m_ValidAccessor(rObj),
			m_InvalidAccessor(rObj),
			m_pAccessor(NULL)
		{
			m_pAccessor = &m_InvalidAccessor;

			m_bLocked = const_cast<T&>(m_rObj).MTLock(eMTAM_Read);

			if ( m_bLocked )
				m_pAccessor = &m_ValidAccessor;
		}

		~CConstMTObjAccessor()
		{
			const_cast<T&>(m_rObj).MTUnlock(eMTAM_Read);
		}

		const I* operator -> () const  { return &(m_pAccessor->Obj()); }

		operator const T& () const { return m_pAccessor->Obj(); }

		bool operator == ( const T& obj ) {	return m_pAccessor->Obj().operator == (obj); }
		bool operator != ( const T& obj ) {	return m_pAccessor->Obj().operator != (obj); }

		operator bool () const		{ return m_bLocked; }

	protected:

		const T&			m_rObj;
		bool				m_bLocked;
		XValidAccessor		m_ValidAccessor;
		XInvalidAccessor	m_InvalidAccessor;
		XAccessorBase*		m_pAccessor;
	};
}


#endif // _NYXMTOBJACCESSOR_HPP_
