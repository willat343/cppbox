#ifndef CPPBOX_MACRO_HPP
#define CPPBOX_MACRO_HPP

// Add a comma to the end
#define ADD_COMMA(x) x,

// FE (FOR_EACH) macros to handle up to 19 arguments
#define FE0(MACRO)
#define FE1(MACRO, X) MACRO(X)
#define FE2(MACRO, X, ...) MACRO(X) FE1(MACRO, __VA_ARGS__)
#define FE3(MACRO, X, ...) MACRO(X) FE2(MACRO, __VA_ARGS__)
#define FE4(MACRO, X, ...) MACRO(X) FE3(MACRO, __VA_ARGS__)
#define FE5(MACRO, X, ...) MACRO(X) FE4(MACRO, __VA_ARGS__)
#define FE6(MACRO, X, ...) MACRO(X) FE5(MACRO, __VA_ARGS__)
#define FE7(MACRO, X, ...) MACRO(X) FE6(MACRO, __VA_ARGS__)
#define FE8(MACRO, X, ...) MACRO(X) FE7(MACRO, __VA_ARGS__)
#define FE9(MACRO, X, ...) MACRO(X) FE8(MACRO, __VA_ARGS__)
#define FE10(MACRO, X, ...) MACRO(X) FE9(MACRO, __VA_ARGS__)
#define FE11(MACRO, X, ...) MACRO(X) FE10(MACRO, __VA_ARGS__)
#define FE12(MACRO, X, ...) MACRO(X) FE11(MACRO, __VA_ARGS__)
#define FE13(MACRO, X, ...) MACRO(X) FE12(MACRO, __VA_ARGS__)
#define FE14(MACRO, X, ...) MACRO(X) FE13(MACRO, __VA_ARGS__)
#define FE15(MACRO, X, ...) MACRO(X) FE14(MACRO, __VA_ARGS__)
#define FE16(MACRO, X, ...) MACRO(X) FE15(MACRO, __VA_ARGS__)
#define FE17(MACRO, X, ...) MACRO(X) FE16(MACRO, __VA_ARGS__)
#define FE18(MACRO, X, ...) MACRO(X) FE17(MACRO, __VA_ARGS__)
#define FE19(MACRO, X, ...) MACRO(X) FE18(MACRO, __VA_ARGS__)

// Expansion based on argument count
#define FOR_EACH_IMPL(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, IMPL, \
        ...)                                                                                                          \
    IMPL

/**
 * @brief The `FOR_EACH` macro calls `MACRO` on each argument passed in.
 *
 */
#define FOR_EACH(MACRO, ...)                                                                                         \
    FOR_EACH_IMPL(_0, ##__VA_ARGS__, FE19, FE18, FE17, FE16, FE15, FE14, FE13, FE12, FE11, FE10, FE9, FE8, FE7, FE6, \
            FE5, FE4, FE3, FE2, FE1, FE0)                                                                            \
    (MACRO, ##__VA_ARGS__)

// FEI (FOR_EACH_I) macros to handle up to 19 arguments
#define FEI0(MACRO, DATA)
#define FEI1(MACRO, DATA, X) MACRO(DATA, X)
#define FEI2(MACRO, DATA, X, ...) MACRO(DATA, X) FEI1(MACRO, DATA, __VA_ARGS__)
#define FEI3(MACRO, DATA, X, ...) MACRO(DATA, X) FEI2(MACRO, DATA, __VA_ARGS__)
#define FEI4(MACRO, DATA, X, ...) MACRO(DATA, X) FEI3(MACRO, DATA, __VA_ARGS__)
#define FEI5(MACRO, DATA, X, ...) MACRO(DATA, X) FEI4(MACRO, DATA, __VA_ARGS__)
#define FEI6(MACRO, DATA, X, ...) MACRO(DATA, X) FEI5(MACRO, DATA, __VA_ARGS__)
#define FEI7(MACRO, DATA, X, ...) MACRO(DATA, X) FEI6(MACRO, DATA, __VA_ARGS__)
#define FEI8(MACRO, DATA, X, ...) MACRO(DATA, X) FEI7(MACRO, DATA, __VA_ARGS__)
#define FEI9(MACRO, DATA, X, ...) MACRO(DATA, X) FEI8(MACRO, DATA, __VA_ARGS__)
#define FEI10(MACRO, DATA, X, ...) MACRO(DATA, X) FEI9(MACRO, DATA, __VA_ARGS__)
#define FEI11(MACRO, DATA, X, ...) MACRO(DATA, X) FEI10(MACRO, DATA, __VA_ARGS__)
#define FEI12(MACRO, DATA, X, ...) MACRO(DATA, X) FEI11(MACRO, DATA, __VA_ARGS__)
#define FEI13(MACRO, DATA, X, ...) MACRO(DATA, X) FEI12(MACRO, DATA, __VA_ARGS__)
#define FEI14(MACRO, DATA, X, ...) MACRO(DATA, X) FEI13(MACRO, DATA, __VA_ARGS__)
#define FEI15(MACRO, DATA, X, ...) MACRO(DATA, X) FEI14(MACRO, DATA, __VA_ARGS__)
#define FEI16(MACRO, DATA, X, ...) MACRO(DATA, X) FEI15(MACRO, DATA, __VA_ARGS__)
#define FEI17(MACRO, DATA, X, ...) MACRO(DATA, X) FEI16(MACRO, DATA, __VA_ARGS__)
#define FEI18(MACRO, DATA, X, ...) MACRO(DATA, X) FEI17(MACRO, DATA, __VA_ARGS__)
#define FEI19(MACRO, DATA, X, ...) MACRO(DATA, X) FEI18(MACRO, DATA, __VA_ARGS__)

/**
 * @brief The `FOR_EACH` macro calls `MACRO` on each argument passed in.
 *
 */
#define FOR_EACH_I(MACRO, DATA, ...)                                                                                   \
    FOR_EACH_IMPL(_0, ##__VA_ARGS__, FEI19, FEI18, FEI17, FEI16, FEI15, FEI14, FEI13, FEI12, FEI11, FEI10, FEI9, FEI8, \
            FEI7, FEI6, FEI5, FEI4, FEI3, FEI2, FEI1, FEI0)                                                            \
    (MACRO, DATA, ##__VA_ARGS__)

/**
 * @brief The `GLUE` macro combines two strings together.
 *
 */
#define GLUE(left, right) left##right

/**
 * @brief The `DISPATCH_GLUE` macro enables a two-step expansion of the left and right arguments before gluing,
 * useful for VA_NARGS for macro selection.
 *
 */
#define DISPATCH_GLUE(left, right) GLUE(left, right)

// Implementation for VA_NARGS macro
#define VA_NARGS_IMPL(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, N, \
        ...)                                                                                                       \
    N

/**
 * @brief The `VA_NARGS` returns the number of arguments when in range 0 to 19.
 *
 */
#define VA_NARGS(...) \
    VA_NARGS_IMPL(_0, ##__VA_ARGS__, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)

#endif
