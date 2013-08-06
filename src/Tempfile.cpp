#include <yandex/contest/Tempfile.hpp>
#include <yandex/contest/detail/LogHelper.hpp>

#include <bunsan/enable_error_info.hpp>
#include <bunsan/filesystem/fstream.hpp>

#include <boost/filesystem/operations.hpp>
#include <boost/assert.hpp>

namespace yandex{namespace contest
{
    Tempfile::Tempfile(const std::string &data):
        // TODO implement atomic file creation: note: use fopen(.."x"..)
        path_(boost::filesystem::unique_path(boost::filesystem::temp_directory_path() / "%%%%-%%%%-%%%%-%%%%"))
    {
        STREAM_DEBUG << "Creating temporary file at " << path_.get() << ".";
        BUNSAN_EXCEPTIONS_WRAP_BEGIN()
        {
            bunsan::filesystem::ofstream fout(path_.get());
            fout << data;
            fout.close();
        }
        BUNSAN_EXCEPTIONS_WRAP_END()
    }

    Tempfile::Tempfile(Tempfile &&tmp) noexcept
    {
        swap(tmp);
    }

    Tempfile &Tempfile::operator=(Tempfile &&tmp) noexcept
    {
        swap(tmp);
        tmp.remove(); // FIXME Should we use noexcept version here? Or should we mark remove() with noexcept?
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
