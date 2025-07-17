#ifndef CPPBOX_MAP_HPP
#define CPPBOX_MAP_HPP

#include <map>
#include <string>

namespace cppbox {

template<class Key, class T, class Compare, class Allocator>
std::string to_string(const std::map<Key, T, Compare, Allocator>& map);

}

#include "cppbox/impl/map.hpp"

#endif
