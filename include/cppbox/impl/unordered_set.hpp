#ifndef CPPBOX_IMPL_UNORDERED_SET_HPP
#define CPPBOX_IMPL_UNORDERED_SET_HPP

#include "cppbox/unordered_set.hpp"

namespace cppbox {

template<class Key, class Hash, class KeyEqual, class Allocator>
std::unordered_set<Key, Hash, KeyEqual, Allocator> merge(const std::unordered_set<Key, Hash, KeyEqual, Allocator>& set1,
        const std::unordered_set<Key, Hash, KeyEqual, Allocator>& set2) {
    std::unordered_set<Key, Hash, KeyEqual, Allocator> result = set1;
    result.insert(set2.cbegin(), set2.cend());
    return result;
}

}

#endif
