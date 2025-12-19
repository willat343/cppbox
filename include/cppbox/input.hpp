#ifndef CPPBOX_INPUT_HPP
#define CPPBOX_INPUT_HPP

#include <iostream>

namespace cppbox {

/**
 * @brief Wait for and return input entered (ENTER pressed).
 *
 * @return std::optional<std::string>, std::nullopt if EOF or error occured
 */
std::optional<std::string> get_input();

/**
 * @brief Wait for a specific string to be entered (ENTER pressed), generalising wait for key.
 *
 * @param string
 * @return true if string was received, false if EOF or error occured
 */
bool wait_for_string(const std::string& string);

}

#include "cppbox/impl/input.hpp"

#endif
