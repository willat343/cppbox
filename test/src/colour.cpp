#include "cppbox/colour.hpp"

#include <gtest/gtest.h>

#include <array>
#include <limits>
#include <stdexcept>

TEST(colour, default_opaque_black) {
    const cppbox::Colour<double> colour;
    EXPECT_EQ(colour.r(), 0.0);
    EXPECT_EQ(colour.g(), 0.0);
    EXPECT_EQ(colour.b(), 0.0);
    EXPECT_EQ(colour.a(), 1.0);
}

TEST(colour, construct_from_components) {
    const cppbox::Colour<double> colour{0.1, 0.2, 0.3, 0.4};
    EXPECT_EQ(colour.r(), 0.1);
    EXPECT_EQ(colour.g(), 0.2);
    EXPECT_EQ(colour.b(), 0.3);
    EXPECT_EQ(colour.a(), 0.4);
    EXPECT_EQ(cppbox::Colour<double>(0.1, 0.2, 0.3).a(), 1.0);
}

TEST(colour, construct_from_array) {
    EXPECT_EQ(cppbox::Colour<double>(std::array<double, 4>{0.1, 0.2, 0.3, 0.4}),
            cppbox::Colour<double>(0.1, 0.2, 0.3, 0.4));
    // Opaque from red, green and blue
    EXPECT_EQ(cppbox::Colour<double>(std::array<double, 3>{0.1, 0.2, 0.3}), cppbox::Colour<double>(0.1, 0.2, 0.3, 1.0));
    EXPECT_THROW(cppbox::Colour<double>(std::array<double, 3>{0.1, 1.2, 0.3}), std::invalid_argument);
}

TEST(colour, construct_float) {
    const cppbox::Colour<float> colour{0.25f, 0.5f, 0.75f};
    EXPECT_EQ(colour.g(), 0.5f);
    EXPECT_EQ(colour.a(), 1.0f);
    EXPECT_THROW(cppbox::Colour<float>(1.5f, 0.0f, 0.0f), std::invalid_argument);
}

TEST(colour, components_outside_unit_interval) {
    EXPECT_THROW(cppbox::Colour<double>(-0.1, 0.0, 0.0, 1.0), std::invalid_argument);
    EXPECT_THROW(cppbox::Colour<double>(0.0, 1.1, 0.0, 1.0), std::invalid_argument);
    EXPECT_THROW(cppbox::Colour<double>(0.0, 0.0, 2.0, 1.0), std::invalid_argument);
    EXPECT_THROW(cppbox::Colour<double>(0.0, 0.0, 0.0, -1.0), std::invalid_argument);
    EXPECT_THROW(cppbox::Colour<double>(std::numeric_limits<double>::quiet_NaN(), 0.0, 0.0, 1.0),
            std::invalid_argument);
}

TEST(colour, from_name) {
    EXPECT_EQ(cppbox::Colour<double>::from_name(cppbox::ColourName::ORANGE),
            cppbox::Colour<double>(1.0, 0.5, 0.0, 1.0));
    EXPECT_EQ(cppbox::Colour<double>::from_name(cppbox::ColourName("CYAN")),
            cppbox::Colour<double>(0.0, 1.0, 1.0, 1.0));
    // Every name has an opaque colour
    for (const cppbox::ColourName name : cppbox::ColourName::values()) {
        EXPECT_EQ(cppbox::Colour<double>::from_name(name).a(), 1.0);
    }
}

TEST(colour, from_seed) {
    const cppbox::Colour<double> colour = cppbox::Colour<double>::from_seed("anymal_d");
    EXPECT_EQ(colour, cppbox::Colour<double>::from_seed("anymal_d"));
    EXPECT_NE(colour, cppbox::Colour<double>::from_seed("anymal_c"));
    EXPECT_EQ(colour.a(), 1.0);
}
