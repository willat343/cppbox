#ifndef CPPBOX_ARRAY_HPP
#define CPPBOX_ARRAY_HPP

#include <array>

namespace cppbox {

template<class T, std::size_t N>
constexpr bool contains(const std::array<T, N>& array);

}

#include "cppbox/impl/array.hpp"

#endif
