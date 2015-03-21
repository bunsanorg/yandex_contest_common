#pragma once

#include <yandex/contest/TypeInfo.hpp>

#include <bunsan/config/cast.hpp>

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include <ostream>

namespace yandex{namespace contest{namespace detail
{
    template <typename T>
    class LogObject
    {
    public:
        explicit LogObject(const T &ref):
            ref_(ref) {}

        const T &operator*() const
        {
            return ref_;
        }

    private:
        const T &ref_;
    };

    template <typename T>
    static LogObject<T> makeLogObject(const T &obj)
    {
        return LogObject<T>(obj);
    }

    template <typename T>
    std::ostream &operator<<(std::ostream &out, const LogObject<T> &obj)
    {
        const auto ptree = bunsan::config::save<boost::property_tree::ptree>(
            boost::serialization::make_nvp(typeinfo::name(*obj).c_str(), *obj)
        );
        boost::property_tree::write_json(out, ptree);
        return out;
    }
}}}
