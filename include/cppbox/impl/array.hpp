#ifndef CPPBOX_IMPL_ARRAY_HPP
#define CPPBOX_IMPL_ARRAY_HPP

#include "cppbox/array.hpp"

namespace cppbox {

template<class T, std::size_t N>
constexpr bool contains(const std::array<T, N>& array, const T& element) {
    return std::find(array.cbegin(), array.cend(), element) != array.cend();
}

template<class T, std::size_t... Sizes>
constexpr std::array<T, (Sizes + ...)> merge(const std::array<T, Sizes>&... array) {
    std::array<T, (Sizes + ...)> merged{};
    std::size_t index{0};
    (
            [&merged, &index](const auto& array) {
                for (const auto& item : array) {
                    merged[index++] = item;
                }
            }(array),
            ...);
    return merged;
}

}

#endif
