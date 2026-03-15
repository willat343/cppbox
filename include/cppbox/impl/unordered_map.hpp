#ifndef CPPBOX_IMPL_UNORDERED_MAP_HPP
#define CPPBOX_IMPL_UNORDERED_MAP_HPP

#include <ranges>

#include "cppbox/unordered_map.hpp"

namespace cppbox {

template<class Key, class T, class Hash, class KeyEqual, class Allocator>
std::unordered_set<Key, Hash, KeyEqual> keys(const std::unordered_map<Key, T, Hash, KeyEqual, Allocator>& map) {
    const auto key_view = map | std::views::keys;
    return {key_view.begin(), key_view.end()};
}

}

#endif
