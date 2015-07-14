#pragma once

#include <yandex/contest/Error.hpp>

#include <bunsan/system_error.hpp>

namespace yandex {
namespace contest {

struct SystemError : bunsan::system_error, virtual Error {
  using bunsan::system_error::system_error;

  using errorCode = error_code;
  using whatMessage = what_message;
};

}  // namespace contest
}  // namespace yandex
