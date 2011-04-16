#ifndef _NYXMSGBUCKET_HPP_
#define _NYXMSGBUCKET_HPP_


namespace NyxOSX
{
	class CActiveObject_Impl;
}

namespace Nyx
{
	class CMsg;

	/**
	 *
	 */
	class CMsgBucket
	{
		friend class NyxOSX::CActiveObject_Impl;
	
	public:
		CMsgBucket() : m_pMsg(NULL) {}
		virtual ~CMsgBucket() {}
		
	protected:
		
		Nyx::CMsg*		m_pMsg;
	};
	
	
	/**
	 *
	 */
	template <class TYPE>
	class TMsgBucket : public Nyx::CMsgBucket
	{
	public:
		TMsgBucket()
		{
			m_pMsg = new TYPE();
		}
		
		virtual ~TMsgBucket()
		{
			if ( NULL != m_pMsg )
				delete m_pMsg;
		}
		
		TYPE* operator -> () { return (TYPE*)m_pMsg; }
	};
};


#endif // _NYXMSGBUCKET_HPP_

