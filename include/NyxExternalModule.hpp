#ifndef _NYXEXTERNALMODULE_HPP_
#define _NYXEXTERNALMODULE_HPP_

#include "NyxObject.hpp"
#include "NyxRef.hpp"

DECLARE_NYXOBJECTREF(CExternalModule)

namespace Nyx
{
	/**
	 *
	 */
	class CExternalModule : public Nyx::CObject
	{
	public:

		static CExternalModule* Alloc(const char* szModule);

	public:

		virtual NyxResult Load() = 0;
		virtual NyxResult Unload() = 0;
		virtual void* GetFct(const char* name) = 0;
        virtual ExternalModuleHandle GetHandle() const = 0;
        virtual bool Valid() const = 0;
	};
}

#endif // _NYXEXTERNALMODULE_HPP_
