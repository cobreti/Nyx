#ifndef _NYXTHREADMODULE_HPP_
#define _NYXTHREADMODULE_HPP_


namespace Nyx
{
	class CThreadModule
	{
	public:

		/**
		 *
		 */
		virtual void Init() = 0;

		/**
		 *
		 */
		virtual void Terminate() = 0;

		/**
		 *
		 */
		virtual void* GetThreadUserData() = 0;

		/**
		 *
		 */
		virtual void SetThreadUserData(void* pData) = 0;
	};
}



#endif // _NYXTHREADMODULE_HPP_
