#ifndef CPPBOX_UNORDERED_MAP_HPP
#define CPPBOX_UNORDERED_MAP_HPP

#include <unordered_map>
#include <unordered_set>

namespace cppbox {

template<class Key, class T, class Hash, class KeyEqual, class Allocator>
std::unordered_set<Key, Hash, KeyEqual> keys(const std::unordered_map<Key, T, Hash, KeyEqual, Allocator>& map);

}

#include "cppbox/impl/unordered_map.hpp"

#endif
