#define BOOST_TEST_MODULE Log
#include <boost/test/unit_test.hpp>

#include <yandex/contest/StreamLog.hpp>

#include <boost/date_time/posix_time/posix_time_types.hpp>

namespace ya = yandex::contest;

BOOST_AUTO_TEST_SUITE(Log)

struct LogFunction
{
    static int count;
    static const char *msg[];

    static void reset() { count = 0; }

    void operator()(const boost::posix_time::ptime &timestamp,
                    const ya::Log::Level level,
                    const std::string &position,
                    const std::string &message) const
    {
        const boost::posix_time::ptime now = boost::posix_time::second_clock::local_time();
        const boost::posix_time::ptime min = now - boost::posix_time::seconds(10);
        const boost::posix_time::ptime max = now + boost::posix_time::seconds(10);

        BOOST_CHECK(min <= timestamp && timestamp <= max);
        BOOST_CHECK(!position.empty());
        BOOST_CHECK_EQUAL(level, static_cast<ya::Log::Level>(count));
        BOOST_CHECK_EQUAL(message, msg[count]);
        ++count;
    }
};

int LogFunction::count = 0;
const char *LogFunction::msg[] = {
    "Trace",
    "Debug",
    "Info",
    "Warning",
    "Error",
    "Fatal"
};

BOOST_AUTO_TEST_CASE(setFunction)
{
    LogFunction::reset();
    ya::Log::setFunction(LogFunction());
    BOOST_CHECK_EQUAL(LogFunction::count, 0);
    STREAM_TRACE << "Trace";
    BOOST_CHECK_EQUAL(LogFunction::count, 1);
    STREAM_DEBUG << "Debug";
    BOOST_CHECK_EQUAL(LogFunction::count, 2);
    STREAM_INFO << "Info";
    BOOST_CHECK_EQUAL(LogFunction::count, 3);
    STREAM_WARNING << "Warning";
    BOOST_CHECK_EQUAL(LogFunction::count, 4);
    STREAM_ERROR << "Error";
    BOOST_CHECK_EQUAL(LogFunction::count, 5);
    STREAM_FATAL << "Fatal";
    BOOST_CHECK_EQUAL(LogFunction::count, 6);
}

BOOST_AUTO_TEST_CASE(setMinimumLevel)
{
    LogFunction::reset();
    ya::Log::setFunction(LogFunction());
    ya::Log::setMinimumLevel(ya::Log::Level::INFO);
    BOOST_CHECK_EQUAL(LogFunction::count, 0);
    STREAM_TRACE << "Trace";
    BOOST_CHECK_EQUAL(LogFunction::count, 0);
    STREAM_DEBUG << "Debug";
    BOOST_CHECK_EQUAL(LogFunction::count, 0);
    LogFunction::count = 2;
    STREAM_INFO << "Info";
    BOOST_CHECK_EQUAL(LogFunction::count, 3);
    STREAM_WARNING << "Warning";
    BOOST_CHECK_EQUAL(LogFunction::count, 4);
    STREAM_ERROR << "Error";
    BOOST_CHECK_EQUAL(LogFunction::count, 5);
    STREAM_FATAL << "Fatal";
    BOOST_CHECK_EQUAL(LogFunction::count, 6);
    ya::Log::setMinimumLevel(ya::Log::Level::TRACE);
}

BOOST_AUTO_TEST_CASE(disableLogging)
{
    LogFunction::reset();
    ya::Log::setFunction(LogFunction());
    BOOST_CHECK_EQUAL(LogFunction::count, 0);
    STREAM_TRACE << "Trace";
    BOOST_CHECK_EQUAL(LogFunction::count, 1);
    STREAM_DEBUG << "Debug";
    BOOST_CHECK_EQUAL(LogFunction::count, 2);
    ya::Log::disableLogging();
    STREAM_INFO << "Info";
    BOOST_CHECK_EQUAL(LogFunction::count, 2);
    STREAM_WARNING << "Warning";
    BOOST_CHECK_EQUAL(LogFunction::count, 2);
    STREAM_ERROR << "Error";
    BOOST_CHECK_EQUAL(LogFunction::count, 2);
    STREAM_FATAL << "Fatal";
    BOOST_CHECK_EQUAL(LogFunction::count, 2);
    ya::Log::enableLogging();
    STREAM_INFO << "Info";
    BOOST_CHECK_EQUAL(LogFunction::count, 3);
    STREAM_WARNING << "Warning";
    BOOST_CHECK_EQUAL(LogFunction::count, 4);
    STREAM_ERROR << "Error";
    BOOST_CHECK_EQUAL(LogFunction::count, 5);
    STREAM_FATAL << "Fatal";
    BOOST_CHECK_EQUAL(LogFunction::count, 6);
}

BOOST_AUTO_TEST_SUITE_END() // Log
