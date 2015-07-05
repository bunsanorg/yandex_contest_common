#define BOOST_TEST_MODULE Tempfile
#include <boost/test/unit_test.hpp>

#include <yandex/contest/Tempfile.hpp>

#include <bunsan/test/filesystem/read_data.hpp>

#include <boost/filesystem/operations.hpp>

using namespace bunsan::test;

namespace ya = yandex::contest;
namespace fs = boost::filesystem;

BOOST_AUTO_TEST_CASE(autoRemove)
{
    fs::path path;
    {
        ya::Tempfile tmp;
        path = tmp.path();
        BOOST_CHECK(filesystem::read_data(tmp.path()).empty());
    }
    BOOST_CHECK(!fs::exists(path));
}

BOOST_AUTO_TEST_CASE(data)
{
    const std::string text = "some arbitrary text";
    fs::path path;
    {
        ya::Tempfile tmp(text);
        path = tmp.path();
        BOOST_CHECK_EQUAL(filesystem::read_data(tmp.path()), text);
    }
    BOOST_CHECK(!fs::exists(path));
}

namespace
{
    ya::Tempfile createTempfile(fs::path &path)
    {
        ya::Tempfile tmp;
        path = tmp.path();
        return tmp;
    }
}

BOOST_AUTO_TEST_CASE(move)
{
    fs::path aPath, bPath;
    {
        ya::Tempfile a;
        aPath = a.path();
        BOOST_CHECK(fs::exists(a.path()));
        a = createTempfile(bPath);
        BOOST_CHECK_EQUAL(a.path(), bPath);
        BOOST_CHECK(fs::exists(a.path()));
        BOOST_CHECK(!fs::exists(aPath));
    }
    BOOST_CHECK(!fs::exists(aPath));
    BOOST_CHECK(!fs::exists(bPath));
}
