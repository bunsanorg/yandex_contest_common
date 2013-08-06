#include <yandex/contest/detail/NullLog.hpp>

namespace yandex{namespace contest{namespace detail
{
    void NullLog::append(const Level /*level*/, const std::string &/*position*/,
                         const std::string &/*message*/) noexcept
    {
        // does nothing
    }
}}}
