#pragma once

#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/fstream.hpp>

struct TempDir: private boost::noncopyable
{
    TempDir():
        path(boost::filesystem::temp_directory_path() / boost::filesystem::unique_path())
    {
        BOOST_REQUIRE(boost::filesystem::create_directory(path));
        BOOST_TEST_MESSAGE("Temporary directory " << path << " was created.");
    }

    ~TempDir()
    {
        boost::system::error_code ec;
        boost::filesystem::remove_all(path, ec);
        BOOST_CHECK(!ec);
        if (ec)
            BOOST_TEST_MESSAGE("Error while removing temporary directory " << path <<
                               ": " << ec.message() << ".");
    }

    boost::filesystem::path path;
};

std::string readData(const boost::filesystem::path &path)
{
    BOOST_TEST_CHECKPOINT(BOOST_CURRENT_FUNCTION);
    BOOST_TEST_MESSAGE("Attempt to read " << path << ".");
    BOOST_REQUIRE(boost::filesystem::exists(path));
    boost::filesystem::ifstream fin(path);
    BOOST_REQUIRE(fin);
    const std::string rdata{
        std::istreambuf_iterator<char>(fin),
        std::istreambuf_iterator<char>()
    };
    fin.close();
    BOOST_REQUIRE(fin);
    return rdata;
}

void writeData(const boost::filesystem::path &path, const std::string &data)
{
    BOOST_TEST_CHECKPOINT(BOOST_CURRENT_FUNCTION);
    BOOST_TEST_MESSAGE("Attempt to write to " << path << ".");
    boost::filesystem::ofstream fout(path);
    BOOST_REQUIRE(fout);
    fout << data << std::flush;
    BOOST_REQUIRE(fout);
    fout.close();
    BOOST_REQUIRE(fout);
}

