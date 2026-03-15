#ifndef CPPBOX_UNORDERED_SET_HPP
#define CPPBOX_UNORDERED_SET_HPP

#include <unordered_set>

namespace cppbox {

template<class Key, class Hash, class KeyEqual, class Allocator>
std::unordered_set<Key, Hash, KeyEqual, Allocator> merge(const std::unordered_set<Key, Hash, KeyEqual, Allocator>& set1,
        const std::unordered_set<Key, Hash, KeyEqual, Allocator>& set2);

}

#include "cppbox/impl/unordered_set.hpp"

#endif
