#include "cppbox/parse.hpp"

#include <algorithm>
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

std::string tolower(const std::string& input) {
    std::string output = input;
    tolower(output);
    return output;
}

std::string tolower(std::string&& string) {
    tolower(string);
    return std::move(string);
}

void tolower(std::string& input) {
    std::transform(input.begin(), input.end(), input.begin(), [](unsigned char c) { return std::tolower(c); });
}

std::string toupper(const std::string& input) {
    std::string output = input;
    toupper(output);
    return output;
}

std::string toupper(std::string&& string) {
    toupper(string);
    return std::move(string);
}

void toupper(std::string& input) {
    std::transform(input.begin(), input.end(), input.begin(), [](unsigned char c) { return std::toupper(c); });
}

}
