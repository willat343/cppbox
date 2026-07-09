#ifndef CPPBOX_CONSTEXPR_MAP_HPP
#define CPPBOX_CONSTEXPR_MAP_HPP

#include <array>
#include <cstddef>
#include <optional>

#include "cppbox/constexpr_hash.hpp"

namespace cppbox {

template<class Key, class T>
struct ConstexprMapEntry {
    Key key;
    T value;
};

template<class Key, class T, std::size_t N, class Hash = ConstexprHash<Key>>
class ConstexprMap {
public:
    using Entry = ConstexprMapEntry<Key, T>;

    /**
     * @brief Create a compile-time map.
     *
     * For example:
     * ```
     * constexpr auto sizes = ConstexprMap(std::to_array<ConstexprMapEntry<std::string_view, std::size_t>>({
     *      {"bool", sizeof(bool)},
     *      {"int32", sizeof(int32_t)},
     *      {"float64", sizeof(double)}
     * }));
     * ```
     *
     * @param inputs
     * @param hash_function
     */
    constexpr ConstexprMap(const std::array<Entry, N> inputs, Hash hash_function = Hash{});

    /**
     * @brief Find the value corresponding to the key.
     *
     * Search is logarithmic in the number of stored entries.
     *
     * @param key
     * @return constexpr std::optional<T>
     */
    constexpr std::optional<T> find(const Key& key) const;

    /**
     * @brief Get the value corresponding to the key or return `default_value` if the key does not exist.
     *
     * Search is logarithmic in the number of stored entries.
     *
     * @param key
     * @param default_value
     * @return constexpr T
     */
    constexpr T get_or(const Key& key, const T default_value) const;

private:
    /**
     * @brief Output type of the hash function.
     *
     */
    using HashType = decltype(std::declval<Hash>()(std::declval<Key>()));

    /**
     * @brief Stored entry type with key hash.
     *
     */
    struct HashEntry {
        HashType hash;
        Entry entry;
    };

    /**
     * @brief Store the input data with key hashes.
     *
     */
    std::array<HashEntry, N> data_;

    /**
     * @brief Hash function which is tagged with `[[no_unique_address]]` to allow it to be optimised to 0 bytes
     * when stateless and prevent unnecessary memory padding (also works when stateful).
     *
     * Developer Note: [[no_unique_address]] seems to cause internal compiler error issues with the g++10 compiler in
     * some cases, so can be re-enabled when a higher compiler is enforced. This tag is a relatively minor optimization.
     */
    /*[[no_unique_address]]*/ Hash hash_function_;
};

}

#include "cppbox/impl/constexpr_map.hpp"

#endif
