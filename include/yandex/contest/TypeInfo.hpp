#pragma once

#include <string>
#include <typeinfo>

namespace yandex{namespace contest{namespace typeinfo
{
    std::string demangle(const char *const name);
    std::string demangle(const std::string &name);

    template <typename T>
    std::string name(const T &obj)
    {
        return demangle(typeid(obj).name());
    }
}}}
