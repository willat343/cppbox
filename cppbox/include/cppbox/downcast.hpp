#ifndef CPPBOX_DOWNCAST_HPP
#define CPPBOX_DOWNCAST_HPP

namespace cppbox {

template<typename DowncastT, typename T>
DowncastT* downcast_and_check(T* ptr);

template<typename DowncastT, typename T>
const DowncastT* downcast_and_check(const T* ptr);

}

#include "cppbox/impl/downcast.hpp"

#endif
