#ifndef CPPBOX_RANGES_HPP
#define CPPBOX_RANGES_HPP

#include <concepts>
#include <ranges>

namespace cppbox {

template<typename Range, typename Element>
concept ForwardRangeOf = std::ranges::forward_range<Range> && std::same_as<std::ranges::range_value_t<Range>, Element>;

/**
 * @brief Check if each element of a range is less than the one before it. For the non-strict check, that no element is
 * greater than the one before it, use `std::ranges::is_sorted(range, std::ranges::greater{})`.
 *
 * @code{.cpp}
 * cppbox::is_strictly_decreasing(std::vector<int>{3, 2, 1}); // true
 * cppbox::is_strictly_decreasing(std::vector<int>{3, 2, 2}); // false
 * @endcode
 *
 * @tparam Range forward range of totally ordered elements
 * @param range
 * @return true if each element is less than the one before it, including for an empty or single-element range
 * @return false otherwise
 */
template<std::ranges::forward_range Range>
    requires(std::totally_ordered<std::ranges::range_value_t<Range>>)
constexpr bool is_strictly_decreasing(const Range& range);

/**
 * @brief Check if each element of a range is greater than the one before it. For the non-strict check, that no element
 * is less than the one before it, use `std::ranges::is_sorted(range)`.
 *
 * @code{.cpp}
 * cppbox::is_strictly_increasing(std::vector<int>{1, 2, 3}); // true
 * cppbox::is_strictly_increasing(std::vector<int>{1, 2, 2}); // false
 * @endcode
 *
 * @tparam Range forward range of totally ordered elements
 * @param range
 * @return true if each element is greater than the one before it, including for an empty or single-element range
 * @return false otherwise
 */
template<std::ranges::forward_range Range>
    requires(std::totally_ordered<std::ranges::range_value_t<Range>>)
constexpr bool is_strictly_increasing(const Range& range);

}

#include "cppbox/impl/ranges.hpp"

#endif
