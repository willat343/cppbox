#include "cppbox/parse.hpp"

#include <gtest/gtest.h>

TEST(parse, join) {
    const std::vector<std::string> strings{"a", "b", "c"};
    EXPECT_EQ(cppbox::join(strings, ", "), "a, b, c");
    EXPECT_EQ(cppbox::join(strings), "abc");
    EXPECT_EQ(cppbox::join({}), "");
}

TEST(parse, max_size) {
    const std::vector<std::string> strings{"a", "abc", "ab"};
    EXPECT_EQ(cppbox::max_size(strings), 3u);
    EXPECT_EQ(cppbox::max_size({}), 0u);
}

TEST(parse, max_size_key) {
    const std::map<std::string, int> map{{"a", 1}, {"abc", 2}, {"ab", 3}};
    EXPECT_EQ(cppbox::max_size_key(map), 3u);
    EXPECT_EQ(cppbox::max_size_key(std::map<std::string, int>{}), 0u);
}

TEST(parse, split_by_char) {
    const std::vector<std::string> expected{"a", "b", "c"};
    EXPECT_EQ(cppbox::split_by_char("a,b,c", ','), expected);
    EXPECT_TRUE(cppbox::split_by_char("", ',').empty());
}

TEST(parse, tolower) {
    EXPECT_EQ(cppbox::tolower(std::string("HeLLo")), "hello");
    EXPECT_EQ(cppbox::tolower(std::string("WORLD")), "world");
    std::string in_place = "MiXed";
    cppbox::tolower(in_place);
    EXPECT_EQ(in_place, "mixed");
}

TEST(parse, toupper) {
    EXPECT_EQ(cppbox::toupper(std::string("HeLLo")), "HELLO");
    EXPECT_EQ(cppbox::toupper(std::string("world")), "WORLD");
    std::string in_place = "MiXed";
    cppbox::toupper(in_place);
    EXPECT_EQ(in_place, "MIXED");
}
