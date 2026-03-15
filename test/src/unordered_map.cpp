#include "cppbox/unordered_map.hpp"

#include <gtest/gtest.h>

TEST(unordered_map, keys) {
    const std::unordered_map<std::string, int> unordered_map = {{"one", 1}, {"two", 2}, {"three", 3}};
    const std::unordered_set<std::string> unordered_set = cppbox::keys(unordered_map);
    EXPECT_EQ(unordered_map.size(), unordered_set.size());
    for (const std::string& key : unordered_map | std::views::keys) {
        EXPECT_TRUE(unordered_set.contains(key));
    }
}
