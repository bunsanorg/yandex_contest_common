#pragma once

#include <bunsan/runtime/demangle.hpp>

namespace yandex {
namespace contest {
namespace typeinfo {

template <typename T>
std::string demangle(T &&name) {
  return bunsan::runtime::demangle(std::forward<T>(name));
}

template <typename T>
std::string name(const T &obj) {
  return demangle(typeid(obj).name());
}

}  // namespace typeinfo
}  // namespace contest
}  // namespace yandex
