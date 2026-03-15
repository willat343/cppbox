#ifndef CPPBOX_IMPL_MAP_HPP
#define CPPBOX_IMPL_MAP_HPP

#include <ranges>
#include <sstream>

#include "cppbox/map.hpp"

namespace cppbox {

template<class Key, class T, class Compare, class Allocator>
std::set<Key, Compare> keys(const std::map<Key, T, Compare, Allocator>& map) {
    const auto key_view = map | std::views::keys;
    return {key_view.begin(), key_view.end()};
}

template<class Key, class T, class Compare, class Allocator>
inline std::string to_string(const std::map<Key, T, Compare, Allocator>& map) {
    std::stringstream ss;
    for (const auto& [k, v] : map) {
        ss << k << ": " << v << "\n";
    }
    return ss.str();
}

}

#endif
