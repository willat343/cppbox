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

/**
 * @brief Convert string to lowercase.
 *
 * @param string
 * @return std::string
 */
std::string tolower(const std::string& string);

/**
 * @brief Convert string (temporary) to lowercase.
 *
 * @param string
 * @return std::string
 */
std::string tolower(std::string&& string);

/**
 * @brief Convert string to lowercase in-place.
 *
 * @param string
 */
void tolower(std::string& string);

/**
 * @brief Convert string to uppercase.
 *
 * @param string
 * @return std::string
 */
std::string toupper(const std::string& string);

/**
 * @brief Convert string (temporary) to uppercase.
 *
 * @param string
 * @return std::string
 */
std::string toupper(std::string&& string);

/**
 * @brief Convert string to uppercase in-place.
 *
 * @param string
 */
void toupper(std::string& string);

}

#endif
