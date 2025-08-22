#ifndef CPPBOX_IMPL_PARSE_HPP
#define CPPBOX_IMPL_PARSE_HPP

#include <algorithm>

#include "cppbox/parse.hpp"

namespace cppbox {

template<class T>
inline std::size_t max_size_key(const std::map<std::string, T>& map) {
    return map.empty() ? 0 : std::max_element(map.cbegin(), map.cend(), [](const auto& pair1, const auto& pair2) {
        return pair1.first.size() < pair2.first.size();
    })->first.size();
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
