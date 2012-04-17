#ifndef _NYXBASE_NYXINTERFACEREF_HPP_
#define _NYXBASE_NYXINTERFACEREF_HPP_


namespace Nyx
{
    template <class INTERFACE, class OWNER>
    class CInterfaceRef
    {
    public:
        CInterfaceRef() : m_pInterface(NULL), m_pOwner(NULL) {}

        CInterfaceRef( OWNER* pOwner ) :
            m_pInterface(NULL),
            m_pOwner(pOwner)
        {
            m_pOwner->Lock(m_pInterface);
        }
        
        CInterfaceRef( OWNER& rOwner ) :
        m_pInterface(NULL),
        m_pOwner(&rOwner)
        {
            m_pOwner->Lock(m_pInterface);
        }

        ~CInterfaceRef()
        {
            Release();
        }
        
        bool Valid() const { return m_pInterface != NULL; }
        
        const CInterfaceRef& operator = (OWNER& Owner)
        {
            Set(&Owner);
            return *this;
        }
        
        const CInterfaceRef& operator = (OWNER* pOwner)
        {
            Set(pOwner);
            return *this;
        }

		INTERFACE* operator -> ()
        {
            return m_pInterface;
        }
        
		const INTERFACE* operator -> () const
        {
            return m_pInterface;
        }

    protected:
        
        void Release()
        {
            if ( m_pInterface && m_pOwner )
            {
                m_pOwner->Unlock(m_pInterface);
                m_pInterface = NULL;
            }
        }
        
        void Set( OWNER* pOwner )
        {
            Release();
            
            m_pOwner = pOwner;
            if ( m_pOwner )
                m_pOwner->Lock(m_pInterface);
        }
        
        
    protected:
        
        INTERFACE*      m_pInterface;
        OWNER*          m_pOwner;
    };
}


#endif // _NYXBASE_NYXINTERFACEREF_HPP_

