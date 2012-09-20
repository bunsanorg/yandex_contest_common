#include "yandex/contest/TypeInfo.hpp"

#include <boost/scope_exit.hpp>

#include <cxxabi.h>

namespace yandex{namespace contest{namespace typeinfo
{
    std::string demangle(const char *const name)
    {
        char *realname = nullptr;
        BOOST_SCOPE_EXIT_ALL(realname)
        {
            if (realname)
                std::free(realname);
        };

        std::size_t len;
        int stat;

        realname = abi::__cxa_demangle(name, nullptr, &len, &stat);

        if (realname)
            return std::string(realname);
        else
            return name;
    }

    std::string demangle(const std::string &name)
    {
        return demangle(name.c_str());
    }
}}}
