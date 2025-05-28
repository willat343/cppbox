#include "cppbox/traits.hpp"

#include <gtest/gtest.h>

TEST(traits, ref) {
    EXPECT_TRUE((std::is_same_v<cppbox::ref_t<double>, double&>));
}

TEST(traits, const_ref) {
    EXPECT_TRUE((std::is_same_v<cppbox::const_ref_t<double>, const double&>));
}

TEST(traits, remove_ref) {
    EXPECT_TRUE((std::is_same_v<cppbox::remove_ref_t<double>, double>));
    EXPECT_TRUE((std::is_same_v<cppbox::remove_ref_t<double&>, double>));
    EXPECT_TRUE((std::is_same_v<cppbox::remove_ref_t<const double&>, const double>));
}
