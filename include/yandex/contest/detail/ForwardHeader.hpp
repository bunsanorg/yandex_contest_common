// no pragma once needed

/*!
 * \brief Forward declarations.
 *
 * For each class forward-declared here,
 * this header file should be included before full class declaration.
 *
 * For each class declared here {Class}Pointer
 * smart pointer typedef is declared.
 *
 * boost::intrusive_ptr smart pointer class is used.
 * For each class intrusive_ptr_add_ref() and intrusive_ptr_add_ref()
 * functions are declared.
 *
 * \note User should include "yandex/contest/detail/ForwardFooter.hpp"
 * in the end of forward file.
 */

#include <boost/intrusive_ptr.hpp>

#define YANDEX_CONTEST_INTRUSIVE_PTR_FWD_DECLARE(CLASS) \
  class CLASS;                                          \
  using CLASS##Pointer = boost::intrusive_ptr<CLASS>;   \
  void intrusive_ptr_add_ref(CLASS *) noexcept;         \
  void intrusive_ptr_release(CLASS *) noexcept
