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

template<class Key, class Hash, class KeyEqual, class Allocator, ForwardRangeOf<Key> Keys>
std::size_t erase_in_place(std::unordered_set<Key, Hash, KeyEqual, Allocator>& set, const Keys& keys) {
    std::size_t num_erased{0};
    for (const Key& key : keys) {
        num_erased += set.erase(key);
    }
    return num_erased;
}

}

#endif
