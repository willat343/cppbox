#ifndef CPPBOX_IMPL_PARSE_IMPL_HPP
#define CPPBOX_IMPL_PARSE_IMPL_HPP

#include <algorithm>
#include <numeric>
#include <sstream>

#include "cppbox/impl/cppbox.hpp"
#include "cppbox/impl/parse.hpp"

namespace cppbox {

CPPBOX_INLINE std::string join(const std::vector<std::string>& strings, const std::string& delimiter) {
    return strings.empty() ? std::string()
                           : std::accumulate(std::next(strings.cbegin()), strings.cend(), strings[0],
                                     [&delimiter](const std::string& lhs, const std::string& rhs) {
                                         return lhs + delimiter + rhs;
                                     });
}

CPPBOX_INLINE std::size_t max_size(const std::vector<std::string>& strings) {
    return strings.empty()
                   ? 0
                   : std::max_element(strings.cbegin(), strings.cend(), [](const auto& string1, const auto& string2) {
                         return string1.size() < string2.size();
                     })->size();
}

CPPBOX_INLINE std::vector<std::string> split_by_char(const std::string& input, const char delim) {
    std::vector<std::string> output;
    if (!input.empty()) {
        std::stringstream ss(input);
        while (ss.good()) {
            std::string substr;
            getline(ss, substr, delim);
            output.push_back(substr);
        }
    }
    return output;
}

}

#endif
