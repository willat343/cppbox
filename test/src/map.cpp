#include "cppbox/map.hpp"

#include <gtest/gtest.h>

TEST(map, keys) {
    const std::map<std::string, int> map = {{"one", 1}, {"two", 2}, {"three", 3}};
    const std::set<std::string> set = cppbox::keys(map);
    EXPECT_EQ(map.size(), set.size());
    for (const std::string& key : map | std::views::keys) {
        EXPECT_TRUE(set.contains(key));
    }
}

TEST(map, to_string) {
    const std::map<std::string, int> map = {{"one", 1}, {"two", 2}};
    EXPECT_EQ(cppbox::to_string(map), "one: 1\ntwo: 2\n");
}
