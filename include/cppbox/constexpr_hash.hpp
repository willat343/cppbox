#ifndef CPPBOX_CONSTEXPR_HASH_HPP
#define CPPBOX_CONSTEXPR_HASH_HPP

#include <concepts>
#include <cstdint>
#include <string_view>
#include <type_traits>

#include "cppbox/enum.hpp"

namespace cppbox {

/**
 * @brief Compute the 32-bit FNV-1a hash of a string, a very simple and fast hashing function with low collision rate
 * for small datasets.
 *
 * @param string
 * @return constexpr std::uint32_t
 */
constexpr std::uint32_t fnv1a_32(const std::string_view string);

/**
 * @brief Compute the 64-bit FNV-1a hash of a string, a very simple and fast hashing function with low collision rate
 * for small datasets.
 *
 * @param string
 * @return constexpr std::uint64_t
 */
constexpr std::uint64_t fnv1a_64(const std::string_view string);

/**
 * @brief Primate template for constexpr hashes.
 *
 * @tparam Key
 */
template<class Key>
struct ConstexprHash;

/**
 * @brief Template specialisation for integral types.
 *
 * @tparam Key
 */
template<std::integral Key>
struct ConstexprHash<Key> {
    constexpr std::size_t operator()(const Key val) const noexcept;
};

/**
 * @brief Template specialisation for enum types.
 *
 * @tparam Key
 */
template<IsEnum Key>
struct ConstexprHash<Key> {
    constexpr std::size_t operator()(const Key val) const noexcept;
};

/**
 * @brief Template specialisation for `std::string_view` strings.
 *
 * @tparam
 */
template<>
struct ConstexprHash<std::string_view> {
    constexpr std::size_t operator()(const std::string_view string) const noexcept;
};

/**
 * @brief Template specialisation for `const char*` strings.
 *
 * @tparam
 */
template<>
struct ConstexprHash<const char*> {
    constexpr std::size_t operator()(const char* string) const noexcept;
};

}

#include "cppbox/impl/constexpr_hash.hpp"

#endif
