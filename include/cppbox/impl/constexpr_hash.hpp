#ifndef CPPBOX_IMPL_CONSTEXPR_HASH_HPP
#define CPPBOX_IMPL_CONSTEXPR_HASH_HPP

#include "cppbox/constexpr_hash.hpp"

namespace cppbox {

constexpr inline std::uint32_t fnv1a_32(const std::string_view string) {
    std::uint32_t hash = 2166136261u;
    for (const char c : string) {
        hash ^= static_cast<uint32_t>(c);
        hash *= 16777619u;
    }
    return hash;
}

constexpr inline std::uint64_t fnv1a_64(const std::string_view string) {
    std::uint64_t hash = 14695981039346656037ULL;
    for (const char c : string) {
        hash ^= static_cast<std::uint64_t>(c);
        hash *= 1099511628211ULL;
    }
    return hash;
}

template<std::integral Key>
constexpr std::size_t ConstexprHash<Key>::operator()(const Key val) const noexcept {
    // Safely cast to unsigned version of same size, avoiding "sign extension"
    return static_cast<std::size_t>(static_cast<std::make_unsigned_t<Key>>(val));
}

template<IsEnum Key>
constexpr std::size_t ConstexprHash<Key>::operator()(const Key val) const noexcept {
    // Hash as the underlying integral type
    return ConstexprHash<std::underlying_type_t<Key>>{}(static_cast<std::underlying_type_t<Key>>(val));
}

constexpr std::size_t ConstexprHash<std::string_view>::operator()(const std::string_view string) const noexcept {
    static_assert(sizeof(std::size_t) == 8 || sizeof(std::size_t) == 4, "sizeof(std::size_t) must be 8 or 4");
    if constexpr (sizeof(std::size_t) == 8) {
        return static_cast<std::size_t>(fnv1a_64(string));
    } else {  // sizeof(std::size_t) == 4
        return static_cast<std::size_t>(fnv1a_32(string));
    }
}

constexpr std::size_t ConstexprHash<const char*>::operator()(const char* string) const noexcept {
    // Hash as a string
    return ConstexprHash<std::string_view>{}(std::string_view(string));
}

}

#endif
