#include "yandex/contest/detail/StreamLog.hpp"

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/lexical_cast.hpp>

namespace yandex{namespace contest{namespace detail
{
    LogPointer StreamLog::create(std::ostream &out)
    {
        LogPointer ret(new StreamLog(out));
        return ret;
    }

    StreamLog::StreamLog(std::ostream &out):
        out_(out)
    {
    }

    void StreamLog::append_(const Level level, const std::string &position,
                            const std::string &message)
    {
        // hack to output message at once
        std::ostringstream msg;
        msg << '[' << boost::posix_time::microsec_clock::local_time() << "] " <<
               level << " [" << position << "] - " << message << std::endl;
        // here message is actually printed
        out_ << msg.str() << std::flush;
    }
}}}
