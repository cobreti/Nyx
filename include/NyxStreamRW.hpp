#ifndef _NYXSTREAMRW_HPP_
#define _NYXSTREAMRW_HPP_

#include "NyxStreamReader.hpp"
#include "NyxStreamWriter.hpp"

namespace Nyx
{
	class IStreamRW : public Nyx::IStreamReader, public Nyx::IStreamWriter
	{
	};
}


#endif // _NYXSTREAMRW_HPP_
