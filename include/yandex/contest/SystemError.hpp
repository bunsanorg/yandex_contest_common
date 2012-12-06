#pragma once

#include "yandex/contest/Error.hpp"

#include "bunsan/system_error.hpp"

#include <utility>

namespace yandex{namespace contest
{
    struct SystemError: virtual Error, virtual bunsan::system_error
    {
        template <typename ... Args>
        explicit SystemError(Args &&...args): bunsan::system_error(std::forward<Args>(args)...) {}

        typedef error_code errorCode;
        typedef error_code_message errorCodeMessage;
        typedef what_message whatMessage;
    };
}}
