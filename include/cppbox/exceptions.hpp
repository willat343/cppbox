#ifndef CPPBOX_EXCEPTIONS_HPP
#define CPPBOX_EXCEPTIONS_HPP

#include <stdexcept>
#include <string>

#include "cppbox/macro.hpp"

// Implementation macro: Throw exception with message (note: do {} while (0) aids macro safety)
#define THROW_INTERNAL(message)                                                                                    \
    do {                                                                                                           \
        throw std::runtime_error(                                                                                  \
                std::string("[") + __FILE__ + ":" + std::to_string(__LINE__) + "|" + __func__ + "] " + (message)); \
    } while (0)

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

/**
 * @brief Use this macro to throw a std::runtime_error if the first argument, a condition, is true. Optionally one can
 * also pass a second argument, a string to provide additional details about the error.
 *
 * Examples:
 *  - throw_if(my_var == 5);
 *  - throw_if(my_vector.empty(), "expected my_vector to contain data");
 *
 */
#define throw_if(...) DISPATCH_GLUE(THROW_IF_IMPL_, VA_NARGS(__VA_ARGS__))(__VA_ARGS__)

// Implementation macro: Throws exception without details
#define THROW_HERE_IMPL_0() THROW_INTERNAL("Exception thrown.")
// Implementation macro: Throws exception with details
#define THROW_HERE_IMPL_1(details) THROW_INTERNAL(std::string("Exception thrown. Details: ") + details)

/**
 * @brief Use this macro to throw a std::runtime_error. Optionally one can pass an argument, a string to provide
 * additional details about the error.
 *
 * Examples:
 *  - throw_here();
 *  - throw_here("encountered error");
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

// Implementation macro: ignore unused variable
#define IGNORE_UNUSED_IMPL(variable) (void)variable;

/**
 * @brief Ignore unused variables. Often useful in conjunction with not_implemented();
 *
 * Example:
 *  ignore_unused(my_var, my_other_var)
 *
 */
#define ignore_unused(...) FOR_EACH(IGNORE_UNUSED_IMPL, __VA_ARGS__)

#endif
