#ifndef __STD_TYPE_H
#define __STD_TYPE_H

#include <type_traits>

namespace clib
{
    namespace type
    {
        using int8 = signed __int8;
        using uint8 = unsigned __int8;
        using int16 = signed __int16;
        using uint16 = unsigned __int16;
        using int32 = signed __int32;
        using uint32 = unsigned __int32;
        using int64 = signed __int64;
        using uint64 = unsigned __int64;

#ifdef _WIN32
        using sint = int32;
        using uint = uint32;
#else
        using sint = int64;
        using uint = uint64;
#endif

        using byte = uint8;
        using size_t = uint;
    }
}

#endif