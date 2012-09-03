#pragma once

/*!
 * \file
 *
 * To avoid copy-paste of boost::intrusive_ptr
 * related functions implementation
 * these defines are introduced.
 *
 * \warning This pointer implementation is not thread-safe.
 *
 * \warning Do not include it in header files.
 */

#define YANDEX_CONTEST_INTRUSIVE_PTR_ADD_REF(P) ++(P->refCount_)
#define YANDEX_CONTEST_INTRUSIVE_PTR_RELEASE(P) if ((--(P->refCount_)) == 0) delete P

#define YANDEX_CONTEST_INTRUSIVE_PTR_DEFINE(CLASS) \
    void intrusive_ptr_add_ref(CLASS *p) noexcept \
    { \
        YANDEX_CONTEST_INTRUSIVE_PTR_ADD_REF(p); \
    } \
    void intrusive_ptr_release(CLASS *p) noexcept \
    { \
        YANDEX_CONTEST_INTRUSIVE_PTR_RELEASE(p); \
    }
