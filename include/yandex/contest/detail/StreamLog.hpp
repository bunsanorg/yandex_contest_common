#pragma once

#include <yandex/contest/detail/ThrowingLog.hpp>

namespace yandex{namespace contest{namespace detail
{
    /*!
     * \brief Log implementation with std::ostream sink.
     */
    class StreamLog: public ThrowingLog
    {
    public:
        static LogPointer create(std::ostream &out);

    protected:
        virtual void append_(const Level level, const std::string &position,
                             const std::string &message) override;

    private:
        explicit StreamLog(std::ostream &out);

    private:
        std::ostream &out_;
    };
}}}
