#include <yandex/contest/Log.hpp>

#include <bunsan/log/core.hpp>
#include <bunsan/log/expressions/scope.hpp>
#include <bunsan/log/trivial.hpp>

#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/format.hpp>
#include <boost/log/sinks/basic_sink_backend.hpp>
#include <boost/log/sinks/sync_frontend.hpp>

#include <mutex>

namespace yandex{namespace contest
{
    static bunsan::log::severity toSeverity(const Log::Level level)
    {
        using bunsan::log::severity;

        switch (level)
        {
        case Log::Level::TRACE:
            return severity::trace;
        case Log::Level::DEBUG:
            return severity::debug;
        case Log::Level::INFO:
            return severity::info;
        case Log::Level::WARNING:
            return severity::warning;
        case Log::Level::ERROR:
            return severity::error;
        case Log::Level::FATAL:
            return severity::fatal;
        }
        return severity::info;
    }

    static Log::Level toLevel(const bunsan::log::severity sev)
    {
        using bunsan::log::severity;

        switch (sev)
        {
        case severity::trace:
            return Log::Level::TRACE;
        case severity::debug:
            return Log::Level::DEBUG;
        case severity::info:
            return Log::Level::INFO;
        case severity::warning:
            return Log::Level::WARNING;
        case severity::error:
            return Log::Level::ERROR;
        case severity::fatal:
            return Log::Level::FATAL;
        }
        return Log::Level::INFO;
    }

    namespace
    {
        using frontend_requirements = boost::log::sinks::combine_requirements<
            boost::log::sinks::synchronized_feeding
        >::type;

        template <typename T>
        struct Visitor
        {
            using result_type = T;

            const T &operator()(const T &obj) const { return obj; }
        };

        BOOST_LOG_ATTRIBUTE_KEYWORD(Timestamp, "Timestamp", boost::posix_time::ptime)

        class SinkBackend: public boost::log::sinks::basic_sink_backend<frontend_requirements>
        {
        public:
            explicit SinkBackend(const Log::Function &function): function_(function) {}

            void consume(const boost::log::record_view &rec)
            {
                namespace expr = bunsan::log::expressions;

                function_(
                    rec[Timestamp].apply_visitor_or_default(
                        Visitor<boost::posix_time::ptime>(),
                        now()
                    ),
                    toLevel(
                        rec[expr::severity].apply_visitor_or_default(
                            Visitor<bunsan::log::severity>(),
                            bunsan::log::severity::info
                        )
                    ),
                    str(boost::format("%1%(%2%):%3%") %
                        rec[expr::file].apply_visitor_or_default(
                            Visitor<std::string>(),
                            "???"
                        ) %
                        rec[expr::function].apply_visitor_or_default(
                            Visitor<std::string>(),
                            "???"
                        ) %
                        rec[expr::line].apply_visitor_or_default(
                            Visitor<unsigned>(),
                            0
                        )
                    ),
                    rec[boost::log::expressions::smessage].apply_visitor_or_default(
                        Visitor<std::string>(), ""
                    )
                );
            }

        private:
            static boost::posix_time::ptime now()
            {
#ifdef BOOST_DATE_TIME_HAS_HIGH_PRECISION_CLOCK
                using clock = boost::posix_time::microsec_clock;
#else
                using clock = boost::posix_time::second_clock;
#endif
                return clock::local_time();
            }

        private:
            Log::Function function_;
        };

        using Sink = boost::log::sinks::synchronous_sink<SinkBackend>;
    }

    void Log::setFunction(const Function &function)
    {
        bunsan::log::remove_default_sink();
        static std::mutex lock;
        static boost::shared_ptr<boost::log::sinks::sink> sink;
        std::lock_guard<std::mutex> lk(lock);

        const auto core = boost::log::core::get();
        if (sink)
        {
            core->remove_sink(sink);
            sink.reset();
        }
        sink = boost::make_shared<Sink>(function);
        boost::log::core::get()->add_sink(sink);
    }

    void Log::setMinimumLevel(const Level level)
    {
        bunsan::log::set_minimum_severity(toSeverity(level));
    }

    void Log::enableLogging()
    {
        bunsan::log::enable();
    }

    void Log::disableLogging()
    {
        bunsan::log::disable();
    }
}}
