#include <Windows.h>
#include "NyxFixedString.hpp"

#include <strsafe.h>


namespace Nyx
{
    /**
     *
     */
    size_t TFixedString_Format(char* pBuffer, size_t buffer_size, const char* szFormat, va_list vl )
    {
        HRESULT hr = StringCbVPrintfA( pBuffer, buffer_size, szFormat, vl );

        if ( SUCCEEDED(hr) )
            return strlen(pBuffer);

        return 0;
    }

}
