#pragma once

#include <yandex/contest/Error.hpp>

#include <bunsan/system_error.hpp>

namespace yandex{namespace contest
{
    struct SystemError: bunsan::system_error, virtual Error
    {
        using bunsan::system_error::system_error;

        typedef error_code errorCode;
        typedef what_message whatMessage;
    };
}}
