#ifndef CPPBOX_EXCEPTIONS_HPP
#define CPPBOX_EXCEPTIONS_HPP

#include <stdexcept>
#include <string>

#include "cppbox/macro.hpp"

// Implementation macro: Throw exception of given type with message
#define THROW_INTERNAL_TYPE(exception_type, message) \
    throw exception_type(                            \
            std::string("[") + __FILE__ + ":" + std::to_string(__LINE__) + "|" + __func__ + "] " + (message))

// Implementation macro: Throw std::runtime_error with message
#define THROW_INTERNAL(message) THROW_INTERNAL_TYPE(std::runtime_error, message)

// Implementation macro: Conditionally throws exception without details
#define THROW_IF_IMPL_1(condition)                                                \
    do {                                                                          \
        if (condition) [[unlikely]]                                               \
            THROW_INTERNAL(std::string("Error Condition: '") + #condition + "'"); \
    } while (0)

// Implementation macro: Conditionally throws exception with details
#define THROW_IF_IMPL_2(condition, details)                                                              \
    do {                                                                                                 \
        if (condition) [[unlikely]]                                                                      \
            THROW_INTERNAL(std::string("Error Condition: '") + #condition + "', Details: " + (details)); \
    } while (0)

// Implementation macro: Conditionally throws exception of given type with details
#define THROW_IF_IMPL_3(condition, details, exception_type)                                                          \
    do {                                                                                                             \
        if (condition) [[unlikely]]                                                                                  \
            THROW_INTERNAL_TYPE(                                                                                     \
                    exception_type, std::string("Error Condition: '") + #condition + "', Details: " + (details));    \
    } while (0)

/**
 * @brief Use this macro to throw an exception if the first argument, a condition, is true. Optionally one can also pass
 * a second argument, a string to provide additional details about the error, and a third argument, the type of the
 * exception to throw, which must be constructible from a std::string and cannot contain unparenthesised commas. The
 * default exception type is std::runtime_error.
 *
 * Examples:
 *  - throw_if(my_var == 5);
 *  - throw_if(my_vector.empty(), "expected my_vector to contain data");
 *  - throw_if(my_var < 0, "expected my_var to be non-negative", std::invalid_argument);
 *
 */
#define throw_if(...) DISPATCH_GLUE(THROW_IF_IMPL_, VA_NARGS(__VA_ARGS__))(__VA_ARGS__)

// Implementation macro: Throws exception without details
#define THROW_HERE_IMPL_0() THROW_INTERNAL("Exception thrown.")
// Implementation macro: Throws exception with details
#define THROW_HERE_IMPL_1(details) THROW_INTERNAL(std::string("Exception thrown. Details: ") + details)

// Implementation macro: Throws exception of given type with details
#define THROW_HERE_IMPL_2(details, exception_type) \
    THROW_INTERNAL_TYPE(exception_type, std::string("Exception thrown. Details: ") + (details))

/**
 * @brief Use this macro to throw an exception. Optionally one can pass a first argument, a string to provide
 * additional details about the error, and a second argument, the type of the exception to throw, which must be
 * constructible from a std::string and cannot contain unparenthesised commas. The default exception type is
 * std::runtime_error.
 *
 * Examples:
 *  - throw_here();
 *  - throw_here("encountered error");
 *  - throw_here("index out of range", std::out_of_range);
 *
 */
#define throw_here(...) DISPATCH_GLUE(THROW_HERE_IMPL_, VA_NARGS(__VA_ARGS__))(__VA_ARGS__)

// Implementation macro: Throws exception without details
#define NOT_IMPLEMENTED_IMPL_0() THROW_INTERNAL("Not implemented.")
// Implementation macro: Throws exception with details
#define NOT_IMPLEMENTED_IMPL_1(details) THROW_INTERNAL(std::string("Not implemented. Details: ") + (details))

/**
 * @brief Use this macro to throw a std::runtime_error indicating essential code is not implemented. Optionally one can
 * also pass an argument, a string to provide additional details about implementation.
 *
 * Examples:
 *  - not_implemented();
 *  - not_implemented("this function must be implemented after my_other_function()");
 *
 */
#define not_implemented(...) DISPATCH_GLUE(NOT_IMPLEMENTED_IMPL_, VA_NARGS(__VA_ARGS__))(__VA_ARGS__)

namespace cppbox {

/**
 * @brief Ignore unused variables. Often useful in conjunction with not_implemented();
 *
 * Example:
 *  cppbox::ignore_unused(my_var, my_other_var);
 *
 */
template<typename... Args>
constexpr void ignore_unused(const Args&...) {}

}

#endif
