#pragma once

#include <boost/noncopyable.hpp>

#include <atomic>

#include <cstddef>

namespace yandex {
namespace contest {

class IntrusivePointeeBase : private boost::noncopyable {
 public:
  IntrusivePointeeBase() : refCount_(0) {}
  virtual ~IntrusivePointeeBase() {}

 private:
  friend void intrusive_ptr_add_ref(IntrusivePointeeBase *) noexcept;
  friend void intrusive_ptr_release(IntrusivePointeeBase *) noexcept;
  std::atomic<std::size_t> refCount_;
};

}  // namespace contest
}  // namespace yandex
