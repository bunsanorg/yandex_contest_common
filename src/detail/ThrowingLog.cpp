#include <yandex/contest/detail/ThrowingLog.hpp>

namespace yandex{namespace contest{namespace detail
{
    void ThrowingLog::append(const Level level, const std::string &position,
                             const std::string &message) noexcept
    {
        try
        {
            append_(level, position, message);
        }
        catch (...)
        {
            // does nothing
        }
    }
}}}
