#pragma once

/*!
 * \file
 *
 * \warning Do not include this file directly.
 * Include "yandex/contest/invoker/Log.hpp" instead.
 */

#include "yandex/contest/Forward.hpp"

#include <sstream>
#include <memory>

namespace yandex{namespace contest{namespace detail
{
    class LogOutputStream
    {
    public:
        LogOutputStream(const LogPointer &log,
                        const Log::Level level,
                        const std::string &position);
        LogOutputStream(const LogOutputStream &)=delete;
        LogOutputStream(LogOutputStream &&)=default;
        LogOutputStream &operator=(const LogOutputStream &)=delete;
        LogOutputStream &operator=(LogOutputStream &&)=default;
        ~LogOutputStream();

        /// Change logging level.
        LogOutputStream &operator<<(const Log::Level level);

        /// Append record to the log.
        template <typename T>
        LogOutputStream &operator<<(const T &obj)
        {
            (*buf_) << obj;
            return *this;
        }

    private:
        LogPointer log_;
        Log::Level level_;
        std::string position_;
        std::unique_ptr<std::ostringstream> buf_;
    };
}}}
