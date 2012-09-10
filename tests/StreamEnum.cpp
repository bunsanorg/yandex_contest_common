#define BOOST_TEST_MODULE Enum
#include <boost/test/unit_test.hpp>

#include "yandex/contest/StreamEnum.hpp"

#include <boost/lexical_cast.hpp>

BOOST_AUTO_TEST_SUITE(stream_enum)

BOOST_AUTO_TEST_SUITE(free)

BOOST_AUTO_TEST_SUITE(class_)

YANDEX_CONTEST_STREAM_ENUM_CLASS(Enum,
(
    FIRST,
    SECOND,
    THIRD
))

BOOST_AUTO_TEST_CASE(test)
{
    BOOST_CHECK_EQUAL(boost::lexical_cast<std::string>(Enum::FIRST), "FIRST");
    BOOST_CHECK_EQUAL(boost::lexical_cast<std::string>(Enum::SECOND), "SECOND");
    BOOST_CHECK_EQUAL(boost::lexical_cast<std::string>(Enum::THIRD), "THIRD");
    BOOST_CHECK_THROW(boost::lexical_cast<std::string>(static_cast<Enum>(100500)), EnumInvalidEnumRepresentationError);
    BOOST_CHECK(boost::lexical_cast<Enum>("FIRST") == Enum::FIRST);
    BOOST_CHECK(boost::lexical_cast<Enum>("SECOND") == Enum::SECOND);
    BOOST_CHECK(boost::lexical_cast<Enum>("THIRD") == Enum::THIRD);
    BOOST_CHECK_THROW(boost::lexical_cast<Enum>("unknown"), EnumInvalidStringRepresentationError);
}

BOOST_AUTO_TEST_SUITE_END() // class_

BOOST_AUTO_TEST_SUITE(old)

YANDEX_CONTEST_STREAM_ENUM(Enum,
(
    FIRST,
    SECOND,
    THIRD
))

BOOST_AUTO_TEST_CASE(test)
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

BOOST_AUTO_TEST_SUITE_END() // old

BOOST_AUTO_TEST_SUITE_END() // free

BOOST_AUTO_TEST_SUITE(in_class)

BOOST_AUTO_TEST_SUITE(class_)

struct Struct
{
    YANDEX_CONTEST_STREAM_INCLASS_ENUM_CLASS(Enum,
    (
        FIRST,
        SECOND,
        THIRD
    ))
};

BOOST_AUTO_TEST_CASE(test)
{
    BOOST_CHECK_EQUAL(boost::lexical_cast<std::string>(Struct::Enum::FIRST), "FIRST");
    BOOST_CHECK_EQUAL(boost::lexical_cast<std::string>(Struct::Enum::SECOND), "SECOND");
    BOOST_CHECK_EQUAL(boost::lexical_cast<std::string>(Struct::Enum::THIRD), "THIRD");
    BOOST_CHECK_THROW(boost::lexical_cast<std::string>(static_cast<Struct::Enum>(100500)), Struct::EnumInvalidEnumRepresentationError);
    BOOST_CHECK(boost::lexical_cast<Struct::Enum>("FIRST") == Struct::Enum::FIRST);
    BOOST_CHECK(boost::lexical_cast<Struct::Enum>("SECOND") == Struct::Enum::SECOND);
    BOOST_CHECK(boost::lexical_cast<Struct::Enum>("THIRD") == Struct::Enum::THIRD);
    BOOST_CHECK_THROW(boost::lexical_cast<Struct::Enum>("unknown"), Struct::EnumInvalidStringRepresentationError);
}

BOOST_AUTO_TEST_SUITE_END() // class_

BOOST_AUTO_TEST_SUITE(old)

struct Struct
{
    YANDEX_CONTEST_STREAM_INCLASS_ENUM(Enum,
    (
        FIRST,
        SECOND,
        THIRD
    ))
};

BOOST_AUTO_TEST_CASE(test)
{
    BOOST_CHECK_EQUAL(boost::lexical_cast<std::string>(Struct::FIRST), "FIRST");
    BOOST_CHECK_EQUAL(boost::lexical_cast<std::string>(Struct::SECOND), "SECOND");
    BOOST_CHECK_EQUAL(boost::lexical_cast<std::string>(Struct::THIRD), "THIRD");
    BOOST_CHECK_THROW(boost::lexical_cast<std::string>(static_cast<Struct::Enum>(100500)), Struct::EnumInvalidEnumRepresentationError);
    BOOST_CHECK(boost::lexical_cast<Struct::Enum>("FIRST") == Struct::FIRST);
    BOOST_CHECK(boost::lexical_cast<Struct::Enum>("SECOND") == Struct::SECOND);
    BOOST_CHECK(boost::lexical_cast<Struct::Enum>("THIRD") == Struct::THIRD);
    BOOST_CHECK_THROW(boost::lexical_cast<Struct::Enum>("unknown"), Struct::EnumInvalidStringRepresentationError);
}

BOOST_AUTO_TEST_SUITE_END() // old

BOOST_AUTO_TEST_SUITE_END() // in_class

BOOST_AUTO_TEST_SUITE_END() // stream_enum
