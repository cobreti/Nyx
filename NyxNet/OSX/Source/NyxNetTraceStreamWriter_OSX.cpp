#include "NyxNetTraceStreamWriter.hpp"
#include "NyxNetTraceFlags.hpp"

namespace NyxNet
{
    NyxNet::TraceFlags CTraceStreamWriter::TraceFlags() const
    {
        return TFlags_OSX;
    }
}

