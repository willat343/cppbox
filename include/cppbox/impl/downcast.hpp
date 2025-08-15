#ifndef CPPBOX_IMPL_DOWNCAST_HPP
#define CPPBOX_IMPL_DOWNCAST_HPP

#include <stdexcept>

#include "cppbox/downcast.hpp"
#include "cppbox/exceptions.hpp"

namespace cppbox {

template<typename DowncastT, typename T>
DowncastT* downcast_and_check(T* ptr) {
    DowncastT* downcast_ptr = dynamic_cast<DowncastT*>(ptr);
    throw_if(!downcast_ptr, "failed to downcast");
    return downcast_ptr;
}

template<typename DowncastT, typename T>
const DowncastT* downcast_and_check(const T* ptr) {
    const DowncastT* downcast_ptr = dynamic_cast<const DowncastT*>(ptr);
    throw_if(!downcast_ptr, "failed to downcast");
    return downcast_ptr;
}

}

#endif
