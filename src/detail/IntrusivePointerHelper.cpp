#include <yandex/contest/detail/IntrusivePointerHelper.hpp>

#include <yandex/contest/IntrusivePointeeBase.hpp>

namespace yandex {
namespace contest {
namespace intrusive_ptr_detail {

void add_ref(IntrusivePointeeBase *ptr) noexcept { intrusive_ptr_add_ref(ptr); }
void release(IntrusivePointeeBase *ptr) noexcept { intrusive_ptr_release(ptr); }

}  // namespace intrusive_ptr_detail
}  // namespace contest
}  // namespace yandex
