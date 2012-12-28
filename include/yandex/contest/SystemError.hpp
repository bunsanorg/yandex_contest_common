#pragma once

#include "yandex/contest/Error.hpp"

#include "bunsan/system_error.hpp"
#include "bunsan/forward_constructor.hpp"

namespace yandex{namespace contest
{
    struct SystemError: virtual Error, virtual bunsan::system_error
    {
        BUNSAN_INHERIT_EXPLICIT_CONSTRUCTOR(SystemError, bunsan::system_error)

        typedef error_code errorCode;
        typedef error_code_message errorCodeMessage;
        typedef what_message whatMessage;
    };
}}
