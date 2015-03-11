#pragma once

#include <yandex/contest/Forward.hpp>
#include <yandex/contest/IntrusivePointeeBase.hpp>

#include <bunsan/stream_enum.hpp>

#include <boost/noncopyable.hpp>

#include <string>

namespace yandex{namespace contest
{
    namespace detail
    {
        class LogOutputStream;
    }

    /*!
     * \warning Do not create Log object on stack (behavior is undefined).
     * Use LogPointer object and heap-allocation.
     */
    class Log: public IntrusivePointeeBase
    {
    public:
        BUNSAN_INCLASS_STREAM_ENUM_CLASS(Level,
        (
            TRACE,
            DEBUG,
            INFO,
            WARNING,
            ERROR
        ))

    public:
        /*!
         * \brief Append new message to the log.
         *
         * Function is thread-safe.
         */
        virtual void append(const Level level, const std::string &position,
                            const std::string &message) noexcept=0;

        /*!
         * \brief Append new message to the log using streaming interface.
         *
         * This function returns special object with redefined "operator<<".
         * User can prepare log message using streaming interface.
         * This object will output everything on destruction.
         *
         * \code{.cpp}
         * log.append(Log::Level::DEBUG, "int main()") << "Hello, " << "world!";
         * \endcode
         *
         * \note This function does not append message to the log and may throw.
         *
         * \warning Do not store returned object.
         */
        detail::LogOutputStream append(const Level level, const std::string &position);

        /*!
         * \brief Global log instance.
         *
         * If no global instance was registered,
         * defaultInstance() is used.
         *
         * \warning Function is not thread-safe.
         *
         * \see defaultInstance
         * \see registerInstance
         */
        static const LogPointer &instance();

        /*!
         * \brief Register global instance.
         *
         * \warning Function is not thread-safe.
         *
         * \see instance
         */
        static void registerInstance(const LogPointer &log);

        /*!
         * \brief Disable logging.
         *
         * \note Logging can be enabled again by registering another instance.
         *
         * \warning Function is not thread-safe.
         */
        static void disableLogging();

        /*!
         * \brief Default log instance.
         *
         * This instance uses std::clog for logging.
         *
         * \note Function is thread-safe.
         */
        static const LogPointer &defaultInstance();

    private:
        static LogPointer instance_;
    };
}}

// This include should be placed after ::yandex::Log declaration.
#include <yandex/contest/detail/LogOutputStream.hpp>
