#ifndef _NYXBODYBLOCK_HPP_
#define _NYXBODYBLOCK_HPP_

#include "NyxTraces.hpp"
#include "NyxResException.hpp"


/**
 *
 */
#define		NyxBeginBody(_name)				{\
												const char* ksznyxbodyname = _name;\
												try\
												{

/**
 *
 */
#define		NyxEndBody(_resultvar)				}\
												catch( Nyx::CResException& ex )\
												{\
													Nyx::CTraceStream(0x0) << Nyx::CTF_Text(L"error in block '")\
													<< Nyx::CTF_AnsiText(ksznyxbodyname) << Nyx::CTF_Text(L"' : ")\
													<< Nyx::CTF_AnsiText(ex.Msg());\
													_resultvar = ex.Result();\
												}\
												catch( Nyx::CException& ex)\
												{\
													Nyx::CTraceStream(0x0) << Nyx::CTF_Text(L"error in block '")\
													<< Nyx::CTF_AnsiText(ksznyxbodyname) << Nyx::CTF_Text(L"' : ")\
													<< Nyx::CTF_AnsiText(ex.Msg());\
												}\
												catch(...)\
												{\
													Nyx::CTraceStream(0x0) << Nyx::CTF_Text(L"Unknown error in block '")\
													<< Nyx::CTF_AnsiText(ksznyxbodyname) << Nyx::CTF_Text(L"'");\
													_resultvar = Nyx::kNyxRes_Failure;\
												}\
											}


namespace Nyx
{
	/**
	 *
	 */
	inline void HandleErrorOnCond( bool bCond, const char* szErrorMsg, const Nyx::NyxResult& res = Nyx::kNyxRes_Failure )
	{
		if ( bCond )
			throw Nyx::CResException(szErrorMsg, res);
	}
}


#endif // _NYXBODYBLOCK_HPP_

