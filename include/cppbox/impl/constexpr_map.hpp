#ifndef CPPBOX_IMPL_CONSTEXPR_MAP_HPP
#define CPPBOX_IMPL_CONSTEXPR_MAP_HPP

#include <algorithm>

#include "cppbox/constexpr_map.hpp"

namespace cppbox {

template<class Key, class T, std::size_t N, class Hash>
constexpr ConstexprMap<Key, T, N, Hash>::ConstexprMap(const std::array<Entry, N> inputs, Hash hash_function)
    : hash_function_(hash_function) {
    // Copy inputs into internal data, hashing the key
    std::transform(inputs.cbegin(), inputs.cend(), data_.begin(),
            [hash_function](const Entry& input) -> HashEntry { return {hash_function(input.key), input}; });
    // Sort internal data by key hash
    std::sort(data_.begin(), data_.end(),
            [](const HashEntry& lhs, const HashEntry& rhs) -> bool { return lhs.hash < rhs.hash; });
}

template<class Key, class T, std::size_t N, class Hash>
constexpr std::optional<T> ConstexprMap<Key, T, N, Hash>::find(const Key& key) const {
    // Hash the query key
    const HashType query_hash = hash_function_(key);
    // Search for the corresponding hash with logarithmic complexity
    const auto it = std::lower_bound(data_.cbegin(), data_.cend(), query_hash,
            [](const HashEntry& entry, const HashType& hash) { return entry.hash < hash; });
    // If the hash is found and the key matches (catching hash collisions) then return the value
    return it != data_.cend() && it->hash == query_hash && it->entry.key == key ? std::optional<T>(it->entry.value)
                                                                                : std::nullopt;
}

template<class Key, class T, std::size_t N, class Hash>
constexpr T ConstexprMap<Key, T, N, Hash>::get_or(const Key& key, const T default_value) const {
    return find(key).value_or(default_value);
}

}

#endif
