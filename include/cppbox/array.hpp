#ifndef CPPBOX_ARRAY_HPP
#define CPPBOX_ARRAY_HPP

#include <array>

namespace cppbox {

template<class T, std::size_t N>
constexpr bool contains(const std::array<T, N>& array);

template<class T, std::size_t... Sizes>
constexpr std::array<T, (Sizes + ...)> merge(const std::array<T, Sizes>&... array);

}

#include "cppbox/impl/array.hpp"

#endif
