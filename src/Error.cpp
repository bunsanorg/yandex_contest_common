#include "yandex/contest/Error.hpp"

namespace yandex{namespace contest
{
    Error::Error(const std::string &message_)
    {
        (*this) << message(message_);
    }

    const char *Error::what() const noexcept
    {
        return boost::diagnostic_information_what(*this);
    }
}}
