#pragma once

#include <bunsan/stream_enum.hpp>

#include <boost/date_time/posix_time/ptime.hpp>

#include <functional>
#include <string>

namespace yandex{namespace contest
{
    class Log
    {
    public:
        BUNSAN_INCLASS_STREAM_ENUM_CLASS(Level,
        (
            TRACE,
            DEBUG,
            INFO,
            WARNING,
            ERROR,
            FATAL
        ))

        typedef std::function<void (const boost::posix_time::ptime &timestamp,
                                    Level level,
                                    const std::string &position,
                                    const std::string &message)> Function;

    public:
        static void setFunction(const Function &function);

        /// Drop all log entries with smaller level.
        static void setMinimumLevel(const Level level);

        /// Enable previously disabled logging.
        static void enableLogging();

        /// Completely disable logging, must be called in forked process.
        static void disableLogging();
    };
}}
