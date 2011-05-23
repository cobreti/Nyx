#ifndef _NYXLOCK_HPP_
#define _NYXLOCK_HPP_

#include "NyxRef.hpp"
#include "NyxMutex.hpp"

namespace Nyx
{
	template <class T>
	class TLock
	{
		typedef		Nyx::CRef<T>	TypeRef;

	public:
		TLock(T* pObj, bool bLock) :
          m_bOwn(bLock),
          m_refObj(pObj)
          {
			  if ( m_bOwn )
				  m_refObj->Lock();
		  }

		~TLock()
		{
			if ( m_bOwn )
				m_refObj->Unlock();
		}


		void Lock()
		{
			m_bOwn = true;
			m_refObj->Lock();
		}
		
	protected:

		bool		m_bOwn;
		TypeRef		m_refObj;
	};

    typedef     TLock<Nyx::CMutex>      TMutexLock;
}


#endif // _NYXLOCK_HPP_
