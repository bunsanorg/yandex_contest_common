#define BOOST_TEST_MODULE Enum
#include <boost/test/unit_test.hpp>

#include "yandex/contest/StreamEnum.hpp"

#include <boost/lexical_cast.hpp>

BOOST_AUTO_TEST_SUITE(Enum)

YANDEX_CONTEST_STREAM_ENUM_CLASS(EnumClass,
(
    FIRST,
    SECOND,
    THIRD
))

BOOST_AUTO_TEST_CASE(Class)
{
    BOOST_CHECK_EQUAL(boost::lexical_cast<std::string>(EnumClass::FIRST), "FIRST");
    BOOST_CHECK_EQUAL(boost::lexical_cast<std::string>(EnumClass::SECOND), "SECOND");
    BOOST_CHECK_EQUAL(boost::lexical_cast<std::string>(EnumClass::THIRD), "THIRD");
    BOOST_CHECK_THROW(boost::lexical_cast<std::string>(static_cast<EnumClass>(100500)), EnumClassInvalidEnumRepresentationError);
    BOOST_CHECK(boost::lexical_cast<EnumClass>("FIRST") == EnumClass::FIRST);
    BOOST_CHECK(boost::lexical_cast<EnumClass>("SECOND") == EnumClass::SECOND);
    BOOST_CHECK(boost::lexical_cast<EnumClass>("THIRD") == EnumClass::THIRD);
    BOOST_CHECK_THROW(boost::lexical_cast<EnumClass>("unknown"), EnumClassInvalidStringRepresentationError);
}

YANDEX_CONTEST_STREAM_ENUM(Enum,
(
    FIRST,
    SECOND,
    THIRD
))

BOOST_AUTO_TEST_CASE(Old)
{
    BOOST_CHECK_EQUAL(boost::lexical_cast<std::string>(FIRST), "FIRST");
    BOOST_CHECK_EQUAL(boost::lexical_cast<std::string>(SECOND), "SECOND");
    BOOST_CHECK_EQUAL(boost::lexical_cast<std::string>(THIRD), "THIRD");
    BOOST_CHECK_THROW(boost::lexical_cast<std::string>(static_cast<Enum>(100500)), EnumInvalidEnumRepresentationError);
    BOOST_CHECK(boost::lexical_cast<Enum>("FIRST") == FIRST);
    BOOST_CHECK(boost::lexical_cast<Enum>("SECOND") == SECOND);
    BOOST_CHECK(boost::lexical_cast<Enum>("THIRD") == THIRD);
    BOOST_CHECK_THROW(boost::lexical_cast<Enum>("unknown"), EnumInvalidStringRepresentationError);
}

BOOST_AUTO_TEST_SUITE_END()
