#include <yandex/contest/IntrusivePointeeBase.hpp>

namespace yandex{namespace contest
{
    void intrusive_ptr_add_ref(IntrusivePointeeBase *ptr) noexcept
    {
        ++(ptr->refCount_);
    }

    void intrusive_ptr_release(IntrusivePointeeBase *ptr) noexcept
    {
        if ((--(ptr->refCount_)) == 0)
            delete ptr;
    }
}}
