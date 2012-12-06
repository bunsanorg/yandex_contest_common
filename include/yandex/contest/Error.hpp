#pragma once

#include "bunsan/error.hpp"

#include <utility>

namespace yandex{namespace contest
{
    /// Base error class for Yandex.Contest.Invoker project.
    struct Error: virtual bunsan::error
    {
        template <typename ... Args>
        explicit Error(Args &&...args): bunsan::error(std::forward<Args>(args)...) {}
    };
}}
