#define BOOST_TEST_MODULE LogObject
#include <boost/test/unit_test.hpp>

#include <yandex/contest/detail/LogHelper.hpp>

BOOST_AUTO_TEST_SUITE(Log)

BOOST_AUTO_TEST_CASE(object)
{
    const std::vector<int> x = {1, 2, 3};
    STREAM_INFO << STREAM_OBJECT(x);
}

BOOST_AUTO_TEST_SUITE_END()
