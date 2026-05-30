#ifndef CPPBOX_IMPL_ARRAY_HPP
#define CPPBOX_IMPL_ARRAY_HPP

#include "cppbox/array.hpp"

namespace cppbox {

template<class T, std::size_t N>
constexpr bool contains(const std::array<T, N>& array, const T& element) {
    return std::find(array.cbegin(), array.cend(), element) != array.cend();
}

}

#endif
