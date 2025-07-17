#ifndef CPPBOX_IMPL_MAP_HPP
#define CPPBOX_IMPL_MAP_HPP

#include <sstream>

#include "cppbox/map.hpp"

namespace cppbox {

template<class Key, class T, class Compare, class Allocator>
std::string to_string(const std::map<Key, T, Compare, Allocator>& map) {
    std::stringstream ss;
    for (const auto& [k, v] : map) {
        ss << k << ": " << v << "\n";
    }
    return ss.str();
}

}

#endif
