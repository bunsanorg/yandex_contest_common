#pragma once

#include <yandex/contest/Error.hpp>

#include <sstream>

namespace yandex{namespace contest
{
    namespace detail
    {
        template <typename X, typename T>
        struct StringStreamCastImpl
        {
            static X cast(const T &obj)
            {
                std::stringstream buf;
                buf << obj;
                X x;
                buf >> x;
                return x;
            }
        };

        template <typename T>
        struct StringStreamCastImpl<std::string, T>
        {
            static std::string cast(const T &obj)
            {
                std::ostringstream buf;
                buf << obj;
                return buf.str();
            }
        };
    }

    template <typename X, typename T>
    inline X stringstream_cast(const T &obj)
    {
        return detail::StringStreamCastImpl<X, T>::cast(obj);
    }
}}
