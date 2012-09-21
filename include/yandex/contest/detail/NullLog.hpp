#pragma once

#include "yandex/contest/Log.hpp"

namespace yandex{namespace contest{namespace detail
{
    /// /dev/null analog for Log.
    class NullLog: public Log
    {
    public:
        /// Wraps append_() in try {} catch {}.
        virtual void append(const Level level, const std::string &position,
                            const std::string &message) noexcept override;
    };
}}}
