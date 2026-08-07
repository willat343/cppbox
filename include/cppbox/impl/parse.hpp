#ifndef CPPBOX_IMPL_PARSE_HPP
#define CPPBOX_IMPL_PARSE_HPP

#include <algorithm>
#include <cctype>
#include <charconv>
#include <sstream>
#include <type_traits>

#include "cppbox/parse.hpp"

namespace cppbox {

template<class T>
inline std::size_t max_size_key(const std::map<std::string, T>& map) {
    return map.empty() ? 0 : std::max_element(map.cbegin(), map.cend(), [](const auto& pair1, const auto& pair2) {
        return pair1.first.size() < pair2.first.size();
    })->first.size();
}

template<class T>
inline std::optional<T> to_number(const std::string& string) {
    T number{};
    if constexpr (std::is_integral_v<T>) {
        const char* const end = string.data() + string.size();
        const std::from_chars_result result = std::from_chars(string.data(), end, number);
        return result.ec == std::errc{} && result.ptr == end ? std::optional<T>{number} : std::nullopt;
    } else {  // std::from_chars for floating point types requires GCC 11 or later
        std::istringstream ss(string);
        ss >> number;
        return !ss.fail() && ss.eof() ? std::optional<T>{number} : std::nullopt;
    }
}

inline std::string tolower(const std::string& input) {
    std::string output = input;
    tolower(output);
    return output;
}

inline std::string tolower(std::string&& string) {
    tolower(string);
    return std::move(string);
}

inline void tolower(std::string& input) {
    std::transform(input.begin(), input.end(), input.begin(), [](unsigned char c) { return std::tolower(c); });
}

inline std::string toupper(const std::string& input) {
    std::string output = input;
    toupper(output);
    return output;
}

inline std::string toupper(std::string&& string) {
    toupper(string);
    return std::move(string);
}

inline void toupper(std::string& input) {
    std::transform(input.begin(), input.end(), input.begin(), [](unsigned char c) { return std::toupper(c); });
}

}

#if CPPBOX_HEADER_ONLY
#include "parse.impl.hpp"
#endif

#endif
