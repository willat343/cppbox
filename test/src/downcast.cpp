#include "cppbox/downcast.hpp"

#include <gtest/gtest.h>

struct Base {
    virtual ~Base() = default;
};

struct DerivedA : Base {};

struct DerivedB : Base {};

TEST(downcast, mutable_success) {
    DerivedA derived;
    Base* base = &derived;
    EXPECT_EQ(cppbox::downcast_and_check<DerivedA>(base), &derived);
}

TEST(downcast, mutable_failure_throws) {
    DerivedA derived;
    Base* base = &derived;
    EXPECT_ANY_THROW(cppbox::downcast_and_check<DerivedB>(base));
}

TEST(downcast, const_success) {
    const DerivedA derived;
    const Base* base = &derived;
    EXPECT_EQ(cppbox::downcast_and_check<DerivedA>(base), &derived);
}

TEST(downcast, const_failure_throws) {
    const DerivedA derived;
    const Base* base = &derived;
    EXPECT_ANY_THROW(cppbox::downcast_and_check<DerivedB>(base));
}
