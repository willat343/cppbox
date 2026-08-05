#include "cppbox/unordered_set.hpp"

#include <gtest/gtest.h>

#include <vector>

TEST(unordered_set, keys) {
    const std::unordered_set<std::string> set1 = {{"one"}, {"two"}, {"three"}};
    const std::unordered_set<std::string> set2 = {{"one"}, {"three"}, {"five"}, {"seven"}};
    const std::unordered_set<std::string> merged = cppbox::merge(set1, set2);
    const std::unordered_set<std::string> expected = {{"one"}, {"two"}, {"three"}, {"five"}, {"seven"}};
    EXPECT_EQ(merged, expected);
}

TEST(unordered_set, erase_in_place) {
    std::unordered_set<std::string> set = {{"one"}, {"two"}, {"three"}};
    const std::vector<std::string> to_erase = {{"one"}, {"three"}, {"missing"}};
    EXPECT_EQ(cppbox::erase_in_place(set, to_erase), 2u);
    const std::unordered_set<std::string> expected = {{"two"}};
    EXPECT_EQ(set, expected);
}
