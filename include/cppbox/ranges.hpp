#ifndef CPPBOX_RANGES_HPP
#define CPPBOX_RANGES_HPP

#include <concepts>
#include <ranges>

namespace cppbox {

template<typename Range, typename Element>
concept FowardRangeOf = std::ranges::forward_range<Range> && std::same_as<std::ranges::range_value_t<Range>, Element>;

}

#endif
