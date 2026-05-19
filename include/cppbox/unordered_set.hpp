#ifndef CPPBOX_UNORDERED_SET_HPP
#define CPPBOX_UNORDERED_SET_HPP

#include <unordered_set>

#include "cppbox/ranges.hpp"

namespace cppbox {

template<class Key, class Hash, class KeyEqual, class Allocator>
std::unordered_set<Key, Hash, KeyEqual, Allocator> merge(const std::unordered_set<Key, Hash, KeyEqual, Allocator>& set1,
        const std::unordered_set<Key, Hash, KeyEqual, Allocator>& set2);

template<class Key, class Hash, class KeyEqual, class Allocator, ForwardRangeOf<Key> Keys>
std::size_t erase_in_place(std::unordered_set<Key, Hash, KeyEqual, Allocator>& set, const Keys& keys);

}

#include "cppbox/impl/unordered_set.hpp"

#endif
