#include "cppbox/unordered_set.hpp"

#include <gtest/gtest.h>

TEST(unordered_set, keys) {
    const std::unordered_set<std::string> set1 = {{"one"}, {"two"}, {"three"}};
    const std::unordered_set<std::string> set2 = {{"one"}, {"three"}, {"five"}, {"seven"}};
    const std::unordered_set<std::string> merged = cppbox::merge(set1, set2);
    const std::unordered_set<std::string> expected = {{"one"}, {"two"}, {"three"}, {"five"}, {"seven"}};
    EXPECT_EQ(merged, expected);
}
