#pragma once

#include "yandex/contest/Error.hpp"

namespace yandex{namespace contest{namespace config
{
    struct Error: virtual contest::Error {};

    struct InputArchiveError: virtual Error {};

    struct OutputArchiveError: virtual Error {};

    struct VariantLoadError: virtual InputArchiveError {};

    struct VariantLoadKeyError: virtual VariantLoadError
    {
        typedef boost::error_info<struct keyTag, std::string> key;
    };

    struct VariantLoadInvalidKeyError: virtual VariantLoadKeyError {};

    struct VariantLoadNoKeyError: virtual VariantLoadKeyError {};

    struct VariantLoadMultipleKeysError: virtual VariantLoadKeyError {};
}}}
