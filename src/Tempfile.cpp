#include "yandex/contest/Tempfile.hpp"
#include "yandex/contest/detail/LogHelper.hpp"

#include "yandex/contest/SystemError.hpp"

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/assert.hpp>

namespace yandex{namespace contest
{
    Tempfile::Tempfile(const std::string &data):
        // TODO implement atomic file creation
        path_(boost::filesystem::unique_path(boost::filesystem::temp_directory_path() / "%%%%-%%%%-%%%%-%%%%"))
    {
        STREAM_DEBUG << "Creating temporary file at " << path_.get() << ".";
        {
            boost::filesystem::ofstream fout(path_.get());
            if (!fout)
            {
                STREAM_ERROR << "Unable to create temporary file at " << path_.get() << "; exception is thrown.";
                BOOST_THROW_EXCEPTION(SystemError("open"));
            }
            fout << data;
            fout.close();
            if (!fout)
            {
                STREAM_ERROR << "Unable to close temporary file at " << path_.get() << "; exception is throw.";
                BOOST_THROW_EXCEPTION(SystemError("close"));
            }
        }
    }

    Tempfile::Tempfile(Tempfile &&tmp)
    {
        this->swap(tmp);
    }

    Tempfile &Tempfile::operator=(Tempfile &&tmp)
    {
        this->swap(tmp);
        tmp.remove();
        return *this;
    }

    void Tempfile::swap(Tempfile &tmp) noexcept
    {
        using boost::swap;
        swap(path_, tmp.path_);
    }

    void Tempfile::remove()
    {
        if (path_)
        {
            STREAM_DEBUG << "Trying to remove temporary file at " << path_.get() << ".";
            boost::system::error_code ec;
            boost::filesystem::remove(path_.get(), ec);
            if (ec)
                STREAM_ERROR << "Unable to remove temporary file at " << path_.get() << " due to \"" << ec << "\" (ignoring).";
            path_.reset();
        }
    }

    const boost::filesystem::path &Tempfile::path() const
    {
        BOOST_ASSERT(path_);
        return path_.get();
    }

    Tempfile::~Tempfile()
    {
        remove();
    }
}}
