#pragma once

#include <string>
#include <type_traits>

namespace yandex{namespace contest{namespace config{namespace traits
{
    /*!
     * \brief We assume that enum is declared using detail::StreamEnum.
     *
     * \todo Probably that should be checked (but for what?).
     */
    template <typename T>
    struct directAssign:
        std::integral_constant<bool,
            std::is_arithmetic<T>::value || std::is_enum<T>::value> {};

    template <>
    struct directAssign<std::string>: std::integral_constant<bool, true> {};

    template <typename Parent, typename Derived>
    struct typeKey
    {
        static constexpr const char *value = nullptr;
    };
}}}}

#define YANDEX_CONFIG_EXPORT(PARENT, DERIVED, FIELD) \
    namespace yandex{namespace config{namespace traits \
    { \
        template <> \
        struct typeKey<PARENT, DERIVED> \
        { \
            static constexpr const char *value = FIELD; \
        }; \
    }}}
