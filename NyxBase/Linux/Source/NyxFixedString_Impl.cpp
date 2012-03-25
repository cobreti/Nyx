#include "NyxFixedString.hpp"

#include <stdio.h>
#include <stdarg.h>


namespace Nyx
{
    /**
     *
     */
    size_t TFixedString_Format(char* pBuffer, size_t buffer_size, const char* szFormat, va_list vl )
    {
        return vsprintf( pBuffer, szFormat, vl );
    }

}
