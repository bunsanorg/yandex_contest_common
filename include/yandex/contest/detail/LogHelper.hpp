#pragma once

#include "yandex/contest/Log.hpp"

#include "yandex/contest/Log.hpp"

#include <boost/current_function.hpp>
#include <boost/lexical_cast.hpp>

/*!
 * \file
 *
 * Useful defines for logging.
 * These defines determine logging position.
 *
 * \section append_iface_sec append() interface
 * APPEND_{Level} defines accept single argument: std::string (or implicitly convertible to) message.
 * \code{.cpp}
 * APPEND_INFO("I am info message!");
 * \endcode
 *
 * \section streaming_iface_sec streaming interface
 * STREAM_{Level} defines accept no arguments.
 * Using operator<< user can output anything supported by std::ostream.
 * To output yandex::contest::config-serializable object use STREAM_OBJECT() wrapper.
 * \code{.cpp}
 * std::vector<int> x = {1, 2, 3};
 * STREAM_INFO << "First part " << 123 << " one more string " << STREAM_OBJECT(obj);
 * \endcode
 *
 * \see ::yandex::contest::Log::append
 *
 * \warning Do not include it in header files.
 */

// common

#define LOG_CURRENT_POSITION (std::string(BOOST_CURRENT_FUNCTION) + std::string(":") + boost::lexical_cast<std::string>(__LINE__))

// Using append() interface.

#define APPEND_LOG(LEVEL, MESSAGE) ::yandex::contest::Log::instance()->append(LEVEL, LOG_CURRENT_POSITION, MESSAGE)
#define APPEND_LOG_BYNAME(LEVEL, MESSAGE) APPEND_LOG(::yandex::contest::contest::invoker::Log::Level::LEVEL, MESSAGE)

#define APPEND_TRACE(MESSAGE) APPEND_LOG_LOG_BYNAME(TRACE, MESSAGE)
#define APPEND_DEBUG(MESSAGE) APPEND_LOG_LOG_BYNAME(DEBUG, MESSAGE)
#define APPEND_INFO(MESSAGE) APPEND_LOG_LOG_BYNAME(INFO, MESSAGE)
#define APPEND_WARNING(MESSAGE) APPEND_LOG_LOG_BYNAME(WARNING, MESSAGE)
#define APPEND_ERROR(MESSAGE) APPEND_LOG_LOG_BYNAME(ERROR, MESSAGE)

// Using streaming interface.

#define STREAM_LOG(LEVEL) ::yandex::contest::Log::instance()->append(LEVEL, LOG_CURRENT_POSITION)
#define STREAM_LOG_BYNAME(LEVEL) STREAM_LOG(::yandex::contest::Log::Level::LEVEL)

#define STREAM_TRACE STREAM_LOG_BYNAME(TRACE)
#define STREAM_DEBUG STREAM_LOG_BYNAME(DEBUG)
#define STREAM_INFO STREAM_LOG_BYNAME(INFO)
#define STREAM_WARNING STREAM_LOG_BYNAME(WARNING)
#define STREAM_ERROR STREAM_LOG_BYNAME(ERROR)

#define STREAM_OBJECT(X) ::yandex::contest::detail::LogOutputStream::object(X)
