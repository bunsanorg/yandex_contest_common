#define BOOST_TEST_MODULE Log
#include <boost/test/unit_test.hpp>

#include <yandex/contest/Log.hpp>

using namespace yandex::contest;

namespace
{
    struct MockLog: public Log
    {
        virtual void append(const Level /*level*/, const std::string &/*position*/,
                            const std::string &/*message*/) noexcept override
        {
            ++count;
        }

        std::size_t count = 0;
    };
}

BOOST_AUTO_TEST_SUITE(LogOutputStream)

BOOST_AUTO_TEST_CASE(move)
{
    LogPointer log(new MockLog);
    {
        detail::LogOutputStream logOutputStream = log->append(Log::Level::INFO, "");
        detail::LogOutputStream logOutputStream2 = std::move(logOutputStream);
    }
    BOOST_CHECK_EQUAL(static_cast<MockLog *>(log.get())->count, 1);
}

BOOST_AUTO_TEST_SUITE_END()
