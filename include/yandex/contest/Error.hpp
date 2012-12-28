#pragma once

#include "bunsan/error.hpp"
#include "bunsan/forward_constructor.hpp"

namespace yandex{namespace contest
{
    /// Base error class for Yandex.Contest.Invoker project.
    struct Error: virtual bunsan::error
    {
        BUNSAN_INHERIT_EXPLICIT_CONSTRUCTOR(Error, bunsan::error)
    };
}}
