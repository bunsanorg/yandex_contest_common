#pragma once

/*!
 * \file
 *
 * This header is intended to be used with forward-declared intrusive pointers.
 *
 * To avoid copy-paste of boost::intrusive_ptr
 * related functions implementation
 * these defines are introduced.
 *
 * \warning Do not include it in header files.
 */

#define YANDEX_CONTEST_INTRUSIVE_PTR_ADD_REF(P) \
  ::yandex::contest::intrusive_ptr_detail::add_ref(P)
#define YANDEX_CONTEST_INTRUSIVE_PTR_RELEASE(P) \
  ::yandex::contest::intrusive_ptr_detail::release(P)

#define YANDEX_CONTEST_INTRUSIVE_PTR_DEFINE(CLASS) \
  void intrusive_ptr_add_ref(CLASS *p) noexcept {  \
    YANDEX_CONTEST_INTRUSIVE_PTR_ADD_REF(p);       \
  }                                                \
  void intrusive_ptr_release(CLASS *p) noexcept {  \
    YANDEX_CONTEST_INTRUSIVE_PTR_RELEASE(p);       \
  }

namespace yandex {
namespace contest {

class IntrusivePointeeBase;

namespace intrusive_ptr_detail {
void add_ref(IntrusivePointeeBase *) noexcept;
void release(IntrusivePointeeBase *) noexcept;
}  // namespace intrusive_ptr_detail

}  // namespace contest
}  // namespace yandex
