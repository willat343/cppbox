#ifndef CPPBOX_IMPL_PARSE_HPP
#define CPPBOX_IMPL_PARSE_HPP

#include <algorithm>

#include "cppbox/parse.hpp"

namespace cppbox {

template<class T>
std::size_t max_size_key(const std::map<std::string, T>& map) {
    return map.empty() ? 0 : std::max_element(map.cbegin(), map.cend(), [](const auto& pair1, const auto& pair2) {
        return pair1.first.size() < pair2.first.size();
    })->first.size();
}

}

#endif
