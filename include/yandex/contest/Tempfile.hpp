#pragma once

#include <boost/filesystem/path.hpp>
#include <boost/optional.hpp>

#include <string>

namespace yandex{namespace contest
{
    class Tempfile
    {
    public:
        /// Create temporary file filled by data.
        explicit Tempfile(const std::string &data=std::string());

        Tempfile(const Tempfile &)=delete;
        Tempfile(Tempfile &&) noexcept;
        Tempfile &operator=(const Tempfile &)=delete;
        Tempfile &operator=(Tempfile &&) noexcept;
        ~Tempfile();

        void remove();
        const boost::filesystem::path &path() const;

        void swap(Tempfile &) noexcept;

    private:
        boost::optional<boost::filesystem::path> path_;
    };

    inline void swap(Tempfile &a, Tempfile &b) noexcept
    {
        a.swap(b);
    }
}}
