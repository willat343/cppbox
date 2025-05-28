#ifndef CPPBOX_PARSE_HPP
#define CPPBOX_PARSE_HPP

#include <string>
#include <vector>

namespace cppbox {

/**
 * @brief Split a string by a deliminator, returning a vector of substrings. If the input is empty, an empty vector is
 * returned.
 *
 * @param input
 * @param delim
 * @return std::vector<std::string>
 */
std::vector<std::string> split_by_char(const std::string& input, const char delim);

}

#endif
