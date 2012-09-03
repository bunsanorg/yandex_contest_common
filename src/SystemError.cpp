#include "yandex/contest/SystemError.hpp"

namespace yandex{namespace contest
{
    SystemError::SystemError():
        SystemError(errno) {}

    SystemError::SystemError(const std::string &what):
        SystemError()
    {
        (*this) << whatMessage(what);
    }

    SystemError::SystemError(const int errcode):
        SystemError(std::error_code(errcode, std::system_category())) {}

    SystemError::SystemError(const int errcode, const std::string &what):
        SystemError(std::error_code(errcode, std::system_category()), what) {}

    SystemError::SystemError(const std::error_code &ec)
    {
        (*this) << errorCode(ec) << errorCodeMessage(ec.message());
    }

    SystemError::SystemError(const std::error_code &ec, const std::string &what):
        SystemError(ec)
    {
        (*this) << whatMessage(what);
    }
}}
