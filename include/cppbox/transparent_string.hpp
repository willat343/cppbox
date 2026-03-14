#ifndef CPPBOX_TRANSPARENT_STRING_HPP
#define CPPBOX_TRANSPARENT_STRING_HPP

#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>

namespace cppbox {

struct TransparentStringHash {
    using is_transparent = void;

    size_t operator()(std::string_view s) const noexcept {
        return std::hash<std::string_view>{}(s);
    }
};

struct TransparentStringEq {
    using is_transparent = void;

    bool operator()(std::string_view a, std::string_view b) const noexcept {
        return a == b;
    }
};

/**
 * @brief `TransparentStringUnorderedMap<T>` is like `std::unordered_map<std::string, T>` but allows for the lookup of
 * types like `std::string_view` and `const char*` with zero allocations or temporaries being created.
 *
 * Note: heterogenous key lookup for const containers is only supported from C++23 onwards
 *
 * @tparam T
 */
template<typename T>
using TransparentStringUnorderedMap = std::unordered_map<std::string, T, TransparentStringHash, TransparentStringEq>;

/**
 * @brief `TransparentStringUnorderedSet` is like `std::unordered_set<std::string>` but allows for the lookup of types
 * like `std::string_view` and `const char*` with zero allocations or temporaries being created.
 *
 * Note: heterogenous key lookup for const containers is only supported from C++23 onwards
 *
 */
using TransparentStringUnorderedSet = std::unordered_set<std::string, TransparentStringHash, TransparentStringEq>;

}

#endif
