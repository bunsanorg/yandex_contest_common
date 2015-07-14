#include <yandex/contest/Tempfile.hpp>

#include <yandex/contest/StreamLog.hpp>

#include <bunsan/filesystem/fstream.hpp>

#include <boost/assert.hpp>
#include <boost/filesystem/operations.hpp>

namespace yandex {
namespace contest {

// TODO implement atomic file creation: note: use fopen(.."x"..)
Tempfile::Tempfile(const std::string &data)
    : path_(boost::filesystem::unique_path(
          boost::filesystem::temp_directory_path() / "%%%%-%%%%-%%%%-%%%%")) {
  STREAM_DEBUG << "Creating temporary file at " << path_.get() << ".";
  bunsan::filesystem::ofstream fout(path_.get());
  BUNSAN_FILESYSTEM_FSTREAM_WRAP_BEGIN(fout) {
    fout << data;
  } BUNSAN_FILESYSTEM_FSTREAM_WRAP_END(fout)
  fout.close();
}

Tempfile::Tempfile(Tempfile &&tmp) noexcept { swap(tmp); }

Tempfile &Tempfile::operator=(Tempfile &&tmp) noexcept {
  swap(tmp);
  // FIXME Should we use noexcept version here?
  // Or should we mark remove() with noexcept?
  tmp.remove();
  return *this;
}

void Tempfile::swap(Tempfile &tmp) noexcept {
  using boost::swap;
  swap(path_, tmp.path_);
}

void Tempfile::remove() {
  if (path_) {
    STREAM_DEBUG << "Trying to remove temporary file at " << path_.get() << ".";
    boost::system::error_code ec;
    boost::filesystem::remove(path_.get(), ec);
    if (ec)
      STREAM_ERROR << "Unable to remove temporary file at " << path_.get()
                   << " due to \"" << ec << "\" (ignoring).";
    path_.reset();
  }
}

const boost::filesystem::path &Tempfile::path() const {
  BOOST_ASSERT(path_);
  return path_.get();
}

Tempfile::~Tempfile() { remove(); }

}  // namespace contest
}  // namespace yandex
