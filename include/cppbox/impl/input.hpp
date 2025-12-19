#include <iostream>
#include <optional>

#include "cppbox/input.hpp"

namespace cppbox {

inline std::optional<std::string> get_input() {
    std::string input;
    if (std::cin >> input) {
        return input;
    }
    return std::nullopt;
}

inline bool wait_for_string(const std::string& string) {
    std::string input;
    while (std::cin >> input) {
        if (input == string) {
            return true;
        }
    }
    return false;
}

}
