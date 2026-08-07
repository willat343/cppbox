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

TEST(parse, to_number) {
    EXPECT_EQ(cppbox::to_number<std::size_t>("42"), 42u);
    EXPECT_EQ(cppbox::to_number<int>("-7"), -7);
    EXPECT_EQ(cppbox::to_number<double>("1.5"), 1.5);
    EXPECT_FALSE(cppbox::to_number<std::size_t>("").has_value());
    EXPECT_FALSE(cppbox::to_number<std::size_t>("-1").has_value());
    EXPECT_FALSE(cppbox::to_number<std::size_t>("12a").has_value());
    EXPECT_FALSE(cppbox::to_number<std::size_t>("a12").has_value());
    EXPECT_FALSE(cppbox::to_number<std::size_t>("1 2").has_value());
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

TEST(parse, trim) {
    EXPECT_EQ(cppbox::trim(std::string(" \t hello world \r\n")), "hello world");
    EXPECT_EQ(cppbox::trim(std::string("hello")), "hello");
    EXPECT_EQ(cppbox::trim(std::string(" \t\r\n")), "");
    EXPECT_EQ(cppbox::trim(std::string()), "");
    std::string in_place = "  padded  ";
    cppbox::trim(in_place);
    EXPECT_EQ(in_place, "padded");
}
