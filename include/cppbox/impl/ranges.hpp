#ifndef CPPBOX_IMPL_RANGES_HPP
#define CPPBOX_IMPL_RANGES_HPP

#include <algorithm>
#include <functional>

#include "cppbox/ranges.hpp"

namespace cppbox {

template<std::ranges::forward_range Range>
    requires(std::totally_ordered<std::ranges::range_value_t<Range>>)
constexpr bool is_strictly_decreasing(const Range& range) {
    return std::ranges::adjacent_find(range, std::ranges::less_equal{}) == std::ranges::end(range);
}

template<std::ranges::forward_range Range>
    requires(std::totally_ordered<std::ranges::range_value_t<Range>>)
constexpr bool is_strictly_increasing(const Range& range) {
    return std::ranges::adjacent_find(range, std::ranges::greater_equal{}) == std::ranges::end(range);
}

}

#endif
