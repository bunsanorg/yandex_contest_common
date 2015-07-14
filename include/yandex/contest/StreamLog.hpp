#pragma once

#include <yandex/contest/detail/LogObject.hpp>
#include <yandex/contest/Log.hpp>

#include <bunsan/log/trivial.hpp>

/*!
 * \file
 *
 * Useful defines for logging.
 * These defines determine logging position.
 *
 * \section streaming_iface_sec streaming interface
 * STREAM_{Level} defines accept no arguments.
 * Using operator<< user can output anything supported by std::ostream.
 * To output yandex::contest::config-serializable object use STREAM_OBJECT()
 * wrapper.
 * \code{.cpp}
 * std::vector<int> x = {1, 2, 3};
 * STREAM_INFO << "First part " << 123 << " one more string " <<
 *             << STREAM_OBJECT(obj);
 * \endcode
 */

#define STREAM_TRACE BUNSAN_LOG_TRACE
#define STREAM_DEBUG BUNSAN_LOG_DEBUG
#define STREAM_INFO BUNSAN_LOG_INFO
#define STREAM_WARNING BUNSAN_LOG_WARNING
#define STREAM_ERROR BUNSAN_LOG_ERROR
#define STREAM_FATAL BUNSAN_LOG_FATAL

#define STREAM_OBJECT(X) ::yandex::contest::detail::makeLogObject(X)
