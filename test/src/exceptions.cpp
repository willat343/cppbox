#include "cppbox/exceptions.hpp"

#include <gtest/gtest.h>

#include <stdexcept>
#include <string>

TEST(exceptions, throw_if_without_details) {
    throw_if(false);
    EXPECT_ANY_THROW(throw_if(true));
}

TEST(exceptions, throw_if_with_details) {
    throw_if(false, std::string("should not throw"));
    try {
        throw_if(true, std::string("boom"));
        FAIL() << "Expected throw_if to throw";
    } catch (const std::runtime_error& e) {
        EXPECT_NE(std::string(e.what()).find("boom"), std::string::npos);
    }
}

TEST(exceptions, throw_if_with_exception_type) {
    throw_if(false, std::string("should not throw"), std::invalid_argument);
    try {
        throw_if(1 > 0, std::string("boom"), std::invalid_argument);
        FAIL() << "Expected throw_if to throw";
    } catch (const std::invalid_argument& e) {
        EXPECT_NE(std::string(e.what()).find("boom"), std::string::npos);
        EXPECT_NE(std::string(e.what()).find("1 > 0"), std::string::npos);
    }
    EXPECT_THROW(throw_if(true, "out of range", std::out_of_range), std::out_of_range);
}

TEST(exceptions, throw_here_without_details) {
    EXPECT_ANY_THROW(throw_here());
}

TEST(exceptions, throw_here_with_details) {
    try {
        throw_here(std::string("custom failure"));
        FAIL() << "Expected throw_here to throw";
    } catch (const std::runtime_error& e) {
        EXPECT_NE(std::string(e.what()).find("custom failure"), std::string::npos);
    }
}

TEST(exceptions, throw_here_with_exception_type) {
    try {
        throw_here(std::string("custom failure"), std::out_of_range);
        FAIL() << "Expected throw_here to throw";
    } catch (const std::out_of_range& e) {
        EXPECT_NE(std::string(e.what()).find("custom failure"), std::string::npos);
    }
}

TEST(exceptions, not_implemented_without_details) {
    EXPECT_ANY_THROW(not_implemented());
}

TEST(exceptions, not_implemented_with_details) {
    try {
        not_implemented(std::string("todo"));
        FAIL() << "Expected not_implemented to throw";
    } catch (const std::runtime_error& e) {
        EXPECT_NE(std::string(e.what()).find("todo"), std::string::npos);
    }
}

TEST(exceptions, ignore_unused_compiles) {
    const int a = 1;
    const double b = 2.0;
    cppbox::ignore_unused(a, b);
}
