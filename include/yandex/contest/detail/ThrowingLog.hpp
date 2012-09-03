#pragma once

#include "yandex/contest/Log.hpp"

namespace yandex{namespace contest{namespace detail
{
    /*!
     * \brief Helper for children that
     * do not to wrap append call in try {} catch {}.
     */
    class ThrowingLog: public Log
    {
    public:
        /// Wraps append_() in try {} catch {}.
        virtual void append(const Level level, const std::string &position,
                            const std::string &message) noexcept override;

    protected:
        virtual void append_(const Level level, const std::string &position,
                             const std::string &message)=0;
    };
}}}
