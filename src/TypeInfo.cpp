#include "yandex/contest/TypeInfo.hpp"

#include <boost/units/detail/utility.hpp>

namespace yandex{namespace contest{namespace typeinfo
{
    std::string demangle(const char *const name)
    {
        return boost::units::detail::demangle(name);
    }

    std::string demangle(const std::string &name)
    {
        return demangle(name.c_str());
    }
}}}
