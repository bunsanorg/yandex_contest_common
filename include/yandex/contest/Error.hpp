#pragma once

#include <exception>

#include <boost/exception/all.hpp>

namespace yandex{namespace contest
{
    /*!
     * \brief Base error class for Yandex.Contest.Invoker project.
     */
    struct Error: virtual std::exception, virtual boost::exception
    {
        Error()=default;

        /// \see message
        explicit Error(const std::string &message_);

        /// Human-readable exception representation.
        virtual const char *what() const throw();

        /*!
         * \tparam ErrorInfo boost::error_info instantiation
         * \return pointer to data associated with ErrorInfo
         */
        template <typename ErrorInfo>
        const typename ErrorInfo::value_type *get() const noexcept
        {
            return boost::get_error_info<ErrorInfo>(*this);
        }

        /*!
         * \copydoc get
         */
        template <typename ErrorInfo>
        typename ErrorInfo::value_type *get() noexcept
        {
            return boost::get_error_info<ErrorInfo>(*this);
        }

        // tags
        /// Human readable error message
        typedef boost::error_info<struct messageTag, std::string> message;
    };
}}
