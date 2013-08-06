#pragma once

/*!
 * \file
 *
 * \warning Do not include this file directly.
 * Include "yandex/contest/invoker/Log.hpp" instead.
 */

#include <yandex/contest/Forward.hpp>

#include <yandex/contest/TypeInfo.hpp>

#include <bunsan/config/output_archive.hpp>

#include <sstream>
#include <memory>

#include <boost/property_tree/ptree.hpp>

namespace yandex{namespace contest{namespace detail
{
    class LogOutputStream
    {
    public:
        template <typename T>
        class Object
        {
        public:
            explicit Object(const T &ref):
                ref_(ref) {}

            const T &operator*() const
            {
                return ref_;
            }

        private:
            const T &ref_;
        };

        template <typename T>
        static Object<T> object(const T &obj)
        {
            return Object<T>(obj);
        }

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

        template <typename T>
        LogOutputStream &operator<<(const Object<T> &obj)
        {
            boost::property_tree::ptree ptree;
            bunsan::config::output_archive<boost::property_tree::ptree>::save_to_ptree(
                boost::serialization::make_nvp(typeinfo::name(*obj).c_str(), *obj), ptree);
            append(ptree);
            return *this;
        }

    private:
        void append(const boost::property_tree::ptree &ptree);

    private:
        LogPointer log_;
        Log::Level level_;
        std::string position_;
        std::unique_ptr<std::ostringstream> buf_;
    };
}}}
