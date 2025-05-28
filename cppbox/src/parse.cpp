#include "cppbox/parse.hpp"

#include <sstream>

namespace cppbox {

std::vector<std::string> split_by_char(const std::string& input, const char delim) {
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
