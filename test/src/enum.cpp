#include "cppbox/enum.hpp"

#include <gtest/gtest.h>

#include <vector>

CREATE_SMART_ENUM(Quality, GOOD, BAD, UGLY)

enum class ExternalQuality { GOOD, BAD, UGLY };
DEFINE_TO_STRING_FUNCTION_FOR_ENUM(ExternalQuality, GOOD, BAD, UGLY)

TEST(create_smart_enum, construct_from_identifier) {
    const Quality quality(Quality::GOOD);
    EXPECT_EQ(quality, Quality::GOOD);
    EXPECT_EQ(std::string(quality), "GOOD");
}

TEST(create_smart_enum, construct_from_string) {
    const Quality quality("BAD");
    EXPECT_EQ(quality, Quality::BAD);
    EXPECT_ANY_THROW(Quality("MISSING"));
}

TEST(create_smart_enum, construct_from_index) {
    const Quality quality(2u);
    EXPECT_EQ(quality, Quality::UGLY);
    EXPECT_ANY_THROW(Quality(3u));
}

TEST(create_smart_enum, count_and_values) {
    EXPECT_EQ(Quality::count, 3u);
    const auto values = Quality::values();
    EXPECT_EQ(values.size(), 3u);
    EXPECT_EQ(values[0], Quality::GOOD);
    EXPECT_EQ(values[1], Quality::BAD);
    EXPECT_EQ(values[2], Quality::UGLY);
}

TEST(create_smart_enum, iteration) {
    std::vector<Quality> collected;
    for (const Quality quality : Quality::values()) {
        collected.push_back(quality);
    }
    EXPECT_EQ(collected.size(), 3u);
}

TEST(create_smart_enum, string_lower_and_upper) {
    const Quality quality(Quality::BAD);
    EXPECT_EQ(quality.string_lower(), "bad");
    EXPECT_EQ(quality.string_upper(), "BAD");
    EXPECT_EQ(Quality::string_lower(0u), "good");
    EXPECT_EQ(Quality::string_upper(0u), "GOOD");
}

TEST(create_smart_enum, switch_statement_usage) {
    const Quality quality(Quality::UGLY);
    std::string result;
    switch (quality) {
        case Quality::GOOD:
            result = "g";
            break;
        case Quality::BAD:
            result = "b";
            break;
        case Quality::UGLY:
            result = "u";
            break;
        default:
            result = "?";
            break;
    }
    EXPECT_EQ(result, "u");
}

TEST(define_to_string_function_for_enum, converts_to_string) {
    EXPECT_EQ(to_string(ExternalQuality::GOOD), "GOOD");
    EXPECT_EQ(to_string(ExternalQuality::UGLY), "UGLY");
}
