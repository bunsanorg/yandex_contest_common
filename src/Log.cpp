#include "yandex/contest/Log.hpp"

#include "yandex/contest/detail/IntrusivePointerHelper.hpp"
#include "yandex/contest/detail/StreamLog.hpp"

#include <iostream>

namespace yandex{namespace contest
{
    YANDEX_CONTEST_INTRUSIVE_PTR_DEFINE(Log)

    LogPointer Log::instance_ = Log::defaultInstance();

    const LogPointer &Log::instance()
    {
        return instance_;
    }

    void Log::registerInstance(const LogPointer &log)
    {
        instance_ = log;
    }

    const LogPointer &Log::defaultInstance()
    {
        // synchronized by compiler
        static LogPointer logInstance = detail::StreamLog::create(std::clog);
        return logInstance;
    }

    detail::LogOutputStream Log::append(const Level level, const std::string &position)
    {
        return detail::LogOutputStream(LogPointer(this), level, position);
    }
}}
