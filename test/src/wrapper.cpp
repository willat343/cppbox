#include "cppbox/wrapper.hpp"

#include <gtest/gtest.h>

TEST(wrapper, is_wrapper) {
    EXPECT_TRUE(cppbox::IsWrapper<cppbox::Wrapper<int>>);
    EXPECT_TRUE((cppbox::IsWrapper<cppbox::Wrapper<int>&>));
    EXPECT_FALSE(cppbox::IsWrapper<cppbox::ConstWrapper<int>>);
    EXPECT_FALSE(cppbox::IsWrapper<int>);
}

TEST(wrapper, is_const_wrapper) {
    EXPECT_TRUE(cppbox::IsConstWrapper<cppbox::ConstWrapper<int>>);
    EXPECT_TRUE((cppbox::IsConstWrapper<cppbox::ConstWrapper<int>&>));
    EXPECT_FALSE(cppbox::IsConstWrapper<cppbox::Wrapper<int>>);
    EXPECT_FALSE(cppbox::IsConstWrapper<int>);
}

TEST(wrapper, wrapper_access) {
    int value = 5;
    cppbox::Wrapper<int> wrapper(value);
    EXPECT_EQ(*wrapper, 5);
    *wrapper = 6;
    EXPECT_EQ(value, 6);
}

TEST(wrapper, const_wrapper_access) {
    const int value = 5;
    cppbox::ConstWrapper<int> const_wrapper(value);
    EXPECT_EQ(*const_wrapper, 5);
}
