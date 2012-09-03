#define BOOST_TEST_MODULE stringstream_cast
#include <boost/test/unit_test.hpp>

#include "yandex/contest/StringStreamCast.hpp"

namespace ya = yandex::contest;

BOOST_AUTO_TEST_SUITE(stringstream_cast)

BOOST_AUTO_TEST_CASE(string)
{
    BOOST_CHECK_EQUAL(ya::stringstream_cast<std::string>(15), "15");
    BOOST_CHECK_EQUAL(ya::stringstream_cast<std::string>("some string"), "some string");
}

BOOST_AUTO_TEST_CASE(arbitrary)
{
    BOOST_CHECK_EQUAL(ya::stringstream_cast<int>("15"), 15);
    // BOOST_CHECK_THROW(ya::stringstream_cast<int>("1 2"), ya::StringStreamCastNotEofError);
}

BOOST_AUTO_TEST_SUITE_END()
