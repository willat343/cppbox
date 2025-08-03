#include "cppbox/parse.hpp"

#include <algorithm>
#include <numeric>
#include <sstream>

namespace cppbox {

std::string join(const std::vector<std::string>& strings, const std::string& delimiter) {
    return strings.empty() ? std::string()
                           : std::accumulate(std::next(strings.cbegin()), strings.cend(), strings[0],
                                     [&delimiter](const std::string& lhs, const std::string& rhs) {
                                         return lhs + delimiter + rhs;
                                     });
}

std::size_t max_size(const std::vector<std::string>& strings) {
    return strings.empty()
                   ? 0
                   : std::max_element(strings.cbegin(), strings.cend(), [](const auto& string1, const auto& string2) {
                         return string1.size() < string2.size();
                     })->size();
}

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
