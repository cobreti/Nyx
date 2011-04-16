#ifndef _NYXREF_HPP_
#define _NYXREF_HPP_


#include "NyxDefs.hpp"
#include "NyxException.hpp"


#define DECLARE_NYXOBJECTREF(_class)						namespace Nyx { class _class; \
																typedef CRef<_class>  _class##Ref; }

#define DECLARE_OBJECTREF(_class)							class _class; \
																typedef Nyx::CRef<_class>  _class##Ref;

#define DECLARE_NSPOBJECTREF(_namespace, _class)			namespace _namespace { class _class; \
																typedef Nyx::CRef<_class>  _class##Ref; }


namespace Nyx
{
	/**
	 *
	 */
	template <class TYPE>
	class CRef
	{
	public:	// public methods
		CRef() :
			m_pObj(NULL)
			{
			}
			
		CRef(const CRef& ref) :
			m_pObj(ref.m_pObj)
			{
				if ( NULL != m_pObj )
				{
					m_pObj->Retain();
				}
			}
			
		CRef(TYPE* pObj) :
			m_pObj(pObj)
			{
				if ( NULL != m_pObj )
				{
					m_pObj->Retain();
				}
			}
			
		~CRef()
			{
				Release();
			}
			
		void Release()
			{
				if ( NULL != m_pObj )
				{
					m_pObj->Release();
					m_pObj = NULL;
				}
			}
			
		bool Valid() const
		{
			return (NULL != m_pObj);
		}
			
		CRef& operator = (const CRef& ref)
			{
				if ( NULL != ref.m_pObj )
				{
					ref.m_pObj->Retain();
				}
				
				if ( NULL != m_pObj )
				{
					m_pObj->Release();
				}
				
				m_pObj = ref.m_pObj;
			
				return *this;
			}
			
		CRef& operator = (TYPE* pObj)
			{
				if ( NULL != pObj )
				{
					pObj->Retain();
				}
			
				if ( NULL != m_pObj )
				{
					m_pObj->Release();
				}
				
				m_pObj = pObj;
				
				return *this;
			}

		CRef& operator = (TYPE& obj)
			{
				if ( NULL == m_pObj )
					throw Nyx::CException("attempt to assign to a null object");

				*m_pObj = obj;
				
				return *this;
			}
			
		TYPE* operator -> ()
			{
				return m_pObj;
			}

		const TYPE* operator -> () const
			{
				return m_pObj;
			}
			
		operator TYPE* ()
			{
				return m_pObj;
			}
			
		operator TYPE* () const
			{
				return m_pObj;
			}
			
		operator TYPE& ()
			{
				if ( NULL == m_pObj )
					throw Nyx::CException("attempt derefencing a NULL pointer");
				return *m_pObj;
			}
			
		operator const TYPE& () const
			{
				if ( NULL == m_pObj )
					throw Nyx::CException("attempt derefencing a NULL pointer");
				return *m_pObj;
			}
			
		bool operator == (const CRef& ref) const
		{
			return ( m_pObj == ref.m_pObj );
		}
	
	protected: // protected members
	
		TYPE*		m_pObj;
	};


	/**
	 *
	 */
	template <class TYPE>
	class CConstRef
	{
	public:	// public methods
		CConstRef() :
			m_pObj(NULL)
			{
			}

		CConstRef(const CConstRef& ref) :
			m_pObj(ref.m_pObj)
			{
				if ( NULL != m_pObj )
				{
					m_pObj->Retain();
				}
			}

		CConstRef(const TYPE* pObj) :
			m_pObj(pObj)
			{
				if ( NULL != m_pObj )
				{
					m_pObj->Retain();
				}
			}
			
		~CConstRef()
			{
				Release();
			}
			
		void Release()
			{
				if ( NULL != m_pObj )
				{
					m_pObj->Release();
					m_pObj = NULL;
				}
			}
			
		bool Valid() const
		{
			return (NULL != m_pObj);
		}
			
		CConstRef& operator = (const CConstRef& ref)
			{
				if ( NULL != ref.m_pObj )
				{
					ref.m_pObj->Retain();
				}
				
				if ( NULL != m_pObj )
				{
					m_pObj->Release();
				}
				
				m_pObj = ref.m_pObj;
			
				return *this;
			}
			
		CConstRef& operator = (const TYPE* pObj)
			{
				if ( NULL != pObj )
				{
					pObj->Retain();
				}
			
				if ( NULL != m_pObj )
				{
					m_pObj->Release();
				}
				
				m_pObj = pObj;
				
				return *this;
			}

		const TYPE* operator -> () const
			{
				return m_pObj;
			}
			
		operator const TYPE* () const
			{
				return m_pObj;
			}
						
		operator const TYPE& () const
			{
				if ( NULL == m_pObj )
					throw Nyx::CException("attempt derefencing a NULL pointer");
				return *m_pObj;
			}
			
		bool operator == (const CConstRef& ref) const
		{
			return ( m_pObj == ref.m_pObj );
		}
	
	protected: // protected members
	
		const TYPE*		m_pObj;
	};
};



#endif // _NYXREF_HPP_
