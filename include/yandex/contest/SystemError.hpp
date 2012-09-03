#pragma once

#include "yandex/contest/Error.hpp"

#include <system_error>

namespace yandex{namespace contest
{
    struct SystemError: virtual Error
    {
        SystemError();
        explicit SystemError(const int errcode);
        explicit SystemError(const std::error_code &ec);
        explicit SystemError(const std::string &what);
        SystemError(const int errcode, const std::string &what);
        SystemError(const std::error_code &ec, const std::string &what);

        typedef boost::error_info<struct errorCodeTag, std::error_code> errorCode;
        typedef boost::error_info<struct errorCodeMessageTag, std::string> errorCodeMessage;
        typedef boost::error_info<struct whatMessageTag, std::string> whatMessage;
    };
}}
