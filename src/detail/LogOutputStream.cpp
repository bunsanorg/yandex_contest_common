//#include <yandex/contest/detail/LogOutputStream.hpp>

#include <yandex/contest/Log.hpp>

#include <boost/assert.hpp>
#include <boost/property_tree/json_parser.hpp>

namespace yandex{namespace contest{namespace detail
{
    LogOutputStream::LogOutputStream(const LogPointer &log, const Log::Level level, const std::string &position):
        log_(log),
        level_(level),
        position_(position)
    {
        BOOST_ASSERT(log_);
        buf_.reset(new std::ostringstream);
    }

    LogOutputStream::~LogOutputStream()
    {
        if (buf_)
            log_->append(level_, position_, buf_->str());
    }

    LogOutputStream &LogOutputStream::operator<<(const Log::Level level)
    {
        level_ = level;
        return *this;
    }

    void LogOutputStream::append(const boost::property_tree::ptree &ptree)
    {
        boost::property_tree::write_json(*buf_, ptree);
    }
}}}
